
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

	// truss
	TrussBarElement bar_t = TrussBarElement(start, end, cross_sect, m);
	CPPUNIT_ASSERT_EQUAL_MESSAGE(
		"We expect 2 nodes",
		(unsigned int)2,
		bar_t.GetNumberOfNodes()
	);
	CPPUNIT_ASSERT_EQUAL_MESSAGE(
		"We expect 1 element",
		(unsigned int)1,
		bar_t.GetNumberOfElements()
	);

	// beam
	BeamBarElement bar_b = BeamBarElement(start, end, cross_sect, m);
	CPPUNIT_ASSERT_EQUAL_MESSAGE(
		"We expect 2 nodes",
		(unsigned int)2,
		bar_b.GetNumberOfNodes()
	);
	CPPUNIT_ASSERT_EQUAL_MESSAGE(
		"We expect 1 element",
		(unsigned int)1,
		bar_b.GetNumberOfElements()
	);
}

void
BarElementTest::getter_tests(){
	Point *start = PointManager::GetInstance().GetPoint(0.0,0.0,0.0),
				*end   = PointManager::GetInstance().GetPoint(1.0,1.0,0.0);
	double cross_sect = 24E-4; // in m^2
	Material m = TEST;

	// truss
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

	// beam
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

/*
 * truss_stiffness_tests
 */
void
BarElementTest::truss_stiffness_tests(){
	float x1 = 0.0, y1 = 0.0, z1 = 0.0,
				x2 = 1.0, y2 = 0.0, z2 = 0.0;
	Point *start = PointManager::GetInstance().GetPoint(x1,y1,z1),
				*end   = PointManager::GetInstance().GetPoint(x2,y2,z2);
	double cross_sect = 24E-4; // in m^2
	Material m = TEST;
	arma::umat test;

	TrussBarElement bar_t = TrussBarElement(start, end, cross_sect, m);
	float c = (cos(atan(abs(start->y-end->y)/abs(start->x-end->x)))), 
				s = (sin(atan(abs(start->y-end->y)/abs(start->x-end->x))));
	float coef = (float)(bar_t.GetCrossSection()*bar_t.GetYoungModulus()/bar_t.GetLength());
	StiffnessMatrixType expected = {
			{c*coef*c,s*coef*c,0.0, -c*coef*c,-s*coef*c,0.0},      // U0
			{c*coef*s,s*coef*s,0.0, -s*coef*c,-s*coef*s,0.0},      // V0
			{0.0,0.0,0.0,  0.0,0.0,0.0},      // W0
			{-c*coef*c,-s*coef*c,0.0, c*coef*c,s*coef*c,0.0},      // U0
			{-c*coef*s,-s*coef*s,0.0, s*coef*c,s*coef*s,0.0},      // V0
			{0.0,0.0,0.0,  0.0,0.0,0.0},      // W1
	};
	//std::cout << bar_t.GetStiffnessMatrix() << std::endl;
	//std::cout << "************************" << std::endl;
	//std::cout << expected << std::endl;
	test = arma::abs(bar_t.GetStiffnessMatrix() - expected ) < 1E0 ;
	CPPUNIT_ASSERT_EQUAL_MESSAGE(
		"We expect the 2D stiffness truss matrix",
		36,
		(int)sum(sum(test,1))
	);


	// TODO: test with z coordinates

}// end truss_stiffness_tests

/*
 * beam_stiffness_tests
 */
void
BarElementTest::beam_stiffness_tests(){
	float x1 = 0.0, y1 = 0.0, z1 = 0.0,
				x2 = 1.0, y2 = 0.0, z2 = 0.0;
	double cross_sect = 24E-4; // in m^2
	Material m = TEST;
	arma::umat test;
	Point *start = PointManager::GetInstance().GetPoint(x1,y1,z1),
				*end   = PointManager::GetInstance().GetPoint(x2,y2,z2);
	BeamBarElement bar_b = BeamBarElement(start,end,cross_sect,m);
	float A = bar_b.GetCrossSection(),
			  E = bar_b.GetYoungModulus(),
				L = bar_b.GetLength(),
				G = 0.0,
				J = 0.0;
	std::cout << "TEST: " << A << " - " << E << " - " << L << std::endl;
	StiffnessMatrixType expected = {
		{A*E/L,0.0,0.0, 0.0,0.0,0.0, -A*E/L,0.0,0.0, 0.0,0.0,0.0},
		{0.0,12*E/pow(L,(float)3.0),0.0, 0.0,0.0,6*E/pow(L,(float)2.0), 0.0,-12*E/pow(L,(float)3.0),0.0, 0.0,0.0,6*E/pow(L,(float)2)},
		{0.0,0.0,12*E/pow(L,(float)3), 0.0,-6*E/pow(L,(float)2),0.0, 0.0,0.0,-12*E/pow(L,(float)3), 0.0,-6*E/pow(L,(float)2),0.0},

		{0.0,0.0,0.0, G*J/L,0.0,0.0, 0.0,0.0,0.0, -G*J/L,0.0,0.0},
		{0.0,0.0,-6*E/pow(L,(float)2), 0.0,4*E/L,0.0, 0.0,0.0,6*E/pow(L,(float)2), 0.0,2*E/L,0.0},
		{0.0,6*E/pow(L,(float)2),0.0, 0.0,0.0,4*E/L, 0.0,-6*E/pow(L,(float)2),0.0, 0.0,0.0,2*E/L},

		{-A*E/L,0.0,0.0, 0.0,0.0,0.0, A*E/L,0.0,0.0, 0.0,0.0,0.0},
		{0.0,-12*E/pow(L,(float)3),0.0, 0.0,0.0,-6*E/pow(L,(float)2), 0.0,12*E/pow(L,(float)3),0.0, 0.0,0.0,-6*E/pow(L,(float)2)},
		{0.0,0.0,-12*E/pow(L,(float)3), 0.0,6*E/pow(L,(float)2),0.0, 0.0,0.0,12*E/pow(L,(float)3), 0.0,6*E/pow(L,(float)2),0.0},

		{0.0,0.0,0.0, -G*J/L,0.0,0.0, 0.0,0.0,0.0, G*J/L,0.0,0.0},
		{0.0,0.0,-6*E/pow(L,(float)2), 0.0,2*E/L,0.0, 0.0,0.0,6*E/pow(L,(float)2), 0.0,4*E/L,0.0},
		{0.0,6*E/pow(L,(float)2),0.0, 0.0,0.0,2*E/L, 0.0,-6*E/pow(L,(float)2),0.0, 0.0,0.0,4*E/L},
	};

	test = ( expected - bar_b.GetStiffnessMatrix() )<1E-6;
	//std::cout << bar_b.GetStiffnessMatrix() << std::endl;
	//std::cout << "************************" << std::endl;
	//std::cout << expected << std::endl;
	CPPUNIT_ASSERT_EQUAL_MESSAGE(
		"We expect the 3D beam stiffness matrix",
		144,
		(int)sum(sum(test,1))
	);

}// end beam_stiffness_tests

