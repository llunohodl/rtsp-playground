cmake_minimum_required(VERSION 3.5)

project(rtsp-playground)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11")


set(SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

include_directories(
    ${CMAKE_SOURCE_DIR}/lib/include
    ${CMAKE_SOURCE_DIR}/include
)

link_directories(
    ${CMAKE_SOURCE_DIR}/lib/lib
)

link_libraries(
    avformat
    avcodec 
    swscale 
    swresample
    postproc
    avutil
    x264
    z
    ssl
    crypto
    dl
    stdc++
    pthread
    m
)

add_executable(${PROJECT_NAME} ${SOURCES})	
