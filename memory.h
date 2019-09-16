//
// Created by Ignacio Mora on 2019-08-21.
//

#ifndef PROYECTO1ARQUIII_MEMORY_H
#define PROYECTO1ARQUIII_MEMORY_H


class Memory {
private:
    int memory[16] = {};
public:

    int read(int position);
    void write(int position, int value);
    void print_memory();
};


#endif //PROYECTO1ARQUIII_MEMORY_H
