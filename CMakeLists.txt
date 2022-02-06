cmake_minimum_required(VERSION 3.21)
project(PropertyMP C)

set(CMAKE_C_STANDARD 11)

add_executable(PropertyMP
        Property_Property.c)
        
target_link_libraries(PropertyMP m)
        
