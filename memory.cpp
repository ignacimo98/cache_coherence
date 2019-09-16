//
// Created by Ignacio Mora on 2019-08-21.
//


#include "memory.h"

#include <cstdio>
#include <fstream>


void Memory::write(int position, int value) {
    this->memory[position] = value;

    std::ofstream outfile;
    outfile.open("info_for_ui/memory_content.txt", std::ios::out | std::ios::trunc );


    outfile << "[";
    for (int i = 0; i < 15; ++i) {
        outfile << memory[i] << ", ";
    }
    outfile << memory[15] << "]";

    outfile.close();
}

int Memory::read(int position) {
    return memory[position];
}

void Memory::print_memory() {
    printf("[%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d]",
            memory[0], memory[1], memory[2], memory[3],
            memory[4], memory[5], memory[6], memory[7],
            memory[8], memory[9], memory[10], memory[11],
            memory[12], memory[13], memory[14], memory[15]);

}


