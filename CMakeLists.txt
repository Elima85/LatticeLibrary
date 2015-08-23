cmake_minimum_required(VERSION 2.8.4)
project(latticelibrary)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(GTEST_ROOT "${PROJECT_SOURCE_DIR}/googletest")

set(SOURCE_FILES
    approximateminimumbarrierdistance.h
    bcclattice.cpp
    bcclattice.h
    cclattice.cpp
    cclattice.h
    cropintensityrange.h
    dataredistribution.h
    defs.h
    exception.h
    fcclattice.cpp
    fcclattice.h
    filehandling.cpp
    filehandling.h
    filtercoefficient.h
    fuzzyconnectedness.h
    image.h
    imagearithmetic.h
    intensityworkset.h
    interpolation.h
    lattice.cpp
    lattice.h
    linearinterpolation.h
    modalitymerge.h
    neighbor.cpp
    neighbor.h
    norm.h
    priorityqueue.h
    renormalizeintensityrange.h
    seed.cpp
    seed.h
    seededdistancemeasure.h
    seededdistancetransform.h
    segmentation.h
    vectoroperators.h
    weightedaveragefilter.h
    )

set(MAIN_SOURCE_FILES
    ${SOURCE_FILES}
    main.cpp
    )

set(TEST_SOURCE_FILES
    ${SOURCE_FILES}
    ${GTEST_ROOT}/src/gtest-all.cc
    bcclatticetestareaapproximation.cpp
    bcclatticetestcoordinates.cpp
    bcclatticetestinitialization.cpp
    bcclatticetestneighbors.cpp
    cclatticetestareaapproximation.cpp
    cclatticetestcoordinates.cpp
    cclatticetestinitialization.cpp
    cclatticetestneighbors.cpp
    dataredistributiontest.cpp
    downsampletest.cpp
    fcclatticetestareaapproximation.cpp
    fcclatticetestcoordinates.cpp
    fcclatticetestinitialization.cpp
    fcclatticetestneighbors.cpp
    filetest.cpp
    filtercoefficienttest.cpp
    imagearithmetictest.cpp
    imagetestbands.cpp
    imagetestcoordinates.cpp
    imagetestinitialization.cpp
    imagetestneighbors.cpp
    imagetestmanipulation.cpp
    intensityworksettest.cpp
    linearinterpolationtest.cpp
    modalitymergetest.cpp
    neighbortest.cpp
    normtest.cpp
    priorityqueuetest.cpp
    seededdistancetransformtest.cpp
    segmentationtest.cpp
    sequencefiltertest.cpp
    spatialtemplatetest.cpp
    latticelibtest.cpp
    uniformweighttest.cpp
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