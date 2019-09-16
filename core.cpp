//
// Created by Ignacio Mora on 2019-09-11.
//

#include <iostream>
#include <sstream>
#include <fstream>
#include "core.h"


Core::Core(bool* clk, int num_core, Program* program, CacheBus* cache_bus, Memory* memory) {
    this->program = program;
    running = false;
    this->clk = clk;
    last_clk_state = *clk;

    this->num_core = num_core;
    this->cache_controller = new CacheController(cache_bus, num_core, memory);
}


void Core::run() {
    running = true;
    std::thread bus_checker(&CacheController::startCheckingBus, cache_controller);
    while (running){

        if (last_clk_state != *clk){
            last_clk_state = *clk;
            std::stringstream fmt;
            Instruction cycle_instruction = program->getInstruction();
            if (cycle_instruction.type == STORE){
                std::ofstream outfile;
                std::stringstream fmt_filename;
                fmt_filename << "info_for_ui/cache" << num_core<< "_info.txt";
                outfile.open(fmt_filename.str(), std::ios::out | std::ios::trunc );
                outfile << "Writing " << num_core+1 << " to address " << cycle_instruction.address;
                outfile.close();


                cache_controller->writeData(cycle_instruction.address, num_core+1);


                fmt << "Core " << num_core << " wrote to address " << cycle_instruction.address << "\n";
                std::cout << fmt.str();


            } else if (cycle_instruction.type == READ){
                std::ofstream outfile;
                std::stringstream fmt_filename;
                fmt_filename << "info_for_ui/cache" << num_core<< "_info.txt";
                outfile.open(fmt_filename.str(), std::ios::out | std::ios::trunc );
                outfile << "Reading from address " << cycle_instruction.address;
                outfile.close();

                int read = cache_controller->readData(cycle_instruction.address);

                outfile.open(fmt_filename.str(), std::ios::out | std::ios::trunc );
                outfile << "Read " << read << " from address " << cycle_instruction.address;
                outfile.close();

                fmt << "Core " << num_core << " read "<< read << " from address " << cycle_instruction.address << "\n";
                std::cout << fmt.str();

            } else{
                std::ofstream outfile;
                std::stringstream fmt_filename;
                fmt_filename << "info_for_ui/cache" << num_core<< "_info.txt";
                outfile.open(fmt_filename.str(), std::ios::out | std::ios::trunc );
                outfile << "Got an execution instruction";
                outfile.close();

                std::cout << fmt.str();

            }


//            fmt << "Core " << num_core << " got " << cycle_instruction.type << "with address"<< cycle_instruction.address <<"\n";


            /// do some magic and run





        }
    }

}
