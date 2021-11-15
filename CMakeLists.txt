cmake_minimum_required(VERSION 3.20)
project(SAT)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        main.cpp
        src/sat.cpp
        src/collision_result.cpp)

add_executable(SAT ${SOURCE_FILES})

target_include_directories(SAT PRIVATE include)

add_subdirectory(lib/glm)
target_link_libraries(SAT glm)