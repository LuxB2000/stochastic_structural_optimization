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
	Simple5TrussFrame f = Simple5TrussFrame();
	CPPUNIT_ASSERT_MESSAGE("We expect the parameter vector beeing initiate",f.GetParameters());
	CPPUNIT_ASSERT_EQUAL_MESSAGE("We expect 7 parameter",7,(int)f.GetParameters()->size()); // the 10th is the material that is not stocked in that vector

	Simple3TrussFrame f3 = Simple3TrussFrame();
	CPPUNIT_ASSERT_MESSAGE("We expect the parameter vector beeing initiate",f3.GetParameters());
	CPPUNIT_ASSERT_EQUAL_MESSAGE("We expect 3 parameters",3,(int)f3.GetParameters()->size());
}

void FrameTest::parameters_tests(void){
	Material m = TEST;
									// lv1 lv21 lv22 lh22 lv3  lh3 section, numbers in meter
	FrameParametersVectorType param =	{1.75, 1.15, 0.6, 0.5, 0.30, 0.6, 0.08};
	Simple5TrussFrame f = Simple5TrussFrame(origin, param, m);
	CPPUNIT_ASSERT_MESSAGE("We expect to find the same parameters than inputs", param==*f.GetParameters());
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
	Material m = TEST;
	FrameParametersVectorType param =	{1.75, 1.15, 0.6, 0.5, 0.30, 0.6, 0.08};
	Simple5TrussFrame f = Simple5TrussFrame(origin, param, m);

}

void FrameTest::build_Simple3TrussFrame_tests(void){
	// Parameters fit the example presented in "Introduction to Finite Element
	// Analysis Using Matlab and Abaqus", A. Khennane, page 110, 2013.
	// param = {dim_y_SimpleTruss, dim_x_TopCornerTruss, dim_y_TopCornerTruss}
	FrameParametersVectorType params = {5.0, 6.0, 1.0};
	double cross_sec = 5310; // in mm^2
	Material mat_type = TEST;
	Simple3TrussFrame f3 = Simple3TrussFrame(origin,params,cross_sec,mat_type);
}
