cmake_minimum_required(VERSION 3.30)
project(OdelTouring CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Person module
add_library(Person)
target_sources(Person
    PUBLIC FILE_SET CXX_MODULES FILES
        Person.cppm
)

# Order module
add_library(Order)
target_sources(Order
    PUBLIC FILE_SET CXX_MODULES FILES
        Order.cppm
)


# (Customer + Manager + Trip) module
add_library(CustomerManagerTrip)
target_sources(CustomerManagerTrip
    PUBLIC FILE_SET CXX_MODULES FILES
        CustomerManagerTrip.cppm
        Customer.cppm
        Manager.cppm
        Trip.cppm 
    PRIVATE
        Manager.cpp
        Customer.cpp
        Trip.cpp
)

target_link_libraries(CustomerManagerTrip PUBLIC Person)
target_link_libraries(CustomerManagerTrip PUBLIC Order)



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
        Interface.cpp
)

target_link_libraries(Functions PRIVATE CustomerManagerTrip Order)

include(FetchContent)
FetchContent_Declare(
  json
  URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
)
FetchContent_MakeAvailable(json)


option(TEST_INTERFACE "Enable new interface testing" OFF)

if(TEST_INTERFACE)
    target_compile_definitions(Functions PRIVATE TEST_NEW_...)
    
    add_executable(test test.cpp)
    target_link_libraries(test PRIVATE Functions)

    option(USE_SANITIZERS "Enable Address and Undefined behavior sanitizers" OFF)
    if(USE_SANITIZERS)
        target_compile_options(test PRIVATE -fsanitize=address,undefined -fno-omit-frame-pointer)
        target_link_options(test PRIVATE -fsanitize=address,undefined)
        target_link_libraries(test PRIVATE nlohmann_json::nlohmann_json)
    endif()
else()
    add_executable(odelTouring main.cpp)
    target_link_libraries(odelTouring PRIVATE Functions)
    target_link_libraries(odelTouring PRIVATE nlohmann_json::nlohmann_json)
endif()









