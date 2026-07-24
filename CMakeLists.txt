cmake_minimum_required(VERSION 3.28)
project(OdelTouring CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(odelTouring)


target_sources(odelTouring
    PRIVATE
        main.cpp 
        Customer.cpp
        Manager.cpp
        Trip.cpp 
        Functions.cpp    
  
    PRIVATE FILE_SET CXX_MODULES FILES
        Person.cppm
)
