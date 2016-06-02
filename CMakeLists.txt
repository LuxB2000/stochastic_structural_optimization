cmake_minimum_required(VERSION 2.8)
project(sso)

# C++ config
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# configure the project paths
set(CORE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/core")
set(CORE_H_DIR "${CMAKE_CURRENT_SOURCE_DIR}/core/headers")
set(CORE_S_DIR "${CMAKE_CURRENT_SOURCE_DIR}/core/src")
set(UTESTS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tests")


include_directories(${CORE_H_DIR})

# Source files
set(SOURCE_FILES
        core/headers/Types.h
        core/headers/StructuralElement.h core/src/StructuralElement.cpp
        core/headers/Truss.h core/src/Truss.cpp
        core/headers/Point.h core/src/Point.cpp
        core/headers/GramSchmidtProcess.h core/src/GramSchmidtProcess.cpp
        core/headers/StiffnessMatrixBuilder.h core/src/StiffnessMatrixBuilder.cpp
        core/headers/TrussSolver.h core/src/TrussSolver.cpp
				core/headers/Frame.h core/src/Frame.cpp
				core/headers/Structure.h core/src/Structure.cpp
				core/headers/TrussStructureBuilder.h core/src/TrussStructureBuilder.cpp
        )

# Extrernal libraries
FIND_LIBRARY(ARMADILLO larmadillo
        /usr/local/lib)
set(LIBS -larmadillo)

## -- CppUnit config --
# looking for the CppUnit library
FIND_PATH(CPPUNIT_INCLUDE_DIR cppunit/TestCase.h /usr/local/include /usr/include)

include_directories(${CPPUNIT_INCLUDE_DIR})

FIND_LIBRARY(CPPUNIT_LIBRARY cppunit
           ${CPPUNIT_INCLUDE_DIR} /../lib
           /usr/local/lib
           /usr/lib)
FIND_LIBRARY(CPPUNIT_DEBUG_LIBRARY cppunit
           ${CPPUNIT_INCLUDE_DIR} /../lib
           /usr/local/lib
           /usr/lib)
## --- end CppUnit config ---

## --- Unit testing config --
LIST(APPEND UnitTestLibs ${CPPUNIT_LIBRARY})
# add the tests
include_directories(${UTESTS_DIR}/headers)
include_directories(${UTESTS_DIR}/src)

# set tests files
set(UTESTS_FILES
        core/headers/Types.h
        tests/headers/BasicTest.h tests/src/BasicTest.cpp
        tests/headers/PointTest.h tests/src/PointTest.cpp
        tests/headers/GramSchmidtProcessTest.h tests/src/GramSchmidtProcessTest.cpp
        tests/headers/TrussTest.h tests/src/TrussTest.cpp
        tests/headers/StiffnessMatrixBuilderTest.h tests/src/StiffnessMatrixBuilderTest.cpp
        tests/headers/TrussSolverTest.h tests/src/TrussSolverTest.cpp
				tests/headers/FrameTest.h tests/src/FrameTest.cpp
				tests/headers/StructureTest.h tests/src/StructureTest.cpp
        tests/headers/TrussStructureBuilderTest.h tests/src/TrussStructureBuilderTest.cpp
        )

#Add all unit tests in addition to all source files.
add_executable(UnitTester test_runner.cpp ${UTESTS_FILES} ${SOURCE_FILES} )
target_link_libraries (UnitTester ${UnitTestLibs} ${LIBS})
## --- end Unit testing config --


# Release
include_directories(${CORE_DIR}/headers)
include_directories(${CORE_DIR}/src)
add_executable(sso main.cpp ${SOURCE_FILES})
target_link_libraries(sso ${LIBS})
