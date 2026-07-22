cmake_minimum_required(VERSION 3.28)
project(OdelTouring CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) 

add_executable(odelTouring 
    main.cpp 
    Person.cpp 
    Customer.cpp
    Manager.cpp
    Trip.cpp 
    Functions.cpp 
)
