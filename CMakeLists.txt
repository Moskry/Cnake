cmake_minimum_required(VERSION 3.10)
project(CNake)

set(OSBitness 32)
if(CMAKE_SIZEOF_VOID_P EQUAL 64)
    set (OSBitness 64)
endif()
set(FullOutputDir "${CMAKE_SOURCE_DIR}/bin/${CMAKE_SYSTEM_NAME}${OSBitness}/${CMAKE_BUILD_TYPE}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${FullOutputDir}/static_libs")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${FullOutputDir}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${FullOutputDir}")

if(WIN32)
    set(CMAKE_PREFIX_PATH "C:/msys64/mingw64")
endif()

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})

include_directories(.)
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(HDR_DIR "${CMAKE_SOURCE_DIR}/hdr")

file(GLOB_RECURSE SOURCES "${SRC_DIR}/*.c")
file(GLOB_RECURSE HEADERS "${HDR_DIR}/*.h")
message(STATUS "Headers found: ${HEADERS}")

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PRIVATE ${HDR_DIR})

target_link_libraries(${PROJECT_NAME} ${GLUT_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES})

if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_PREFIX_PATH}/bin/libfreeglut.dll"
        "${CMAKE_PREFIX_PATH}/bin/glew32.dll"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
endif()

#add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy_directory
#    ${CMAKE_SOURCE_DIR}/shaders $<TARGET_FILE_DIR:${PROJECT_NAME}>/shaders
#)

message(STATUS "Build Output Directory: ${FullOutputDir}")
message(STATUS "OpenGL includes: ${OPENGL_INCLUDE_DIRS}")
message(STATUS "GLUT includes: ${GLUT_INCLUDE_DIRS}")