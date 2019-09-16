//
// Created by Ignacio Mora on 2019-09-11.
//

#include <iostream>
#include <thread>
#include <fstream>
#include <sstream>
#include "cache_controller.h"

CacheController::CacheController(CacheBus *cache_bus, int num_core, Memory* memory):cache(num_core) {
    this->bus = cache_bus;
    this->num_core = num_core;
    this->memory = memory;

}



int CacheController::readData(int address) {
    int block = address % 8;
    int tag = address / 8;

    if (cache.getTag(block) == tag){
        if (cache.getStatus(block) == INVALID){


            Bus request;
            request.action = ReadMiss;
            request.memory_address = address;
            request.controller_num = num_core;
            request.data = 0;
            request.controller_reads[num_core] = true;
            request.ticks = 0;
            bus->new_request(request);
            cache.setStatus(block, SHARED);
            waiting_for_response = true;
            auto start = std::chrono::steady_clock::now();
            while (waiting_for_response){
                auto now = std::chrono::steady_clock::now();
                if (std::chrono::duration_cast<std::chrono::seconds>(now - start).count() > 5){
                    waiting_for_response = false;
                    cache.setData(block, memory->read(address));
                }
            }
            if (sent_by_mem){

                std::this_thread::sleep_for(std::chrono::milliseconds(5000));
                sent_by_mem = false;
            }
            return cache.getData(block);
        }
        if (cache.getStatus(block) == SHARED or cache.getStatus(block) == MODIFIED){

            return cache.getData(block);
        }

    } else{

        if (cache.getStatus(block) == INVALID or cache.getStatus(block) == SHARED){
            Bus request;
            request.action = ReadMiss;
            request.memory_address = address;
            request.controller_num = num_core;
            request.controller_reads[num_core] = true;
            request.ticks = 0;
            bus->new_request(request);
            cache.setStatus(block, SHARED);
            waiting_for_response = true;
            auto start = std::chrono::steady_clock::now();
            while (waiting_for_response){
                auto now = std::chrono::steady_clock::now();
                if (std::chrono::duration_cast<std::chrono::seconds>(now - start).count() > 5){
                    waiting_for_response = false;
                    cache.setData(block, memory->read(address));
                }
            }
            if (sent_by_mem){
                std::this_thread::sleep_for(std::chrono::milliseconds(5000));
                sent_by_mem = false;
            }
            return cache.getData(block);
        }
        if (cache.getStatus(block) == MODIFIED){
            Bus wb_request;
            wb_request.data = cache.getData(block);
            wb_request.action = WriteBack;
            wb_request.memory_address = block + cache.getTag(block)*8;
            wb_request.controller_reads[num_core] = true;
            std::cout << "Controller " << num_core << " is writing back " << wb_request.data << std::endl;

//            std::this_thread::sleep_for(std::chrono::milliseconds(5000));
            bus->new_request(wb_request);

            Bus request;
            request.action = ReadMiss;
            request.memory_address = address;
            request.controller_num = num_core;
            request.controller_reads[num_core] = true;
            request.ticks = 0;
            bus->new_request(request);
            cache.setStatus(block, SHARED);
            waiting_for_response = true;
            auto start = std::chrono::steady_clock::now();
            while (waiting_for_response){
                auto now = std::chrono::steady_clock::now();
                if (std::chrono::duration_cast<std::chrono::seconds>(now - start).count() > 5){
                    waiting_for_response = false;
                    cache.setData(block, memory->read(address));
                }
            }
            if (sent_by_mem){

                std::this_thread::sleep_for(std::chrono::milliseconds(5000));
                sent_by_mem = false;
            }
            return cache.getData(block);
        }

    }

    return 0;
}

