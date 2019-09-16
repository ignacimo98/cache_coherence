//
// Created by Ignacio Mora on 2019-08-21.
//

#ifndef PROYECTO1ARQUIII_CLOCK_H
#define PROYECTO1ARQUIII_CLOCK_H



class Clock {
public:
    Clock(bool* clk);
    void tick();
    void startTicking();
    void stopTicking();

private:
    bool* clk;
    bool ticking;
};


#endif //PROYECTO1ARQUIII_CLOCK_H
