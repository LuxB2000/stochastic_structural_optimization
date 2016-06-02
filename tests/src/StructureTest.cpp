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
	CPPUNIT_ASSERT_MESSAGE("OK",1==1);
}
