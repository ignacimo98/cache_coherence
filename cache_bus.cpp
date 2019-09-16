//
// Created by Ignacio Mora on 2019-09-14.
//

#include "cache_bus.h"

#include <mutex>

std::mutex response_bus_mutex;
std::mutex request_bus_mutex;

Bus CacheBus::peek_request_bus() {
    return request_bus.front();
}
void CacheBus::increment_request_bus_ticks() {
    request_bus.front().ticks++;
}
void CacheBus::new_request(Bus request) {
    request_bus.push(request);
}

void CacheBus::pop_request_bus() {
    request_bus.pop();
    request_bus_mutex.unlock();
}

void CacheBus::new_response(Bus response) {
    response_bus.push(response);
}

Bus CacheBus::peek_response_bus() {
    return response_bus.front();
}

void CacheBus::pop_response_bus() {

    response_bus.pop();
    response_bus_mutex.unlock();
}

void CacheBus::dismiss_response_bus() {
    response_bus_mutex.unlock();
}

bool CacheBus::is_request_bus_empty() {
    request_bus_mutex.lock();
    return request_bus.empty();
}

bool CacheBus::is_response_bus_empty() {
    response_bus_mutex.lock();
    return response_bus.empty();
}

void CacheBus::dismiss_request_bus() {
    request_bus_mutex.unlock();
}

void CacheBus::set_seen_request(int num_controller) {
    request_bus.front().controller_reads[num_controller] = true;
}

bool CacheBus::request_seen_by_everyone() {
    return (request_bus.front().controller_reads[0] and request_bus.front().controller_reads[1] and
            request_bus.front().controller_reads[1] and request_bus.front().controller_reads[3]);
}



bool CacheBus::get_seen_by(int num_controller) {
    if (not request_bus.empty())
        return request_bus.front().controller_reads[num_controller];
    else
        return true;
}




