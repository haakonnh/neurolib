cmake_minimum_required(VERSION 3.12)

project(neurolib)

set(SOURCE_FILES
    src/neurolib.cpp
    src/neurolib.hpp
)

add_library(neurolib STATIC ${SOURCE_FILES})

target_include_directories(neurolib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(example main.cpp)


# Link against the necessary libraries
target_link_libraries(example PRIVATE neurolib -static-libgcc -static-libstdc++ -static -lmingw32 -lmingwex -lkernel32 -pthread)
