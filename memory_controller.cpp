//
// Created by Ignacio Mora on 2019-09-14.
//

#include <iostream>
#include "memory_controller.h"

MemoryController::MemoryController(CacheBus *cache_bus, bool *clk, Memory *memory) {
    this->cache_bus = cache_bus;
    this->clk = clk;
    this->memory = memory;
    this->running = false;
    last_clk_state = *clk;

}

void MemoryController::startCheckingBus() {
    running = true;
    while(running){
        checkBus();
    }
}

void MemoryController::checkBus() {
    if (not cache_bus->is_request_bus_empty()){
        Bus current_request = cache_bus->peek_request_bus();
        if (current_request.action == WriteBack){
            cache_bus->pop_request_bus();
            memory->write(current_request.memory_address, current_request.data);
        } else if (cache_bus->request_seen_by_everyone()){
            cache_bus->pop_request_bus();
            if (current_request.action == ReadMiss){
                Bus response;
                response.action = ReadHit;
                response.data = memory->read(current_request.memory_address);
                response.memory_address = current_request.memory_address;
                response.controller_num = current_request.controller_num;
                response.controller_reads[0] = true;
                response.controller_reads[1] = true;
                response.controller_reads[2] = true;
                response.controller_reads[3] = true;
                cache_bus->new_response(response);
            }
        } else{
            cache_bus->dismiss_request_bus();
        }

    } else {
        cache_bus->dismiss_request_bus();
    }

}
