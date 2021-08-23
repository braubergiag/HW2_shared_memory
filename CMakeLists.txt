cmake_minimum_required(VERSION 3.19)
project(shared_mem C)
find_library(LIBRT rt)

set(CMAKE_C_STANDARD 11)

add_executable(sender sender.c protocol.h )
add_executable(reciever reciever.c protocol.h )
#add_executable(request request.c  protocol.h )
#add_executable(worker worker.c  protocol.h )
if (LIBRT)
    target_link_libraries(sender  ${LIBRT})
    target_link_libraries(reciever  ${LIBRT})

endif()