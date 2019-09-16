cmake_minimum_required(VERSION 3.14)
project(Proyecto1ArquiII)

set(CMAKE_CXX_STANDARD 17)

add_executable(Proyecto1ArquiII main.cpp memory.cpp memory.h clock.cpp clock.h cache_controller.cpp cache_controller.h core.cpp core.h cache.cpp cache.h include/random.hpp program.cpp program.h processor.cpp processor.h cache_bus.cpp cache_bus.h memory_controller.cpp memory_controller.h)