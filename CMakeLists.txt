cmake_minimum_required(VERSION 3.30.5)
project(Heartbeat C)

set(CMAKE_C_STANDARD 11)


add_library(heartbeat SHARED lib/heartbeat.c lib/client.c lib/server.c
        lib/heartbeat.h lib/socket.h
        lib/telegram/telegram.c
        lib/telegram/telegram.h)


add_executable(server server.c)
add_executable(client client.c)

add_custom_target(all_targets ALL
        DEPENDS heartbeat server client
)

if(WIN32)
    target_link_libraries(heartbeat PRIVATE ws2_32)
    target_link_libraries(heartbeat PRIVATE ws2_32 Rpcrt4)
    target_link_libraries(client PRIVATE ws2_32 Rpcrt4)
    target_link_libraries(heartbeat PRIVATE winhttp)
else ()
    find_package(CURL REQUIRED)
    find_library(UUID_LIB uuid REQUIRED)

    target_link_libraries(heartbeat
            PRIVATE
            CURL::libcurl
            ${UUID_LIB}
    )

    target_link_libraries(client
            PRIVATE
            CURL::libcurl
            ${UUID_LIB}
    )



endif()

target_link_libraries(server PRIVATE heartbeat)
target_link_libraries(client PRIVATE heartbeat)