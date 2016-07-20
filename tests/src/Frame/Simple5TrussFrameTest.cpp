#include "Simple5TrussFrameTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(Simple5TrussFrameTest);

Simple5TrussFrameTest::Simple5TrussFrameTest(){
}

Simple5TrussFrameTest::~Simple5TrussFrameTest(){
}

void Simple5TrussFrameTest::setUp(){
	origin = PointManager::GetInstance().GetPoint(0.0,0.0,0.0);
}

void Simple5TrussFrameTest::tearDown(){
}

void Simple5TrussFrameTest::basic_tests(void){
	Simple5TrussFrame f = Simple5TrussFrame();
	CPPUNIT_ASSERT_MESSAGE("We expect the parameter vector beeing initiate",f.GetParameters());
	CPPUNIT_ASSERT_EQUAL_MESSAGE("We expect 7 parameter",7,(int)f.GetParameters()->size()); // the 10th is the material that is not stocked in that vector

	Material m = TEST;
									// lv1 lv21 lv22 lh22 lv3  lh3 section, numbers in meter
	FrameParametersVectorType param =	{1.75, 1.15, 0.6, 0.5, 0.30, 0.6, 0.08};
	Simple5TrussFrame f5 = Simple5TrussFrame(origin, param, m);
	CPPUNIT_ASSERT_MESSAGE("We expect to find the same parameters than inputs", param==*f5.GetParameters());
}

void Simple5TrussFrameTest::build_tests(void){
	Material m = TEST;
	FrameParametersVectorType param =	{1.75, 1.15, 0.6, 0.5, 0.30, 0.6, 0.08};
	Simple5TrussFrame f = Simple5TrussFrame(origin, param, m);
}
