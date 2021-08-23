cmake_minimum_required(VERSION 3.19)
project(shared_mem C)
find_library(LIBRT rt)

set(CMAKE_C_STANDARD 11)

add_executable(producer Producer.c shmbuf.h)
add_executable(consumer Consumer.c shmbuf.h)

if (LIBRT)
    target_link_libraries(producer  ${LIBRT})
    target_link_libraries(consumer  ${LIBRT})

endif()