//
// Created by Ignacio Mora on 2019-09-13.
//

#ifndef PROYECTO1ARQUIII_PROCESSOR_H
#define PROYECTO1ARQUIII_PROCESSOR_H


#include "core.h"
#include "program.h"
#include "memory.h"
#include "memory_controller.h"

class Processor {
private:
    bool* clk;
    CacheBus cache_bus;
    Memory* memory;
    MemoryController memory_controller;

    int num_cores;
    std::vector<Core*> cores;
    std::vector<std::thread> core_threads;
    std::vector<std::default_random_engine*> random_engines;
    std::vector<Program*> programs;
    std::thread mem_ctrl_thread;


public:
    Processor(bool* clk, int num_cores, int dist_number, float parameter, Memory* memory);

    void run();

};


#endif //PROYECTO1ARQUIII_PROCESSOR_H
