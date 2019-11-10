#include <zconf.h>
#include "Drawer.h"
#include "Window.h"
#include "ProtectedModel.h"

Drawer::Drawer(Window& main, ProtectedModel& model) :
main(main), model(model){
    this->running = true;
}

void Drawer::run() {

    std::chrono::high_resolution_clock::duration fixed_time(60);

    while (running){
        std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
        this->main.clear();
        this->model.renderAll();
        this->main.update();
        std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
        std::this_thread::sleep_for(fixed_time - (start - end));
    }
}

void Drawer::stop() {
    running = false;
}
