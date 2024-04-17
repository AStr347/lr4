cmake_minimum_required(VERSION 2.8)

project(mpi CXX)

# set Release/Debug dir place
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "..")
# set flags
set(CMAKE_CXX_COMPILE_FLAGS ${CMAKE_CXX_COMPILE_FLAGS} ${MPI_COMPILE_FLAGS})
set(CMAKE_CXX_LINK_FLAGS ${CMAKE_CXX_LINK_FLAGS} ${MPI_LINK_FLAGS})

set(SOURCEDIR ${PROJECT_SOURCE_DIR}/src)
# global include dirs
include_directories(${SOURCEDIR}/include)

# Require MPI for this project:
find_package(MPI REQUIRED)
# hello world build
add_executable(hello ${SOURCEDIR}/hello.cpp)
target_include_directories(hello PUBLIC ${MPI_INCLUDE_PATH})
target_link_libraries(hello PUBLIC ${MPI_LIBRARIES})

# lr4 build
add_executable(lr4 ${SOURCEDIR}/lr4.cpp)
target_include_directories(lr4 PUBLIC ${MPI_INCLUDE_PATH})
target_link_libraries(lr4 PUBLIC ${MPI_LIBRARIES})