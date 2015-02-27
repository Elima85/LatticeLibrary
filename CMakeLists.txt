cmake_minimum_required(VERSION 2.8.4)
project(dist)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(GTEST_ROOT "${PROJECT_SOURCE_DIR}/googletest")

set(SOURCE_FILES
    cimage.h
    binarycimage.h
    binarycimage.cpp
    crispsegmentationcimage.h
    crispsegmentationcimage.cpp
    intensitycimage.h
    distancecimage.h
    distancecimage.cpp
    fuzzysegmentationcimage.h
    defs.h
    exception.h
    filehandling.cpp
    filehandling.h
    filter.h
    seed.h
    seed.cpp
    seededdistancetransform.h
    label.h
    miscellaneous.cpp
    miscellaneous.h
    neighbor.h
    neighbor.cpp
    norm.h
    priorityqueue.h
    vectoroperators.h
    lattice.h
    lattice.cpp
    cclattice.h
    cclattice.cpp
    bcclattice.h
    bcclattice.cpp
    fcclattice.h
    fcclattice.cpp
    )

set(MAIN_SOURCE_FILES
    ${SOURCE_FILES}
    main.cpp
    )

set(TEST_SOURCE_FILES
    ${SOURCE_FILES}
    ${GTEST_ROOT}/src/gtest-all.cc
    filetest.cpp
    cclatticetestinitialization.cpp
    cclatticetestcoordinates.cpp
    cclatticetestneighbors.cpp
    bcclatticetestinitialization.cpp
    bcclatticetestcoordinates.cpp
    bcclatticetestneighbors.cpp
    fcclatticetestinitialization.cpp
    fcclatticetestcoordinates.cpp
    fcclatticetestneighbors.cpp
    misctest.cpp
    neighbortest.cpp
    normtest.cpp
    priorityqueuetest.cpp
    cimagetestinitialization.cpp
    cimagetestcoordinates.cpp
    cimagetestbands.cpp
    cimagetestneighbors.cpp
    cimagetestmanipulation.cpp
    intensitycimagetest.cpp
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