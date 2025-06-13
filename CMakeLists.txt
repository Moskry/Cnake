cmake_minimum_required(VERSION 3.10)
project(CNake)

set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(HDR_DIR "${CMAKE_SOURCE_DIR}/hdr")

file(GLOB_RECURSE SOURCES "${SRC_DIR}/*.c")
file(GLOB_RECURSE HEADERS "${HDR_DIR}/*.h")
message(STATUS "Headers found: ${HEADERS}")

add_executable(CNake ${SOURCES} ${HEADERS})

target_include_directories(CNake PRIVATE ${HDR_DIR})