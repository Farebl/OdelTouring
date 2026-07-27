cmake_minimum_required(VERSION 3.30)
project(OdelTouring CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Person module
add_library(Person)
target_sources(Person
    PUBLIC FILE_SET CXX_MODULES FILES
        Person.cppm
)


# (Customer + Manager + Trip) module
add_library(CustomerManagerTrip)
target_sources(CustomerManagerTrip
    PUBLIC FILE_SET CXX_MODULES FILES
        CustomerManagerTrip.cppm
        Customer.cppm
        Manager.cppm
        Trip.cppm
)


target_link_libraries(CustomerManagerTrip PUBLIC Person)



# Order module
add_library(Order)
target_sources(Order
    PUBLIC FILE_SET CXX_MODULES FILES
        Order.cppm
)


# (Termanil-GUI + Queries functions) module
add_library(Functions)
target_sources(Functions
    PUBLIC
        FILE_SET CXX_MODULES FILES
            Functions.cppm
            Interface.cppm
            QueryFunctions.cppm

PRIVATE
        QueryFunctions.cpp
)


target_link_libraries(Functions PRIVATE CustomerManagerTrip)
target_link_libraries(Functions PRIVATE Order)


add_executable(odelTouring main.cpp)

target_link_libraries(odelTouring PRIVATE Functions)



