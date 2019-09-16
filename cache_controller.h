//
// Created by Ignacio Mora on 2019-09-11.
//

#ifndef PROYECTO1ARQUIII_CACHE_CONTROLLER_H
#define PROYECTO1ARQUIII_CACHE_CONTROLLER_H


#include "cache.h"
#include "cache_bus.h"
#include "memory.h"

class CacheController {
private:
    int num_core;
    Cache cache;
    CacheBus* bus;
    bool invalidate_request_arrived = false;
    int address_to_invalidate;
    bool waiting_for_response;
    int address_requested;
    bool running = false;
    bool sent_by_mem;
    Memory* memory;



public:
    CacheController(CacheBus* cache_bus, int num_core, Memory* memory);
    int readData(int address);
    void writeData(int address, int data);
    void checkBus();
    void startCheckingBus();


};


#endif //PROYECTO1ARQUIII_CACHE_CONTROLLER_H
