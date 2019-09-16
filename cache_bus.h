//
// Created by Ignacio Mora on 2019-09-14.
//

#ifndef PROYECTO1ARQUIII_CACHE_BUS_H
#define PROYECTO1ARQUIII_CACHE_BUS_H

#include <queue>


enum Action {WriteMiss, ReadMiss, Invalidate, ReadHit, WriteBack};

typedef struct {
    Action action;
    int controller_num;
    int memory_address;
    int data;
    int ticks = 0;
    bool controller_reads[4] = {false, false, false, false};
} Bus;

class CacheBus {
public:
    std::queue<Bus> response_bus;
    std::queue<Bus> request_bus;

    bool is_request_bus_empty();
    Bus peek_request_bus();
    void increment_request_bus_ticks();
    void new_request(Bus request);
    void pop_request_bus();
    void dismiss_request_bus();
    void set_seen_request(int num_controller);
    bool get_seen_by(int num_controller);
    bool request_seen_by_everyone();

    bool is_response_bus_empty();
    void new_response(Bus response);
    Bus peek_response_bus();
    void pop_response_bus();
    void dismiss_response_bus();



};


#endif //PROYECTO1ARQUIII_CACHE_BUS_H
