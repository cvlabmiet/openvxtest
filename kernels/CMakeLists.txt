file(GLOB SRCS src/*.c src/*.cpp)
add_library(kernels ${SRCS})
target_include_directories(kernels PUBLIC include)