void CacheController::writeData(int address, int data) {
    int block = address % 8;
    int tag = address / 8;

    if (cache.getTag(block) == tag){
        if (cache.getStatus(block) == MODIFIED){
            cache.setData(block, data);
        }
        if (cache.getStatus(block) == INVALID){
            Bus request;
            request.memory_address = address;
            request.action = WriteMiss;
            request.controller_num = num_core;
            request.controller_reads[num_core] = true;
            bus->new_request(request);
            cache.setBlock(block, MODIFIED, tag, data);
        }
        if (cache.getStatus(block) == SHARED){
            Bus request;
            request.memory_address = address;
            request.action = Invalidate;
            request.controller_num = num_core;
            request.controller_reads[num_core] = true;
            bus->new_request(request);
            cache.setBlock(block, MODIFIED, tag, data);
        }
    } else {
        if (cache.getStatus(block) == MODIFIED){
            Bus wb_request;
            wb_request.data = cache.getData(block);
            wb_request.action = WriteBack;
            wb_request.memory_address = block + cache.getTag(block)*8;
            wb_request.controller_reads[num_core] = true;
            std::cout << "Controller " << num_core << " is writing back " << wb_request.data << std::endl;
//            std::this_thread::sleep_for(std::chrono::milliseconds(5000));
            bus->new_request(wb_request);

            Bus request;
            request.controller_reads[num_core] = true;
            request.controller_num = num_core;
            request.action = WriteMiss;
            request.memory_address = address;
            cache.setBlock(block, MODIFIED, tag, data);
            bus->new_request(request);

        }
        if (cache.getStatus(block) == INVALID){
            Bus request;
            request.memory_address = address;
            request.action = WriteMiss;
            request.controller_num = num_core;
            request.controller_reads[num_core] = true;
            bus->new_request(request);
            cache.setBlock(block, MODIFIED, tag, data);
        }
        if (cache.getStatus(block) == SHARED){
            Bus request;
            request.memory_address = address;
            request.action = WriteMiss;
            request.controller_num = num_core;
            request.controller_reads[num_core] = true;
            bus->new_request(request);
            cache.setBlock(block, MODIFIED, tag, data);
        }
    }


}

void CacheController::checkBus() {

    if (not bus->is_request_bus_empty()){
        if (not bus->get_seen_by(num_core)){
            bus->set_seen_request(num_core);
            Bus current_request = bus->peek_request_bus();
            int block = current_request.memory_address % 8;
            int tag = current_request.memory_address / 8;
            if (current_request.action == ReadMiss){
                if (cache.getTag(block) == tag) {
                    if (cache.getStatus(block) == SHARED){
                        Bus response;
                        response.data = cache.getData(block);
                        response.memory_address = current_request.memory_address;
                        response.controller_num = current_request.controller_num;
                        response.controller_reads[num_core] = true;
                        response.action = ReadHit;
                        bus->new_response(response);
                        bus->pop_request_bus();
                    } else if (cache.getStatus(block) == MODIFIED){
                        Bus wb_request;
                        wb_request.data = cache.getData(block);
                        wb_request.action = WriteBack;
                        wb_request.memory_address = current_request.memory_address;
                        wb_request.controller_reads[num_core] = true;
                        std::cout << "Controller " << num_core << " is writing back " << wb_request.data << std::endl;
//                        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
                        bus->new_request(wb_request);

                        Bus response;
                        response.data = cache.getData(block);
                        response.memory_address = current_request.memory_address;
                        response.controller_num = current_request.controller_num;
                        response.controller_reads[num_core] = true;
                        response.action = ReadHit;
                        cache.setStatus(block, SHARED);
                        bus->new_response(response);
                        bus->pop_request_bus();

                    } else {
                        bus->dismiss_request_bus();
                    }
                } else{
                    bus->dismiss_request_bus();
                }

            } else if (current_request.action == Invalidate){
                if (cache.getTag(block) == tag){
                    cache.setStatus(block, INVALID);
                }
                bus->dismiss_request_bus();

            } else if (current_request.action == WriteMiss) {
                if (cache.getTag(block) == tag){
                    if(cache.getStatus(block) == SHARED){
                        cache.setStatus(block, INVALID);
                    }
                    if (cache.getStatus(block) == MODIFIED){
                        Bus request;
                        request.action = WriteBack;
                        request.controller_num = num_core;
                        request.controller_reads[num_core] = true;
                        request.data = cache.getData(block);
                        request.memory_address = current_request.memory_address;
                        std::cout << "Controller " << num_core << " is writing back " << request.data << std::endl;
                        cache.setStatus(block, INVALID);
                        bus->new_request(request);



                    }
                }
                bus->dismiss_request_bus();


            } else {
                bus->dismiss_request_bus();
            }

        } else {
            bus->dismiss_request_bus();
        }

    } else {
        bus->dismiss_request_bus();
    }




    if (not bus->is_response_bus_empty()){
        Bus response = bus->peek_response_bus();
        int block = response.memory_address % 8;
        int tag = response.memory_address / 8;
        if (response.controller_num == num_core){
            bus->pop_response_bus();
            cache.setData(block, response.data);
            cache.setTag(block, tag);
            waiting_for_response = false;
            sent_by_mem = response.controller_reads[0] and response.controller_reads[1] and response.controller_reads[2] and response.controller_reads[3];
        } else{
            bus->dismiss_response_bus();
        }
    } else{
        bus->dismiss_response_bus();
    }

}

void CacheController::startCheckingBus() {
    running = true;
    while (running){
        checkBus();
    }

}
