//
// Created by Ignacio Mora on 2019-09-12.
//

#ifndef PROYECTO1ARQUIII_PROGRAM_H
#define PROYECTO1ARQUIII_PROGRAM_H


#include <random>
#include "include/random.hpp"

using Random = effolkronium::random_static;

enum InstructionType{EXE = 0, READ = 1, STORE = 2};

typedef struct {
    InstructionType type;
    int address;
    } Instruction;

class Program {
private:
    int dist_number;
    std::uniform_int_distribution<int> uniform_dist;
    std::poisson_distribution<int> poisson_dist;
    std::geometric_distribution<int> geometric_dist;
    std::binomial_distribution<int> binomial_dist;




public:
    Program(int distribution, float parameter);
    Instruction getInstruction();


};


#endif //PROYECTO1ARQUIII_PROGRAM_H
