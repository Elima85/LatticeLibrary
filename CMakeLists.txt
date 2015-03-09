cmake_minimum_required(VERSION 2.8.4)
project(dist)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(GTEST_ROOT "${PROJECT_SOURCE_DIR}/googletest")

set(SOURCE_FILES
    image.h
    binaryimage.h
    binaryimage.cpp
    crispsegmentationimage.h
    crispsegmentationimage.cpp
    intensityimage.h
    distanceimage.h
    distanceimage.cpp
    fuzzysegmentationimage.h
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
    imagetestinitialization.cpp
    imagetestcoordinates.cpp
    imagetestbands.cpp
    imagetestneighbors.cpp
    imagetestmanipulation.cpp
    intensityimagetest.cpp
    distanceimagetest.cpp
    seededdistancetransformtest.cpp
    latticelibtest.cpp
    )

include_directories(
    "${GTEST_ROOT}"
    "${GTEST_ROOT}/include"
)

add_executable(release ${MAIN_SOURCE_FILES})
add_executable(testing ${TEST_SOURCE_FILES})

target_link_libraries(
    testing
    pthread
)