cmake_minimum_required(VERSION 2.8.4)
project(dist)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(GTEST_ROOT "${PROJECT_SOURCE_DIR}/googletest")

set(SOURCE_FILES
    cimage.h
    cimageBCC.h
    cimageCC.h
    cimageFCC.h
    defs.h
    exception.h
    filehandling.cpp
    filehandling.h
    filter.h
    label.h
    miscellaneous.cpp
    miscellaneous.h
    neighbor.h
    norm.h
    priorityqueue.h
    vectoroperators.h
    )

set(MAIN_SOURCE_FILES
    ${SOURCE_FILES}
    main.cpp
    )

set(TEST_SOURCE_FILES
    ${SOURCE_FILES}
    ${GTEST_ROOT}/src/gtest-all.cc
    filetest.cpp
    imagebcctest.cpp
    imagecctest.cpp
    imagefcctest.cpp
    misctest.cpp
    neighbortest.cpp
    normtest.cpp
    priorityqueuetest.cpp
    test.cpp
    )

include_directories(
    "${GTEST_ROOT}"
    "${GTEST_ROOT}/include"
)

add_executable(dist ${MAIN_SOURCE_FILES})
add_executable(test ${TEST_SOURCE_FILES})

target_link_libraries(
    test
    pthread
)