//
// Created by Ignacio Mora on 2019-09-14.
//

#ifndef PROYECTO1ARQUIII_MEMORY_CONTROLLER_H
#define PROYECTO1ARQUIII_MEMORY_CONTROLLER_H


#include "cache_bus.h"
#include "memory.h"

class MemoryController {
private:
    CacheBus* cache_bus;
    bool* clk;
    Memory* memory;
    bool running;
    bool last_clk_state;
    int ticks_to_wait = 2;

public:
    MemoryController(CacheBus* cache_bus, bool* clk, Memory* memory);
    void startCheckingBus();
    void checkBus();

};


#endif //PROYECTO1ARQUIII_MEMORY_CONTROLLER_H
