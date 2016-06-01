/*
 * =====================================================================================
 *
 *       Filename:  FrameTest.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/06/16 13:08:21
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jerome Plumat (JP)
 *
 * =====================================================================================
 */

#include "FrameTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(FrameTest);

FrameTest::FrameTest(){
}

FrameTest::~FrameTest(){
}

void FrameTest::tearDown(){
}

void FrameTest::setUp(){
}

void FrameTest::basic_tests(){
	Simple5TrussFrame f = Simple5TrussFrame();
	CPPUNIT_ASSERT_MESSAGE("We expect the parameter vector beeing initiate",f.GetParameters());
	CPPUNIT_ASSERT_MESSAGE("We expect 6 parameter",f.GetParameters()->size());
}

void FrameTest::parameters_tests(void){
	Point* origine = PointManager::GetInstance().GetPoint(0.0,0.0,0.0);
																	// l1    l2   a2    l3    a3
	FrameParametersVectorType param =	{1.5, 0.75, 43.2, 0.35, 90};
	Simple5TrussFrame f = Simple5TrussFrame(origine, param);
	CPPUNIT_ASSERT_MESSAGE("We expect to find the same parameters than inputs", param==*f.GetParameters());
}

void FrameTest::build_tests(){
	Point* origine = PointManager::GetInstance().GetPoint(0.0,0.0,0.0);
	FrameParametersVectorType param =	{1.5, 0.75, 43.2, 0.35, 90};
	Simple5TrussFrame f = Simple5TrussFrame(origine, param);
}
