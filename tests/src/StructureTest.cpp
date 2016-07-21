/*
 * =====================================================================================
 *
 *       Filename:  StructureTest.cpp
 *
 *    Description:  The test relative to the Structure
 *
 *        Version:  1.0
 *        Created:  02/06/16 11:14:07
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jerome Plumat (JP)
 *
 * =====================================================================================
 */

#include "StructureTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(StructureTest);

StructureTest::StructureTest(){
}

StructureTest::~StructureTest(){
}

void StructureTest::tearDown(){
}

void StructureTest::setUp(){
}

void StructureTest::basic_tests(){
	Structure structure = Structure();
	// got the number of frame created in the building
	CPPUNIT_ASSERT_MESSAGE("We expect an empty structure",structure.GetNumberOfFrames()==0);

}

void StructureTest::origin_tests(){
	Structure structure = Structure();
	CPPUNIT_ASSERT_MESSAGE("We expect the default origin", 
			structure.GetOrigin()->x == 0 && structure.GetOrigin()->y == 0 && structure.GetOrigin()->z == 0 );
	
	Point* new_origin = PointManager::GetInstance().GetPoint(1.0,1.0,1.0);
	structure.SetOrigin(new_origin);
	CPPUNIT_ASSERT_MESSAGE("We expect the specified origin", 
			structure.GetOrigin()==new_origin);

}

void StructureTest::build_tests(){
	// params
	double cross_sec = 5310*1E-6; // in m^2
	Material mat_type = TEST;
	// build a structure with only one frame
	int nbrOfFrames = 1;
	// parameters of the Simple3TrussFrame
	FrameParametersVectorType params = {5.0, 6.0, 1.0};
	// boundary condition, WARNING: we assume to know the point IDs
	// TODO: make it more general, passing the coordinates of the points?
	BoundaryConditionsVectorType bc = BoundaryConditionsVectorType();
    bc.push_back({0,0}); // at joint 0, Rx=0
    bc.push_back({0,1}); // at joint 0, Ry=0
    bc.push_back({0,2}); // at joint 0, Rz=0
    bc.push_back({4,0}); // at joint 4, Rx=0
    bc.push_back({4,1}); // at joint 4, Ry=0
    bc.push_back({4,2}); // at joint 4, Rz=0

	Point* origin = PointManager::GetInstance().GetPoint(0.0,0.0,0.0);
	Structure structure = Structure(origin);
	structure.SetNumberOfFrames( nbrOfFrames );
	structure.SetFrameParameters( params, cross_sec, mat_type );
	structure.SetBoundaryConditions( bc );
	structure.Build();

	CPPUNIT_ASSERT_MESSAGE("We expect a structure with one frame",structure.GetNumberOfFrames()==nbrOfFrames);
}
