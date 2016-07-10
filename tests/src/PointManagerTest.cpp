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

void PointManagerTest::add_point_test(){
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Expect the manager to contain no point", (long) 0, PointManager::GetInstance().GetNumberOfPoints());
		//
		// ask for a point given coordinates
		//
		float x=0.0, y=0.0, z=0.0;
		Point* p = PointManager::GetInstance().GetPoint(x,y,z);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Expect the manager to contain 1 point", (long) 1, PointManager::GetInstance().GetNumberOfPoints());
		CPPUNIT_ASSERT_MESSAGE("Expect the manager to find the same point",p->x==x && p->y==y & p->z==z);
    CPPUNIT_ASSERT_MESSAGE("The index of (0,0,0) must be 0" ,p->index==0);

		// asking a second time the same point
		Point* p1 = PointManager::GetInstance().GetPoint(x,y,z);
		CPPUNIT_ASSERT_EQUAL_MESSAGE("Expect the manager to contain 1 point", (long) 1, PointManager::GetInstance().GetNumberOfPoints());

		float x2=1.0, y2=2.0, z2=3.0;
		Point* p2 = PointManager::GetInstance().GetPoint(x2,y2,z2);
		CPPUNIT_ASSERT_MESSAGE("Expect the manager to find the same point",p2->x==x2 && p2->y==y2 & p2->z==z2);

		float x3=2.1, y3=2.0, z3=3.0;
		Point* p3 = PointManager::GetInstance().GetPoint(x3,y3,z3);
		CPPUNIT_ASSERT_MESSAGE("Expect the manager to find the same point",p3->x==x3 && p3->y==y3 & p3->z==z3);

		// expected coordinates: between [0,10[ with 1E-3 precision
		x3=4.105; // WARNING: will not be available for MESHES !!
		y3=0.061;
		z3=8.082;
		p3 = PointManager::GetInstance().GetPoint(x3,y3,z3);
		CPPUNIT_ASSERT_MESSAGE("Expect the manager to find the same point",p3->x==x3 && p3->y==y3 & p3->z==z3);
		x3=4.106; // WARNING: will not be available for MESHES !!
		y3=0.062;
		z3=8.083;
		p3 = PointManager::GetInstance().GetPoint(x3,y3,z3);
		CPPUNIT_ASSERT_MESSAGE("Expect the manager to find the same point",p3->x==x3 && p3->y==y3 & p3->z==z3);

}

void PointManagerTest::connexion_test(){
		// create a connexion between two points
		float x1=0.0, y1=0.0, z1=0.0;
		float x2=1.0, y2=1.0, z2=1.0;

		Point* p1 = PointManager::GetInstance().GetPoint(x1,y1,z1);
		Point* p2 = PointManager::GetInstance().GetPoint(x2,y2,z2);

		PointManager::GetInstance().SetConnexion(p1,p2);
		// retreive the connexions from the point
		PointManager::PointVectorType neigh_1 = PointManager::GetInstance().GetConnexions(p1);
		PointManager::PointVectorType neigh_2 = PointManager::GetInstance().GetConnexions(p2);
		CPPUNIT_ASSERT_MESSAGE("Expect to find the same point in neighborhood of 1",neigh_1.size()==1 && 
				neigh_1[0]->x == p2->x && neigh_1[0]->y == p2->y && neigh_1[0]->z == p2->z);
		CPPUNIT_ASSERT_MESSAGE("Expect to find the same point in neighborhood of 2",neigh_2.size()==1 && 
				neigh_2[0]->x == p1->x && neigh_2[0]->y == p1->y && neigh_2[0]->z == p1->z);

		// add a second connexion to p1
		float x3=1.0, y3=0.0, z3=1.0;
		Point* p3 = PointManager::GetInstance().GetPoint(x3,y3,z3);
		PointManager::GetInstance().SetConnexion(p1,p3);
		neigh_1 = PointManager::GetInstance().GetConnexions(p1);
		CPPUNIT_ASSERT_MESSAGE("Expect to find the two points in neighborhood of 1",neigh_1.size()==2 && 
				neigh_1[1]->x == p3->x && neigh_1[1]->y == p3->y && neigh_1[1]->z == p3->z);

		// remove a connexion
		PointManager::GetInstance().RemoveConnexion(p1,p3);
		neigh_1 = PointManager::GetInstance().GetConnexions(p1);
		CPPUNIT_ASSERT_MESSAGE("Expect to find one point in neighborhood of 1",neigh_1.size()==1 && 
				neigh_1[0]->x == p2->x && neigh_1[0]->y == p2->y && neigh_1[0]->z == p2->z);
		PointManager::PointVectorType neigh_3 = PointManager::GetInstance().GetConnexions(p3);
		CPPUNIT_ASSERT_MESSAGE("Expect to find no point in neighborhood of 3",neigh_3.size()==0 );// && 

}

