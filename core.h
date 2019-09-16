//
// Created by Ignacio Mora on 2019-09-11.
//

#ifndef PROYECTO1ARQUIII_CORE_H
#define PROYECTO1ARQUIII_CORE_H

#include <thread>
#include <chrono>


#include "include/random.hpp"
#include "program.h"
#include "cache_controller.h"


using Random = effolkronium::random_static;

class Core {

public:
    Core(bool* clk, int num_core, Program* program, CacheBus* cache_bus, Memory* memory);
    void run();

private:
    Program* program;
    int num_core;
    CacheController* cache_controller;
    bool running;
    bool* clk;
    bool last_clk_state;
    bool waiting_for_execution = false;



};


#endif //PROYECTO1ARQUIII_CORE_H
