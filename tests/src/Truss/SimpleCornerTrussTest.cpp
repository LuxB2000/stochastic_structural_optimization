/*
 * =====================================================================================
 *
 *       Filename:  SimpleCornerTrussTest.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/06/16 11:42:16
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jerome Plumat (JP), j.plumat@auckland.ac.nz
 *        Company:  UoA, Auckand, NZ
 *
 * =====================================================================================
 */

#include "SimpleCornerTrussTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(SimpleCornerTrussTest);

SimpleCornerTrussTest::SimpleCornerTrussTest(){
}

SimpleCornerTrussTest::~SimpleCornerTrussTest(){
}

void SimpleCornerTrussTest::tearDown(){
}

void SimpleCornerTrussTest::setUp(){
}

void SimpleCornerTrussTest::basic_tests(){
	Point a = Point(0.0,0.0,0.0);
	Point b = Point(0.0,1.0,0.0);
	Point c = Point(0.0,2.0,0.0);
	SimpleCornerTruss ctruss = SimpleCornerTruss( &a,&b,&c,1.0,TEST);
	CPPUNIT_ASSERT_MESSAGE("The stiffness matrix should be initialized",
			ctruss.GetLocalStiffnessMatrixPointer()); // check if pointer is not null
	CPPUNIT_ASSERT_EQUAL_MESSAGE("The stiffness should a 9x9 matrix",
			81,static_cast<int>(ctruss.GetLocalStiffnessMatrixPointer()->n_elem));
    CPPUNIT_ASSERT_MESSAGE("The transformation matrix should be initialized",
			ctruss.GetLocalTransformationMatrixPointer());// check if pointer is not null
  //  CPPUNIT_ASSERT_EQUAL_MESSAGE("The transformation matrix should a 6x6 matrix",
	//		36,static_cast<int>(ctruss.GetLocalTransformationMatrixPointer()->n_elem));
}

void SimpleCornerTrussTest::getters_tests(){
}

void SimpleCornerTrussTest::length_tests(){
	Point a1 = Point(0.0,0.0,0.0);
	Point b1 = Point(0.0,1.0,0.0);
	Point c1 = Point(0.0,2.0,0.0);
	double area = 1.0;
	Material m = TEST;

	SimpleCornerTruss ctruss = SimpleCornerTruss( &a1, &b1, &c1, area, m );
	CPPUNIT_ASSERT_EQUAL_MESSAGE( "Trivial corner should have a trivial length",
			2.0, ctruss.GetLength() );

	Point c2 = Point(1.0,2.0,0.0);
	CPPUNIT_ASSERT_EQUAL_MESSAGE( "Simple corner should have a length as the sum of the different parts",
			1.0+sqrt(2), SimpleCornerTruss(&a1,&b1,&c2,area,m).GetLength() );

	Point c3 = Point(1.0,2.0,1.0);
	CPPUNIT_ASSERT_EQUAL_MESSAGE( "Simple corner should have a length as the sum of the different parts even in 3D",
			1.0+sqrt(3), SimpleCornerTruss(&a1,&b1,&c3,area,m).GetLength() );
}
