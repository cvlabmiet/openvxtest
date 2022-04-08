cmake_minimum_required(VERSION 3.15)
project(openvxtest LANGUAGES CXX C VERSION 0.3.0 DESCRIPTION "Training project on openvx implementation")

set(CMAKE_CXX_STANDARD 17)
if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

add_subdirectory(demo)
add_subdirectory(kernels)
