/*
 * =====================================================================================
 *
 *       Filename:  StiffnessBuilderTest.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  20/09/16 10:37:03
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jerome Plumat (JP), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "StiffnessBuilderTest.h"
CPPUNIT_TEST_SUITE_REGISTRATION(StiffnessBuilderTest);
StiffnessBuilderTest::StiffnessBuilderTest(){
}

StiffnessBuilderTest::~StiffnessBuilderTest(){
}

void
StiffnessBuilderTest::tearDown(){
}

void
StiffnessBuilderTest::setUp(){
}

void
StiffnessBuilderTest::basic_tests(){
	unsigned int N=2; // two points in the structure
	TrussStiffnessBuilder builder_t = TrussStiffnessBuilder(N);
	BeamStiffnessBuilder builder_b = BeamStiffnessBuilder(N);
}

void
StiffnessBuilderTest::getter_tests(){
	unsigned int N=2; // two points in the structure

	TrussStiffnessBuilder builder_t = TrussStiffnessBuilder(N);
	CPPUNIT_ASSERT_EQUAL_MESSAGE(
		"We expect a stiffness matrix with 36 elements",
		(int)pow(N*TrussType::NDOF,2),
		(int)builder_t.GetStiffnessMatrix().n_elem
	);

	BeamStiffnessBuilder builder_b = BeamStiffnessBuilder(N);
	CPPUNIT_ASSERT_EQUAL_MESSAGE(
		"We expect a stiffness matrix with 144 elements",
		(int)pow(N*BeamType::NDOF,2),
		(int)builder_b.GetStiffnessMatrix().n_elem
	);
}

void
StiffnessBuilderTest::truss_building_tests(){
	arma::umat test;
	// construct a system with 3 point
	int N = 3;

	// each point has 3 degrees of freedom - since SimpleTruss only
	float A = 23E-4; // in m^2, random number, just to have hight values to compare
	TrussStiffnessBuilder k_builder = TrussStiffnessBuilder(N);
	// first truss: from joint 0 and joint 1, coordintes in meters
	Point* a = PointManager::GetInstance().GetPoint(0.0,0.0,0.0);
	Point* b =  PointManager::GetInstance().GetPoint(4.0,0.0,0.0);
	InternalTrussElement truss = InternalTrussElement(a,b,A,TEST);
	float coef = (float) ( truss.GetCrossSection()*truss.GetYoungModulus()/truss.GetLength() );
	StiffnessMatrixType expected = {
					{coef, 0.0, 0.0, -coef, 0.0, 0.0, 0.0, 0.0, 0.0},   // U0
					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},      // V0
					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},      // W0
					{-coef, 0.0, 0.0, coef, 0.0, 0.0, 0.0, 0.0, 0.0},   // U1
					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},      // V1
					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},      // W1
					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
					{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0} };


	k_builder.Build(truss.GetLocalStiffnessMatrix(),truss.GetTransformationMatrix(),0,1);
	//std::cout <<  k_builder.GetStiffnessMatrix() << std::endl;
	test = arma::abs(expected - k_builder.GetStiffnessMatrix() )<1E-6;
	CPPUNIT_ASSERT_EQUAL_MESSAGE(
			"We expect the default stiffness matrix",
			81,
			static_cast<int>(sum(sum(test,1)))
	);

    // add an other truss between joint 1 and 2
    Point* b1 =  PointManager::GetInstance().GetPoint(4.0,6.0,0.0);
    InternalTrussElement truss1 = InternalTrussElement(b,b1,A,TEST);
    float coef1 = (float) ( truss1.GetCrossSection()*truss1.GetYoungModulus()/truss1.GetLength() );
    StiffnessMatrixType expected1 = {
         //  U0   V0   W0   U1   V1   W1   U2   V2   W2
            {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},      // U0
            {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},      // V0
            {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},      // W0
            {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,   0.0},      // U1
            {0.0, 0.0, 0.0, 0.0,coef1, 0.0, 0.0,-coef1,0.0},      // V1
            {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},      // W1
            {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},      // U2
            {0.0, 0.0, 0.0, 0.0,-coef1,0.0, 0.0,coef1, 0.0},      // V2
            {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}       // W2
    };
    StiffnessMatrixType expected_s = expected1;
    expected1 = expected1 + expected;

    k_builder.Build(truss1.GetLocalStiffnessMatrix(),truss1.GetTransformationMatrix(),1,2);
    test = arma::abs(expected1 - k_builder.GetStiffnessMatrix())<1E1; // seems huge EPS but matrix values are order of magnitude of 1E7
    //std::cout <<  k_builder.GetStiffnessMatrix() << std::endl;
    //std::cout <<  expected1 << std::endl;
    //std::cout <<  test << std::endl;
    CPPUNIT_ASSERT_EQUAL_MESSAGE(
				"We expect the sum of the two first stiffness matrices",
				81,
				static_cast<int>(sum(sum(test,1)))
		);

	// add an other truss between joint 0 and 2
	float c = (cos(atan(b1->y/b1->x))), s = ( sin(atan(b1->y/b1->x)) );
	InternalTrussElement truss2 = InternalTrussElement(a,b1,A,TEST);
	float coef2 = (float)(truss2.GetCrossSection()*truss2.GetYoungModulus()/truss2.GetLength());
	StiffnessMatrixType expected2 = {
			 //  U0        V0    W0   U1   V1   W1   U2   V2   W2
			{c*coef2*c,s*coef2*c, 0.0, 0.0, 0.0, 0.0,-c*coef2*c,-s*coef2*c, 0.0},      // U0
			{c*coef2*s,s*coef2*s, 0.0, 0.0, 0.0, 0.0,-s*coef2*c,-s*coef2*s, 0.0},      // V0
			{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},      // W0
			{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},      // U1
			{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},      // V1
			{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},      // W1
			{-c*coef2*c,-s*coef2*c, 0.0, 0.0, 0.0, 0.0,c*coef2*c,s*coef2*c, 0.0},      // V2
			{-s*coef2*c,-s*coef2*s, 0.0, 0.0, 0.0, 0.0,s*coef2*c,s*coef2*s, 0.0},       // U2
			{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}      // W2
	};
	expected2 = expected2 + expected_s + expected;

	k_builder.Build(truss2.GetLocalStiffnessMatrix(),truss2.GetTransformationMatrix(),0,2);
	test = arma::abs(expected2 - k_builder.GetStiffnessMatrix())<1E1;
	//std::cout << k_builder.GetStiffnessMatrix()  << std::endl;
	//std::cout <<  expected2 << std::endl;
	//std::cout <<  test << std::endl;

	CPPUNIT_ASSERT_EQUAL_MESSAGE(
			"We expect to find the sum of the three stiffness matrices.",
			81,
			static_cast<int>(sum(sum(test,1)))
	);
}


