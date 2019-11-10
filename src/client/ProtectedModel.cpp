#include "ProtectedModel.h"
#include "Entity.h"
#include "Camera.h"
#include "Car.h"
#include <vector>
#include <mutex>
#include "Window.h"
#include "TileMap.h"
#include "ThrowableFactory.h"
#include <string>

ProtectedModel::ProtectedModel(Window& main, std::string playerID) :
    playerID(playerID), 
	main(main), 
	cam(main), 
	map(main, "../media/maps/simple.json",  cam.getZoom()) {}

void ProtectedModel::updateCar(std::string& id,
                                  int x,
                                  int y,
                                  int angle,
                                  int health) {
    std::unique_lock<std::mutex> lck(m);

    if (entities.count(id) == 0)
        this->entities[id] = new Car("../media/sprites/pitstop_car_1.png", main);

    if (!cam.targetSet()) 
        cam.setOnTarget(this->entities[this->playerID]);

    if (entities[id] != NULL) {
        std::cout << "Se setea estado en auto\n";
        entities[id]->setState(0, 0, angle, health);
        //entities[id]->setState(x * cam.getZoom() / 1000, y * cam.getZoom() / 1000, angle, health);
    }
}

void ProtectedModel::updateObject(int id, int type, int x, int y, bool state) {
    std::unique_lock<std::mutex> lck(m);

    if (objects.count(id) == 0) {
        std::cout << "Se crea objeto id: " << id << std::endl;
        ThrowableFactory factory(this->main);
        this->objects[id] = factory.generateThrowable(type);
    }

    this->objects[id]->setPos(x * cam.getZoom() / 1000 , y * cam.getZoom() / 1000);
    this->objects[id]->setState(state);
}

void ProtectedModel::renderAll() {
    std::unique_lock<std::mutex> lock(m);
    std::cout << "Se renderiza modelo" << std::endl;
    if (this->cam.targetSet()) {
        map.render(cam);
        cam.update();
        for (auto& object : objects)
            object.second->render(cam);
        for (auto& car : entities)
            car.second->render(cam);
    }
}

ProtectedModel::~ProtectedModel(){
    for (auto& car : entities)
        delete car.second;
    for (auto& object : objects)
        delete object.second;
}


std::vector<int> ProtectedModel::getActualState() {
    std::unique_lock<std::mutex> lock(m);
    std::vector<int> state;
    state.push_back(this->entities[playerID]->getAngle());
    state.push_back(this->entities[playerID]->getXPos());
    state.push_back(this->entities[playerID]->getYPos());
    return state;
}

std::vector<std::vector<int>> ProtectedModel::getEntitiesPos() {
    std::unique_lock<std::mutex> lock(m);
    std::vector<std::vector<int>> entities_buf;
    for (auto& object : objects) {
        std::vector<int> entity_buf;
        entity_buf.push_back(object.first);
        entity_buf.push_back(object.second->getXPos());
        entity_buf.push_back(object.second->getYPos());
        entities_buf.push_back(std::move(entity_buf));
    }
    return entities_buf;
}

std::vector<std::vector<int>>& ProtectedModel::getMap() {
    return map.getTileNumbers();
}
