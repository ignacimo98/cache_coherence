//
// Created by Ignacio Mora on 2019-09-12.
//

#include "program.h"


Program::Program(int distribution, float parameter) {
    this->dist_number = distribution;

    this->uniform_dist = std::uniform_int_distribution(0,2);
    this->poisson_dist = std::poisson_distribution(parameter);
    this->geometric_dist = std::geometric_distribution(parameter);
    this->binomial_dist = std::binomial_distribution(2, parameter);
}

Instruction Program::getInstruction() {

    Instruction to_return;
    int random_int = 0;
    if (dist_number == 0){
        random_int = Random::get(uniform_dist);
    } else if(dist_number == 1){
        random_int = Random::get(poisson_dist);
    } else if (dist_number == 2){
        random_int = Random::get(geometric_dist);
    } else{
        random_int = Random::get(binomial_dist);
    }

    if (random_int%3 == 0){
        to_return.type = EXE;
        to_return.address = 0;
    } else if (random_int%3 == 1){
        to_return.type = READ;
        to_return.address = Random::get()%16;
    } else {
        to_return.type = STORE;
        to_return.address = Random::get()%16;
    }

    return to_return;
}


