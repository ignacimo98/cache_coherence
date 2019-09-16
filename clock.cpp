//
// Created by Ignacio Mora on 2019-08-21.
//

#include "clock.h"

#include <thread>
#include <chrono>

void Clock::tick() {
    *clk = !*clk;
}

Clock::Clock(bool* clk) {
    this->clk = clk;

}

void Clock::startTicking() {
    ticking = true;
    while (ticking){
        tick();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

void Clock::stopTicking() {
    ticking = false;
}




