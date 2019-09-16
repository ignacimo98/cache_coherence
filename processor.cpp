//
// Created by Ignacio Mora on 2019-09-13.
//

#include <iostream>
#include "processor.h"

Processor::Processor(bool *clk, int num_cores, int dist_number, float parameter, Memory* memory):memory_controller(&cache_bus, clk, memory) {
    this->clk = clk;
    this->num_cores = num_cores;
    this->memory = memory;


    Program* program = new Program(dist_number, parameter);


    for (int i = 0; i < num_cores; ++i) {
        cores.push_back(new Core(clk, i, new Program(dist_number, parameter), &cache_bus, memory));
    }


}

void Processor::run() {

    for (int i = 0; i < num_cores; ++i) {
        core_threads.push_back(std::thread(&Core::run,*cores[i]));
    }
    mem_ctrl_thread = std::thread(&MemoryController::startCheckingBus, &memory_controller);


}
