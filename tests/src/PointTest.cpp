//
// Created by plumat on 4/8/16.
//

#include "../headers/PointTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(PointTest);

PointTest::PointTest() {

}

PointTest::~PointTest() {

}

void PointTest::setUp() {

}

void PointTest::tearDown() {

}

void PointTest::basic_tests() {
    float x=1.0, y=2.0, z=3.5;
		Point::IndexType id = 1;

		// test constructor with index
    Point a1 = Point(x,y,z,id);

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Expect the x coordinate", x, a1.x);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Expect the y coordinate", y, a1.y);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Expect the z coordinate", z, a1.z);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Expect the index", id, a1.index);


    // copy constructor
    Point b = Point(a1);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Expect the x coordinate", x, b.x);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Expect the y coordinate", y, b.y);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Expect the z coordinate", z, b.z);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Expect the index", id, b.index);

}

void PointTest::operator_tests(){
	Point p1 = Point(1.0,1.0,1.0,0);
	Point p2 = Point(1.0,1.0,1.0,1);
	Point p3 = Point(1.1,1.0,1.0,2);
	Point p4 = Point(1.0,0.0,1.0,3);

	CPPUNIT_ASSERT_MESSAGE("We expect two points been equal", p1==p2);
	CPPUNIT_ASSERT_MESSAGE("We expect two points been different", !(p1==p3));
	CPPUNIT_ASSERT_MESSAGE("We expect two points been different", !(p1==p4));

	CPPUNIT_ASSERT_MESSAGE("We expect two points been equal", !(p1!=p2));
	CPPUNIT_ASSERT_MESSAGE("We expect two points been different", (p1!=p3));
	CPPUNIT_ASSERT_MESSAGE("We expect two points been different", (p1!=p4));
}
