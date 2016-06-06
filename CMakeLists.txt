cmake_minimum_required(VERSION 2.8)
project(sso)

# C++ config
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# configure the project paths
set(CORE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/core")
set(CORE_H_DIR "${CMAKE_CURRENT_SOURCE_DIR}/core/headers")
set(CORE_S_DIR "${CMAKE_CURRENT_SOURCE_DIR}/core/src")
set(CORE_HT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/core/headers/Truss")
set(CORE_ST_DIR "${CMAKE_CURRENT_SOURCE_DIR}/core/src/Truss")


	include_directories(${CORE_H_DIR})

# Source files
	set(SOURCE_FILES
					core/headers/Types.h
					core/headers/Point.h core/src/Point.cpp

					core/headers/StructuralElement.h core/src/StructuralElement.cpp
					# truss objects
					${CORE_HT_DIR}/InternalTrussObject.h ${CORE_ST_DIR}/InternalTrussObject.cpp
					${CORE_HT_DIR}/AbstractTruss.h ${CORE_ST_DIR}/AbstractTruss.cpp
					${CORE_HT_DIR}/SimpleTruss.h ${CORE_ST_DIR}/SimpleTruss.cpp
					${CORE_HT_DIR}/SimpleCornerTruss.h ${CORE_ST_DIR}/SimpleCornerTruss.cpp

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
set(UTESTS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tests")
set(UTESTS_H_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tests/headers")
set(UTESTS_S_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tests/src")
set(UTESTS_HT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tests/headers/Truss")
set(UTESTS_ST_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tests/src/Truss")

include_directories(${UTESTS_H_DIR})
include_directories(${UTESTS_S_DIR})
include_directories(${UTESTS_HT_DIR})
include_directories(${UTESTS_ST_DIR})

# set tests files
	set(UTESTS_FILES
					core/headers/Types.h
					core/headers/Material.h
					tests/headers/BasicTest.h tests/src/BasicTest.cpp
					tests/headers/PointTest.h tests/src/PointTest.cpp
					tests/headers/GramSchmidtProcessTest.h tests/src/GramSchmidtProcessTest.cpp
					${UTESTS_HT_DIR}/SimpleTrussTest.h ${UTESTS_ST_DIR}/SimpleTrussTest.cpp
					${UTESTS_HT_DIR}/SimpleCornerTrussTest.h ${UTESTS_ST_DIR}/SimpleCornerTrussTest.cpp
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
include_directories(${CORE_H_DIR})
include_directories(${CORE_HT_DIR})
include_directories(${CORE_DIR}/src)
add_executable(sso main.cpp ${SOURCE_FILES})
target_link_libraries(sso ${LIBS})
