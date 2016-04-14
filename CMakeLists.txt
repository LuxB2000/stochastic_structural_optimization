cmake_minimum_required(VERSION 2.8)
project(sso)

# C++ config
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# configure the project paths
set(UTESTS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tests")

# Source files
set(SOURCE_FILES
        core/headers/StructuralElement.h core/src/StructuralElement.cpp
        core/headers/Truss.h core/src/Truss.cpp
        core/headers/Point.h core/src/Point.cpp
        core/headers/GramSchmidtProcess.h core/src/GramSchmidtProcess.cpp
        )

# Extrernal libraries
FIND_LIBRARY(ARMADILLO larmadillo
        /usr/local/lib)
set(LIBS -larmadillo)

## -- CppUnit config --
# looking for the CppUnit library
set(CppUnit_INCLUDE_DIR "/usr/local/cppunit/") #TODO: improve, should be more generic and use FIND_PATH
set(CPPUNIT_INCLUDE_DIR "/usr/local/cppunit/")

include_directories(${CPPUNIT_INCLUDE_DIR})

FIND_LIBRARY(CPPUNIT_LIBRARY cppunit
           ${CPPUNIT_INCLUDE_DIR}/../lib
           /usr/local/lib
           /usr/lib)
FIND_LIBRARY(CPPUNIT_DEBUG_LIBRARY cppunit
           ${CPPUNIT_INCLUDE_DIR}/../lib
           /usr/local/lib
           /usr/lib)
## --- end CppUnit config ---

## --- Unit testing config --
LIST(APPEND UnitTestLibs ${CPPUNIT_LIBRARY})
# add the tests
include_directories(${UTESTS_DIR}/headers)
include_directories(${UTESTS_DIR}/src)
#Find all source files in unit test: !! unit test files are assume to be some_nameTest.{cpp,h}
FILE(GLOB_RECURSE UTESTS_FILES "*Test.cpp" "*Test.h")
#message("Test: ${UTESTS_DIR}")
#message("Test: ${UTESTS_FILES}")
#Add all unit tests in addition to all source files.
add_executable(UnitTester test_runner.cpp ${UTESTS_FILES} ${SOURCE_FILES} tests/src/GramSchmidtProcessTest.cpp)
target_link_libraries (UnitTester ${UnitTestLibs} ${LIBS})
## --- end Unit testing config --


# Release
add_executable(sso main.cpp ${SOURCE_FILES})
target_link_libraries(sso ${LIBS})
