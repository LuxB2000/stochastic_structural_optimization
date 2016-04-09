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

    // test default constructor
    Point *a = new Point(x,y,z);

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Expect the x coordinate", x, a->x);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Expect the y coordinate", y, a->y);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Expect the z coordinate", z, a->z);

    // copy constructor
    Point *b = new Point(*a);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Expect the x coordinate", x, b->x);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Expect the y coordinate", y, b->y);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Expect the z coordinate", z, b->z);

    delete a;
    delete b;
}

