#include <sys/param.h>
#include "TileMap.h"
#include "Window.h"
#include "Constants.h"
#include "Car.h"
#include <nlohmann/json.hpp>
#include <Identifiers.h>

TileMap::TileMap(Window& window, const std::string& mapFile, int zoom, int offset) :
window(window) {
    std::ifstream in(mapFile);
    nlohmann::json json_p;
    in >> json_p;
    int sized = json_p["tiles"].size();
    int x = - (sized - 1) * TILE_WIDTH * zoom / 2;
    int y = - (sized - 1) * TILE_HEIGHT * zoom / 2;

    for (auto& tileList : json_p["tiles"]) {
        std::vector<int> tiles2 = tileList.get<std::vector<int>>();
        int size2 = tiles2.size();
        x = - (size2 - 1) * TILE_WIDTH * zoom / 2;
        for (int j : tiles2) {
            this->tiles.emplace_back(std::move(Tile(window, TILE_0, x, y,  TILE_HEIGHT, TILE_WIDTH)));
            if (j == THIRD_QUAD_TRACK) {
                this->tiles.emplace_back(std::move(Tile(window, TILE_1, x, y,  TILE_HEIGHT, TILE_WIDTH)));
            }
            else if (j == SECOND_QUAD_TRACK) {
                this->tiles.emplace_back(std::move(Tile(window, TILE_2, x, y, TILE_HEIGHT, TILE_WIDTH)));
            }
            else if (j == FOURTH_QUAD_TRACK) {
                this->tiles.emplace_back(std::move(Tile(window, TILE_3, x, y, TILE_HEIGHT, TILE_WIDTH)));
            }
            else if (j == FIRST_QUAD_TRACK) {
                this->tiles.emplace_back(std::move(Tile(window, TILE_4, x, y,  TILE_HEIGHT, TILE_WIDTH)));
            }
            else if (j == LEFT_TRACK) {
                this->tiles.emplace_back(std::move(Tile(window, TILE_5, x, y,  TILE_HEIGHT, TILE_WIDTH)));
            }
            else if (j == RIGHT_TRACK) {
                this->tiles.emplace_back(std::move(Tile(window, TILE_6, x, y,  TILE_HEIGHT, TILE_WIDTH)));
            }
            else if (j == UP_TRACK) {
                this->tiles.emplace_back(std::move(Tile(window, TILE_7, x, y,  TILE_HEIGHT, TILE_WIDTH)));
            }
            else if (j == DOWN_TRACK) {
                this->tiles.emplace_back(std::move(Tile(window, TILE_8, x, y,  TILE_HEIGHT, TILE_WIDTH)));
            }
            x += (zoom * TILE_WIDTH);
        }
        y += (zoom*TILE_HEIGHT);
    }
    in.close();
}


void TileMap::render(Camera& cam ){
    for (Tile &tile : this->tiles)
        tile.render(cam);
}

TileMap::~TileMap() { }
