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
	CPPUNIT_ASSERT_EQUAL_MESSAGE("We expect 7 parameter",7,(int)f.GetParameters()->size()); // the 10th is the material that is not stocked in that vector
}

void FrameTest::parameters_tests(void){
	Material m = TEST;
	Point* origine = PointManager::GetInstance().GetPoint(0.0,0.0,0.0);
									// lv1 lv21 lv22 lh22 lv3  lh3 section, numbers in meter
	FrameParametersVectorType param =	{1.75, 1.15, 0.6, 0.5, 0.30, 0.6, 0.08};
	Simple5TrussFrame f = Simple5TrussFrame(origine, param, m);
	CPPUNIT_ASSERT_MESSAGE("We expect to find the same parameters than inputs", param==*f.GetParameters());
}

void FrameTest::build_tests(){
	Material m = TEST;
	Point* origine = PointManager::GetInstance().GetPoint(0.0,0.0,0.0);
	FrameParametersVectorType param =	{1.75, 1.15, 0.6, 0.5, 0.30, 0.6, 0.08};
	Simple5TrussFrame f = Simple5TrussFrame(origine, param, m);

	// check the different Points coordinate
}

void FrameTest::stiffness_test(){
}
