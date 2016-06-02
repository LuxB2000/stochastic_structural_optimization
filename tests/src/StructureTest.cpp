/*
 * =====================================================================================
 *
 *       Filename:  StructureTest.cpp
 *
 *    Description:  
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
			structure.GetOrigin()==Point(0,0,0));
	
	Point new_origin = Point(1.0,1.0,1.0);
	structure.SetOrigin(new_origin);
	CPPUNIT_ASSERT_MESSAGE("We expect the default origin", 
			structure.GetOrigin()==new_origin);

}
