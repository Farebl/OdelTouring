cmake_minimum_required(VERSION 3.28)
project(OdelTouring CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(Person)
target_sources(Person
    PUBLIC FILE_SET CXX_MODULES FILES
        Person.cppm
)


add_library(Customer)
target_sources(Customer
    PUBLIC FILE_SET CXX_MODULES FILES
        Customer.cppm
)

target_link_libraries(Customer PUBLIC Person)



add_executable(odelTouring)
target_sources(odelTouring
    PRIVATE
        main.cpp 
        Manager.cpp
        Trip.cpp 
        Functions.cpp    
)

target_link_libraries(odelTouring PRIVATE Customer)



