cmake_minimum_required(VERSION 2.8)
project(sso)

# C++ config
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# configure the project paths
set(CORE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/core")
set(CORE_H_DIR "${CMAKE_CURRENT_SOURCE_DIR}/core/headers")
set(CORE_S_DIR "${CMAKE_CURRENT_SOURCE_DIR}/core/src")
set(CORE_TH_DIR "${CMAKE_CURRENT_SOURCE_DIR}/core/headers/Truss")
set(CORE_ST_DIR "${CMAKE_CURRENT_SOURCE_DIR}/core/src/Truss")
set(CORE_EH_DIR "${CMAKE_CURRENT_SOURCE_DIR}/core/headers/Exception")
set(CORE_ES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/core/src/Exception")
set(CORE_FH_DIR "${CMAKE_CURRENT_SOURCE_DIR}/core/headers/Frame")
set(CORE_FS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/core/src/Frame")
set(CORE_HT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/core/headers/Types")

set(CORE_ISEO_DIR "${CMAKE_CURRENT_SOURCE_DIR}/core/InternalStructuralElementObject")
set(CORE_SB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/core/StiffnessBuilder")


## -- Source files --
set(SOURCE_FILES
			core/headers/Types.h
			core/headers/Point.h core/src/Point.cpp
			core/headers/math_tools.h
			core/headers/sso_tools.h

			${CORE_ES_DIR}/AbstractException.cpp
			${CORE_EH_DIR}/sso_exception.h

			# Point Manager
			${CORE_H_DIR}/PointManager.h ${CORE_S_DIR}/PointManager.cpp

			#${CORE_TH_DIR}/TrussType.h

			# Internal Structural Element Object
			${CORE_ISEO_DIR}/InternalStructuralElementObject.h
			${CORE_SB_DIR}/StiffnessBuilder.h

			core/headers/StructuralElement.h core/src/StructuralElement.cpp
			# simple truss objects
			${CORE_TH_DIR}/InternalTrussObject.h ${CORE_ST_DIR}/InternalTrussObject.cpp
			${CORE_TH_DIR}/AbstractTruss.h ${CORE_ST_DIR}/AbstractTruss.cpp
			${CORE_TH_DIR}/SimpleTruss.h ${CORE_ST_DIR}/SimpleTruss.cpp

			core/headers/GramSchmidtProcess.h core/src/GramSchmidtProcess.cpp
			core/headers/StiffnessMatrixBuilder.h core/src/StiffnessMatrixBuilder.cpp
			core/headers/TrussSolver.h core/src/TrussSolver.cpp

			# complex truss object
			${CORE_TH_DIR}/SimpleCornerTruss.h ${CORE_ST_DIR}/SimpleCornerTruss.cpp

			# complex structure
			${CORE_FS_DIR}/Frame.cpp
			${CORE_FS_DIR}/TrussFrame.cpp
			${CORE_FS_DIR}/Simple3TrussFrame.cpp
			${CORE_FS_DIR}/Simple5TrussFrame.cpp

			core/headers/Structure.h core/src/Structure.cpp
			core/headers/TrussStructureBuilder.h core/src/TrussStructureBuilder.cpp
)# end Set SOURCE_FILES

## -- Extrernal libraries --
FIND_LIBRARY(ARMADILLO larmadillo
				/usr/local/lib)
set(LIBS -larmadillo)

# Introduce the external libraries
set(LIBS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libs")
# include the logger: easylogging++
set(EASYLOGGINGPP_FOLDER ${LIBS_DIR}/easyloggingpp)
set(EASYLOGGINGPP_H ${EASYLOGGINGPP_FOLDER}/easylogging++.h)
include_directories(${EASYLOGGINGPP_FOLDER})


# CppUnit config 
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

## --- Unit testing config --
	LIST(APPEND UnitTestLibs ${CPPUNIT_LIBRARY})
# add the tests
set(UTESTS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tests")
set(UTESTS_H_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tests/headers")
set(UTESTS_S_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tests/src")
set(UTESTS_HT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tests/headers/Truss")
set(UTESTS_ST_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tests/src/Truss")
set(UTESTS_FH_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tests/headers/Frame")
set(UTESTS_FS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tests/src/Frame")

include_directories(${UTESTS_H_DIR})
include_directories(${UTESTS_S_DIR})
include_directories(${UTESTS_HT_DIR})
include_directories(${UTESTS_ST_DIR})
include_directories(${UTESTS_FH_DIR})
include_directories(${UTESTS_ST_DIR})

# set tests files
	set(UTESTS_FILES
					core/headers/Types.h
					core/headers/Material.h
					core/headers/math_tools.h


					${UTESTS_H_DIR}/PointManagerTest.h ${UTESTS_S_DIR}/PointManagerTest.cpp


					tests/headers/BasicTest.h tests/src/BasicTest.cpp
					tests/headers/PointTest.h tests/src/PointTest.cpp
					tests/headers/MathToolsTest.h tests/src/MathToolsTest.cpp
					tests/headers/GramSchmidtProcessTest.h tests/src/GramSchmidtProcessTest.cpp

					${UTESTS_S_DIR}/InternalStructuralElementObjectTests.cpp
					${UTESTS_S_DIR}/StiffnessBuilderTest.cpp

					${UTESTS_HT_DIR}/InternalTrussObjectTest.h ${UTESTS_ST_DIR}/InternalTrussObjectTest.cpp
					tests/headers/StiffnessMatrixBuilderTest.h tests/src/StiffnessMatrixBuilderTest.cpp
        tests/headers/TrussSolverTest.h tests/src/TrussSolverTest.cpp
				${UTESTS_HT_DIR}/SimpleCornerTrussTest.h ${UTESTS_ST_DIR}/SimpleCornerTrussTest.cpp


				tests/headers/Frame/FrameTest.h tests/src/Frame/FrameTest.cpp
				${UTESTS_FS_DIR}/Simple3TrussFrameTest.cpp
				${UTESTS_FS_DIR}/Simple5TrussFrameTest.cpp


				tests/headers/StructureTest.h tests/src/StructureTest.cpp
				tests/headers/TrussStructureBuilderTest.h tests/src/TrussStructureBuilderTest.cpp
        )

#Add all unit tests in addition to all source files.
add_executable(UnitTester test_runner.cpp ${SOURCE_FILES} ${UTESTS_FILES} ${EASYLOGGINGPP_H} )
target_link_libraries (UnitTester ${UnitTestLibs} ${LIBS})
## --- end Unit testing config --


# Release
include_directories(${LIBS_DIR})
include_directories(${CORE_EH_DIR})
include_directories(${CORE_H_DIR})
include_directories(${CORE_TH_DIR})
include_directories(${CORE_FH_DIR})
include_directories(${CORE_HT_DIR})
include_directories(${CORE_ISEO_DIR})
include_directories(${CORE_SB_DIR})
#include_directories(${CORE_DIR}/src)
#add_executable(sso main.cpp ${SOURCE_FILES} ${EASYLOGGINGPP_H})
#target_link_libraries(sso ${LIBS})
# Create a library that could be use for EASEA
add_library( sso SHARED ${SOURCE_FILES} ${EASYLOGGINGPP_H})
