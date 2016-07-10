#include "MathToolsTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(MathToolsTest);

MathToolsTest::MathToolsTest(){
}

MathToolsTest::~MathToolsTest(){
}

void MathToolsTest::tearDown(){
	if( a ) delete a;
	if( b ) delete b;
}

void MathToolsTest::setUp(){
}

void MathToolsTest::basic_tests(){

	a=new Point(0.0,0.0,0.0,0);
	b=new Point(1.0,1.0,0.0,1);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Pythagoria((0,0,0),(1,1,0)()=sqrt(2)",
			(float)sqrt(2),Pythagoria(a,b));

	a=new Point(0.0,0.0,0.0,2);
	b=new Point(1.0,1.0,1.0,3);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("Pythagoria((0,0,0),(1,1,1)()=sqrt(3)",
			(float)sqrt(3),Pythagoria(a,b));
}
