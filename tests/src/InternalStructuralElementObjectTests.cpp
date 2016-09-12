#include "TrussType.h"
#include "BeamType.h"
#include "InternalStructuralElementObjectTests.h"

CPPUNIT_TEST_SUITE_REGISTRATION(InternalStructuralElementObjectTest);

InternalStructuralElementObjectTest::InternalStructuralElementObjectTest(){
}

InternalStructuralElementObjectTest::~InternalStructuralElementObjectTest(){
}

void InternalStructuralElementObjectTest::setUp(){
}

void InternalStructuralElementObjectTest::tearDown(){
}

void InternalStructuralElementObjectTest::types_test(){
	CPPUNIT_ASSERT_MESSAGE("TrussType must have a DOF equals to 3", TrussType::NDOF == 3 );
	CPPUNIT_ASSERT_MESSAGE("BeamType must have a DOF equals to 6", BeamType::NDOF == 6 );
}

void InternalStructuralElementObjectTest::basic_test(){
	Point* start = PointManager::GetInstance().GetPoint(0.0, 0.0, 0.0);
	Point* end = PointManager::GetInstance().GetPoint(1.0, 1.0, 1.0);
	double cross_sec = 2.5;

	InternalTrussElement obj_t = InternalTrussElement(start,end,cross_sec,BASIC);
	CPPUNIT_ASSERT_MESSAGE("Each Internal Truss Element Object must have 2 points",obj_t.GetNumberOfPoints() == 2);

	InternalBeamElement obj_b = InternalBeamElement(start,end,cross_sec,BASIC);
	CPPUNIT_ASSERT_MESSAGE("Each Internal Beam Element Object must have 2 points",obj_b.GetNumberOfPoints() == 2);

	CPPUNIT_ASSERT_EQUAL_MESSAGE("The stiffness should a 6x6 matrix for TrussType",
			36,static_cast<int>(obj_t.GetLocalStiffnessMatrix().n_elem));
	CPPUNIT_ASSERT_EQUAL_MESSAGE("The displacement vector should be 1x6 for TrussType",
			6,static_cast<int>(obj_t.GetNodalDisplacementInLocalCoordinates().n_elem));
	CPPUNIT_ASSERT_EQUAL_MESSAGE("The element forces vector should be 1x3 for TrussType",
			3,static_cast<int>(obj_t.GetElementForcesInLocalCoordinates().n_elem));

	CPPUNIT_ASSERT_EQUAL_MESSAGE("The stiffness should a 12x12 matrix for BeamType",
			144,static_cast<int>(obj_b.GetLocalStiffnessMatrix().n_elem));
	CPPUNIT_ASSERT_EQUAL_MESSAGE("The displacement vector should be 1x24 for BeamType",
			12,static_cast<int>(obj_b.GetNodalDisplacementInLocalCoordinates().n_elem));
	CPPUNIT_ASSERT_EQUAL_MESSAGE("The element forces vector should be 1x6 for BeamType",
			6,static_cast<int>(obj_b.GetElementForcesInLocalCoordinates().n_elem));
}

void InternalStructuralElementObjectTest::constructor_test(){
	Point* start = PointManager::GetInstance().GetPoint(0.0, 0.0, 0.0);
	Point* end = PointManager::GetInstance().GetPoint(1.0, 1.0, 1.0);
	double cross_sec = 2.5;

	InternalTrussElement obj_t = InternalTrussElement(start,end,cross_sec,BASIC);
	InternalBeamElement obj_b  = InternalBeamElement (start,end,cross_sec,BASIC);
}
