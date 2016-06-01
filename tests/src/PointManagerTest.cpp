#include "PointManagerTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(PointManagerTest);

PointManagerTest::PointManagerTest() {

}

PointManagerTest::~PointManagerTest() {

}

void PointManagerTest::setUp() {

}

void PointManagerTest::tearDown() {

}

void PointManagerTest::basic_tests() {
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Expect the x coordinate", 1, 1);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Expect the manager to contain no point", (long) 0, PointManager::GetInstance().GetNumberOfPoints());
}

void PointManagerTest::add_delete_point_test(){
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Expect the manager to contain no point", (long) 0, PointManager::GetInstance().GetNumberOfPoints());
		//
		// ask for a point given coordinates
		//
		float x=0.0, y=0.0, z=0.0;
		Point* p = PointManager::GetInstance().GetPoint(x,y,z);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Expect the manager to contain 1 point", (long) 1, PointManager::GetInstance().GetNumberOfPoints());
		CPPUNIT_ASSERT_MESSAGE("Expect the manager to find the same point",p->x==x && p->y==y & p->z==z);
    CPPUNIT_ASSERT_MESSAGE("The index of (0,0,0) must be 0" ,p->index==0);
}

