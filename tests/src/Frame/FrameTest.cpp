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
	origin = PointManager::GetInstance().GetPoint(0.0,0.0,0.0);
}

void FrameTest::basic_tests(){

}

void FrameTest::parameters_tests(void){
}

void FrameTest::stiffness_test(){
}

/*
void FrameTest::parameters_tests(void){
																	// l1    l2   a2    l3    a3
	FrameParametersVectorType param =	{1.5, 0.75, 43.2, 0.35, 90};
	Simple5TrussFrame f = Simple5TrussFrame(origin, param);
	CPPUNIT_ASSERT_MESSAGE("We expect to find the same parameters than inputs", param==*f.GetParameters());
}
*/

void FrameTest::build_Simple5TrussFrame_tests(){

}

