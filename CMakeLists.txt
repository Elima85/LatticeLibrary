cmake_minimum_required(VERSION 2.8.4)
project(latticelibrary)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(GTEST_ROOT "${PROJECT_SOURCE_DIR}/googletest")

set(SOURCE_FILES
    bcclattice.cpp
    cclattice.cpp
    fcclattice.cpp
    lattice.cpp
    neighbor.cpp
    seed.cpp
    )

set(MAIN_SOURCE_FILES
    ${SOURCE_FILES}
    main.cpp
    )

set(TEST_SOURCE_FILES
    ${SOURCE_FILES}
    ${GTEST_ROOT}/src/gtest-all.cc
        test/bcclatticetestareaapproximation.cpp
        test/bcclatticetestcoordinates.cpp
        test/bcclatticetestinitialization.cpp
        test/bcclatticetestneighbors.cpp
        test/cclatticetestareaapproximation.cpp
        test/cclatticetestcoordinates.cpp
        test/cclatticetestinitialization.cpp
        test/cclatticetestneighbors.cpp
        test/dataredistributiontest.cpp
        test/downsampletest.cpp
        test/fcclatticetestareaapproximation.cpp
        test/fcclatticetestcoordinates.cpp
        test/fcclatticetestinitialization.cpp
        test/fcclatticetestneighbors.cpp
        test/filehandling.cpp
        test/filetest.cpp
        test/filtercoefficienttest.cpp
        test/imagearithmetictest.cpp
        test/imagetestbands.cpp
        test/imagetestcoordinates.cpp
        test/imagetestinitialization.cpp
        test/imagetestneighbors.cpp
        test/imagetestmanipulation.cpp
        test/intensityworksettest.cpp
        test/linearinterpolationtest.cpp
        test/modalitymergetest.cpp
        test/neighbortest.cpp
        test/normtest.cpp
        test/priorityqueuetest.cpp
        test/seededdistancetransformtest.cpp
        test/segmentationtest.cpp
        test/sequencefiltertest.cpp
        test/spatialtemplatetest.cpp
        test/structuringelementtest.cpp
        test/uniformweighttest.cpp
        test/latticelibtest.cpp
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