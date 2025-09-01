cmake_minimum_required(VERSION 4.0)
project(Heartbeat C)

set(CMAKE_C_STANDARD 11)


add_library(heartbeat SHARED lib/heartbeat.c lib/client.c lib/server.c
        lib/heartbeat.h lib/socket.h)


add_executable(server server.c)
add_executable(client client.c)

add_custom_target(all_targets ALL
        DEPENDS heartbeat server client
)

if(WIN32)
    target_link_libraries(heartbeat PRIVATE ws2_32)
endif()

target_link_libraries(server PRIVATE heartbeat)
target_link_libraries(client PRIVATE heartbeat)