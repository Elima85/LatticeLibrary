cmake_minimum_required(VERSION 2.8.4)
project(latticelibrary)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(GTEST_ROOT "${PROJECT_SOURCE_DIR}/googletest")

set(SOURCE_FILES
    approximateminimumbarrierdistance.h
    arrayadjustment.h
    bcclattice.cpp
    bcclattice.h
    cclattice.cpp
    cclattice.h
    defs.h
    exception.h
    fcclattice.cpp
    fcclattice.h
    filehandling.cpp
    filehandling.h
    filter.h
    filtercoefficient.h
    fuzzyconnectedness.h
    image.h
    intensityworkset.h
    lattice.cpp
    lattice.h
    neighbor.cpp
    neighbor.h
    norm.h
    priorityqueue.h
    seed.cpp
    seed.h
    seededdistancemeasure.h
    seededdistancetransform.h
    segmentation.h
    valuecropper.h
    valuenormalizer.h
    valuedenormalizer.h
    vectoroperators.h
    )

set(MAIN_SOURCE_FILES
    ${SOURCE_FILES}
    main.cpp
    )

set(TEST_SOURCE_FILES
    ${SOURCE_FILES}
    ${GTEST_ROOT}/src/gtest-all.cc
    arrayadjustmenttest.cpp
    bcclatticetestinitialization.cpp
    bcclatticetestcoordinates.cpp
    bcclatticetestneighbors.cpp
    cclatticetestinitialization.cpp
    cclatticetestcoordinates.cpp
    cclatticetestneighbors.cpp
    fcclatticetestinitialization.cpp
    fcclatticetestcoordinates.cpp
    fcclatticetestneighbors.cpp
    filetest.cpp
    filtertest.cpp
    imagetestinitialization.cpp
    imagetestcoordinates.cpp
    imagetestbands.cpp
    imagetestneighbors.cpp
    imagetestmanipulation.cpp
    intensityworksettest.cpp
    neighbortest.cpp
    normtest.cpp
    priorityqueuetest.cpp
    seededdistancetransformtest.cpp
    segmentationtest.cpp
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