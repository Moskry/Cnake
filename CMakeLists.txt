cmake_minimum_required(VERSION 3.10)
project(CNake)

include_directories(hdr)
file(GLOB SOURCE_FILES "src/*.c")

add_executable(CNake ${SOURCE_FILES})