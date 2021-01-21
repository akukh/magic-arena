cmake_minimum_required(VERSION 3.11 FATAL_ERROR) 

project(magic_arena)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")

set(SOURCE_DIR  "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(PUBLIC_DIR  "${SOURCE_DIR}/public")
set(PRIVATE_DIR "${SOURCE_DIR}/private")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

file(GLOB SOURCES "${SOURCE_DIR}/*.cpp" "${PRIVATE_DIR}/*.cpp")
file(GLOB HEADERS "${PUBLIC_DIR}/*.hpp")

add_executable(magic_arena ${SOURCES} ${HEADERS})
target_include_directories(magic_arena PRIVATE "src/public")
