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


add_library(CustomerManagerTrip)
target_sources(CustomerManagerTrip
    PUBLIC FILE_SET CXX_MODULES FILES
        CustomerManagerTrip.cppm
        Customer.cppm
        Manager.cppm
        Trip.cppm
)


target_link_libraries(CustomerManagerTrip PUBLIC Person)


add_executable(odelTouring)
target_sources(odelTouring
    PRIVATE
        main.cpp 
        Functions.cpp    
)

target_link_libraries(odelTouring PRIVATE CustomerManagerTrip)




