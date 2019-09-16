#include <iostream>
#include <thread>
#include <random>

#include "include/random.hpp"
#include "clock.h"
#include "memory.h"
#include "core.h"
#include "processor.h"
#include "program.h"

using Random = effolkronium::random_static;

const int num_cores = 4;

int main(int argc, char *argv[]) {
    bool clk = false;
    Clock clock(&clk);

    Program *program;

    int dist_num = 0;
    float parameter = 0;


    std::cout << "Welcome to the magic processor!" << std::endl;
    if (argc == 1) {
        std::cout
                << "No probability distribution specified for the program generation, the default distribution will be used [UNIFORM]."
                << std::endl;
    } else if (argc == 2) {
        if (std::string(argv[1]) == "-h" or std::string(argv[1]) == "--help") {
            //TODO Instruction Manual
            std::cout << "The help is comming." << std::endl;

            return 0;
        } else if (std::string(argv[1]) == "-u" or std::string(argv[1]) == "--uniform") {
            std::cout << "Using a uniform probability distribution for the program generation." << std::endl;
        } else if (std::string(argv[1]) == "-p" or std::string(argv[1]) == "--poisson") {
            std::cout << "Using a Poisson probability distribution for the program generation." << std::endl;
            std::cout << "No mean specified, using the default[1]." << std::endl;
            dist_num = 1;
            parameter = 1.0;

        } else if (std::string(argv[1]) == "-b" or std::string(argv[1]) == "--binomial") {
            std::cout << "Using a Binomial probability distribution for the program generation." << std::endl;
            std::cout << "No probability of success specified, using the default[0.5]." << std::endl;
            dist_num = 2;
            parameter = 0.5;

        } else if (std::string(argv[1]) == "-g" or std::string(argv[1]) == "--geometric") {
            std::cout << "Using a Geometric probability distribution for the program generation." << std::endl;
            std::cout << "No probability of success specified, using the default[0.5]." << std::endl;
            dist_num = 3;
            parameter = 0.5;
        } else {
            std::cout << std::string(argv[1]) << " is not a valid option, ending execution." << std::endl;
            return 0;
        }

    } else if (argc == 3) {
        if (std::string(argv[1]) == "-p" or std::string(argv[1]) == "--poisson") {
            std::cout << "Using a Poisson probability distribution with a mean of "
                      << std::stof(std::string(argv[2])) << " for the program generation." << std::endl;
            dist_num = 1;
            parameter = std::stof(std::string(argv[2]));

        } else if (std::string(argv[1]) == "-b" or std::string(argv[1]) == "--binomial") {
            std::cout << "Using a Binomial probability distribution with a probability of success of "
                      << std::stof(std::string(argv[2])) << " for the program generation." << std::endl;
            dist_num = 2;
            parameter = std::stof(std::string(argv[2]));

        } else if (std::string(argv[1]) == "-g" or std::string(argv[1]) == "--geometric") {
            std::cout << "Using a Geometric probability distribution with a probability of success of "
                      << std::stof(std::string(argv[2])) << " for the program generation." << std::endl;
            dist_num = 3;
            parameter = std::stof(std::string(argv[2]));
        } else {
            std::cout << std::string(argv[1])
                      << " is not a valid option with the specified arguments, ending execution." << std::endl;
            return 0;
        }
    }
    Memory memory;

    Processor proc(&clk, 4, dist_num, parameter, &memory);
    proc.run();


    std::thread thread_clk(&Clock::startTicking, &clock);


    thread_clk.join();

    return 0;
}