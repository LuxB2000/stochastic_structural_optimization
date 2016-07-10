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
	CPPUNIT_ASSERT_MESSAGE("We expect an empty structure",structure.GetNumberOfFrames()==0);

}

void StructureTest::origin_tests(){
	Structure structure = Structure();
	CPPUNIT_ASSERT_MESSAGE("We expect the default origin", 
			structure.GetOrigin()->x == 0 && structure.GetOrigin()->y == 0 && structure.GetOrigin()->z == 0 );
	
	Point* new_origin = PointManager::GetInstance().GetPoint(1.0,1.0,1.0);
	structure.SetOrigin(new_origin);
	CPPUNIT_ASSERT_MESSAGE("We expect the default origin", 
			structure.GetOrigin()==new_origin);

}
