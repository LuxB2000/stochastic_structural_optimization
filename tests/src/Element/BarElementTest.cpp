
#include "BarElementTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(BarElementTest);

BarElementTest::BarElementTest(){
}

BarElementTest::~BarElementTest(){
}

void
BarElementTest::tearDown(){
}

void
BarElementTest::setUp(){
}

void
BarElementTest::basic_tests(){
	Point *start = PointManager::GetInstance().GetPoint(0.0,0.0,0.0),
				*end   = PointManager::GetInstance().GetPoint(1.0,0.0,0.0);
	double cross_sect = 24E-4; // in m^2
	Material m = TEST;
	TrussBarElement bar_t = TrussBarElement(start, end, cross_sect, m);
	BeamBarElement bar_b = BeamBarElement(start, end, cross_sect, m);
}

void
BarElementTest::getter_tests(){
	Point *start = PointManager::GetInstance().GetPoint(0.0,0.0,0.0),
				*end   = PointManager::GetInstance().GetPoint(1.0,1.0,0.0);
	double cross_sect = 24E-4; // in m^2
	Material m = TEST;
	TrussBarElement bar_t = TrussBarElement(start, end, cross_sect, m);
	CPPUNIT_ASSERT_EQUAL_MESSAGE(
		"We expect a length equal to sqrt(2)",
		sqrt(2.0),
		bar_t.GetLength()
	);
	CPPUNIT_ASSERT_EQUAL_MESSAGE(
		"We expect a stiffness matrix with 36 elements",
		36,
		(int)bar_t.GetStiffnessMatrix().n_elem
	);


	BeamBarElement bar_b = BeamBarElement(start, end, cross_sect, m);
	CPPUNIT_ASSERT_EQUAL_MESSAGE(
		"We expect a length equal to sqrt(2)",
		sqrt(2.0),
		bar_b.GetLength()
	);
	CPPUNIT_ASSERT_EQUAL_MESSAGE(
		"We expect a stiffness matrix with 144 elements",
		144,
		(int)bar_b.GetStiffnessMatrix().n_elem
	);

}// end getter_tests

