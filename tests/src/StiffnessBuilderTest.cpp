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


void StiffnessBuilderTest::simple_truss_structure_building_tests(void){
	// TODO
}

void StiffnessBuilderTest::beam_building_tests(void){
	/*
	 * Study case:
	 *
	 * .---------.---------
	 * /\        /\         
	 *
	 * |_________|_________|
	 *      2m        2m
	 *
	 * BarElementTest::truss_stiffness_tests
	 * Numerical solutions have been generated by the Matlab code presented in 
	 * "A 3D Finite Element modeling composite wind tubine wings" by R. DE FRIA LOPE.
	 */
	Point *p0 = PointManager::GetInstance().GetPoint(0.0,0.0,0.0),
	      *p1 = PointManager::GetInstance().GetPoint(2.0,0.0,0.0),
	      *p2 = PointManager::GetInstance().GetPoint(4.0,0.0,0.0);

	float cross_sec =  2300E-6, // in m^2
				alpha = 0.0;

	int N = 3; // number of points
	arma::umat test;
	StiffnessMatrixType expected;


	InternalBeamElement el_b1 = InternalBeamElement( p0, p1, cross_sec, TEST, alpha );
	InternalBeamElement el_b2 = InternalBeamElement( p1, p2, cross_sec, TEST, alpha );

	BeamStiffnessBuilder builder_b = BeamStiffnessBuilder(N);
	builder_b.Build(el_b1.GetLocalStiffnessMatrix(), el_b1.GetTransformationMatrix(), 0, 1 );
	builder_b.Build(el_b2.GetLocalStiffnessMatrix(), el_b2.GetTransformationMatrix(), 1, 2 );

	// expected is a N*DOF = 18x18
	expected = {
		{230000000, 0.0, 0.0, 0.0, 0.0, 0.0, -230000000, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
		{0.0, 300000000000.000, 0.0, 0.0, 0.0, 300000000000.000, 0.0, -300000000000.000, 0.0, 0.0, 0.0, 300000000000.000, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
		{0.0, 0.0, 300000000000.000, 0.0, -300000000000.000, 0.0, 0.0, 0.0, -300000000000.000, 0.0, -300000000000.000, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
		{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
		{0.0, 0.0, -300000000000.000, 0.0, 400000000000.000, 0.0, 0.0, 0.0, 300000000000.000, 0.0, 200000000000.000, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
		{0.0, 300000000000.000, 0.0, 0.0, 0.0, 400000000000.000, 0.0, -300000000000.000, 0.0, 0.0, 0.0, 200000000000.000, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
		{-230000000, 0.0, 0.0, 0.0, 0.0, 0.0, 460000000, 0.0, 0.0, 0.0, 0.0, 0.0, -230000000, 0.0, 0.0, 0.0, 0.0, 0.0},
		{0.0, -300000000000.000, 0.0, 0.0, 0.0, -300000000000.000, 0.0, 600000000000.000, 0.0, 0.0, 0.0, 0.0, 0.0, -300000000000.000, 0.0, 0.0, 0.0, 300000000000.000},
		{0.0, 0.0, -300000000000.000, 0.0, 300000000000.000, 0.0, 0.0, 0.0, 600000000000.000, 0.0, 0.0, 0.0, 0.0, 0.0, -300000000000.000, 0.0, -300000000000.000, 0.0},
		{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
		{0.0, 0.0, -300000000000.000, 0.0, 200000000000.000, 0.0, 0.0, 0.0, 0.0, 0.0, 800000000000.000, 0.0, 0.0, 0.0, 300000000000.000, 0.0, 200000000000.000, 0.0},
		{0.0, 300000000000.000, 0.0, 0.0, 0.0, 200000000000.000, 0.0, 0.0, 0.0, 0.0, 0.0, 800000000000.000, 0.0, -300000000000.000, 0.0, 0.0, 0.0, 200000000000.000},
		{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -230000000, 0.0, 0.0, 0.0, 0.0, 0.0, 230000000, 0.0, 0.0, 0.0, 0.0, 0.0},
		{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -300000000000.000, 0.0, 0.0, 0.0, -300000000000.000, 0.0, 300000000000.000, 0.0, 0.0, 0.0, -300000000000.000},
		{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -300000000000.000, 0.0, 300000000000.000, 0.0, 0.0, 0.0, 300000000000.000, 0.0, 300000000000.000, 0.0},
		{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
		{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -300000000000.000, 0.0, 200000000000.000, 0.0, 0.0, 0.0, 300000000000.000, 0.0, 400000000000.000, 0.0},
		{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 300000000000.000, 0.0, 0.0, 0.0, 200000000000.000, 0.0, -300000000000.000, 0.0, 0.0, 0.0, 400000000000.000}
	};

	test = arma::abs(expected - builder_b.GetStiffnessMatrix()) < 1E1;

	//std::cout << builder_b.GetStiffnessMatrix() << std::endl;
	//std::cout << "============================" << std::endl;
	//std::cout << test << std::endl;
	//std::cout << "============================" << std::endl;
	CPPUNIT_ASSERT_EQUAL_MESSAGE(
			"We expect the stiffness matrix of two horizontal beams." ,
			18*18,
			static_cast<int>(sum(sum(test,1)))
	);
}

void
StiffnessBuilderTest::triangle_beam_structure_building_tests(void){

	/*
	 * Study case:
	 *
	 *           _
	 *     /|    |
	 *    / |    | 2m
	 *   /  |    |
	 *   ----    -
	 * /// ///
	 *
	 * |-----|
	 *   3.5m
	 *
	 * Numerical solutions have been generated by the Matlab code presented in 
	 * "A 3D Finite Element modeling composite wind tubine wings" by R. DE FRIA LOPE.
	 */   
	double cross_sec = 24E-4; // in m^2
	Material m = TEST; // E = 1;

	std::vector<float> x_vect = {0.0, 3.5, 3.5 };
	std::vector<float> y_vect = {0.0, 0.0, 2.0 };
	std::vector<float> z_vect = {0.0, 0.0, 0.0 };
	
	// Points defining the beams
	Point *start, *end;

	// beam alpha angle
	float alpha = 0.0;

	// variables
	unsigned int i=0, // loop variable
							 N = x_vect.size(); // nbr of nodes

	StiffnessMatrixType expected = StiffnessMatrixType(18,18,arma::fill::zeros);
	arma::umat test;

	// stiffness matrix builder
	BeamStiffnessBuilder builder = BeamStiffnessBuilder(N);

	start = PointManager::GetInstance().GetPoint( x_vect.at(i), y_vect.at(i), z_vect.at(i) );
	end = PointManager::GetInstance().GetPoint( x_vect.at(i+1), y_vect.at(i+1), z_vect.at(i+1) );
	BeamBarElement b = BeamBarElement( start, end, cross_sec, m, alpha );
	builder.Build( b.GetStiffnessMatrix(), i, i+1);
	expected = {
		{137142857.142857, 0, 0, 0, 0, 0, -137142857.142857, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 55976676384.8397, 0, 0, 0, 97959183673.4694, 0, -55976676384.8397, 0, 0, 0, 97959183673.4694, 0, 0, 0, 0, 0, 0},
		{0, 0, 55976676384.8396, 0, -97959183673.4694, 0, 0, 0, -55976676384.8396, 0, -97959183673.4694, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, -97959183673.4694, 0, 228571428571.429, 0, 0, 0, 97959183673.4694, 0, 114285714285.714, 0, 0, 0, 0, 0, 0, 0},
		{0, 97959183673.4694, 0, 0, 0, 228571428571.428, 0, -97959183673.4694, 0, 0, 0, 114285714285.714, 0, 0, 0, 0, 0, 0},
		{-137142857.142857, 0, 0, 0, 0, 0, 137142857.142857, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, -55976676384.8397, 0, 0, 0, -97959183673.4694, 0, 55976676384.8397, 0, 0, 0, -97959183673.4694, 0, 0, 0, 0, 0, 0},
		{0, 0, -55976676384.8396, 0, 97959183673.4694, 0, 0, 0, 55976676384.8396, 0, 97959183673.4694, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, -97959183673.4694, 0, 114285714285.714, 0, 0, 0, 97959183673.4694, 0, 228571428571.429, 0, 0, 0, 0, 0, 0, 0},
		{0, 97959183673.4694, 0, 0, 0, 114285714285.714, 0, -97959183673.4694, 0, 0, 0, 228571428571.428, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
	};
	test = arma::abs( expected - builder.GetStiffnessMatrix() )<1E-3;
	//std::cout <<  arma::abs( expected - builder.GetStiffnessMatrix() ) << std::endl;
	CPPUNIT_ASSERT_EQUAL_MESSAGE(
			"We expect the stiffness matrix for the first bar of the triangle." ,
			18*18,
			static_cast<int>(sum(sum(test,1)))
	);


	i++;
	start = PointManager::GetInstance().GetPoint( x_vect.at(i), y_vect.at(i), z_vect.at(i) );
	end = PointManager::GetInstance().GetPoint( x_vect.at(i+1), y_vect.at(i+1), z_vect.at(i+1) );
	BeamBarElement b2 = BeamBarElement( start, end, cross_sec, m, alpha );
	builder.Build( b2.GetStiffnessMatrix(), i, i+1);
	expected = {
		{137142857.142857, 0, 0, 0, 0, 0, -137142857.142857, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 55976676384.8397, 0, 0, 0, 97959183673.4694, 0, -55976676384.8397, 0, 0, 0, 97959183673.4694, 0, 0, 0, 0, 0, 0},
		{0, 0, 55976676384.8396, 0, -97959183673.4694, 0, 0, 0, -55976676384.8396, 0, -97959183673.4694, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, -97959183673.4694, 0, 228571428571.429, 0, 0, 0, 97959183673.4694, 0, 114285714285.714, 0, 0, 0, 0, 0, 0, 0},
		{0, 97959183673.4694, 0, 0, 0, 228571428571.428, 0, -97959183673.4694, 0, 0, 0, 114285714285.714, 0, 0, 0, 0, 0, 0},
		{-137142857.142857, 0, 0, 0, 0, 0, 137142857.142857, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, -55976676384.8397, 0, 0, 0, -97959183673.4694, 0, 56216676384.8397, 0, 0, 0, -97959183673.4694, 0, -240000000.000000, 0, 0, 0, 0},
		{0, 0, -55976676384.8396, 0, 97959183673.4694, 0, 0, 0, 55976676384.8396, 0, 97959183673.4694, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, -97959183673.4694, 0, 114285714285.714, 0, 0, 0, 97959183673.4694, 0, 228571428571.429, 0, 0, 0, 0, 0, 9.86076131526265e-21, 0},
		{0, 97959183673.4694, 0, 0, 0, 114285714285.714, 0, -97959183673.4694, 0, 0, 0, 228571428571.428, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, -240000000.000000, 0, 0, 0, 0, 0, 240000000.000000, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9.86076131526265e-21, 0, 0, 0, 0, 0, 1.97215226305253e-20, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
	};
	test = arma::abs( expected - builder.GetStiffnessMatrix() )<1E-3;
	//std::cout <<  arma::abs( expected - builder.GetStiffnessMatrix() ) << std::endl;
	CPPUNIT_ASSERT_EQUAL_MESSAGE(
			"We expect the stiffness matrix for the 1st and 2nd bar of the triangle." ,
			18*18,
			static_cast<int>(sum(sum(test,1)))
	);

	// WARNING: cyclic structure -> last point is the first
	i++;
	start = PointManager::GetInstance().GetPoint( x_vect.at(i), y_vect.at(i), z_vect.at(i) );
	end = PointManager::GetInstance().GetPoint( x_vect.at(0), y_vect.at(0), z_vect.at(0) );
	BeamBarElement b3 = BeamBarElement( start, end, cross_sec, m, alpha );
	builder.Build( b3.GetStiffnessMatrix(), i, 0);
	expected = {
		{9245478731.76648, -15731209426.4815, 0, 0, 0, -36637952370.9662, -137142857.142857, 0, 0, 0, 0, 0, -9108335874.62362, 15731209426.4815, 0, 0, 0, -36637952370.9662},
		{-15731209426.4815, 83625366226.3879, 0, 0, 0, 162075600322.660, 0, -55976676384.8397, 0, 0, 0, 97959183673.4694, 15731209426.4815, -27648689841.5482, 0, 0, 0, 64116416649.1909},
		{0, 0, 92614628755.8058, 36637952370.9662, -162075600322.660, 0, 0, 0, -55976676384.8396, 0, -97959183673.4694, 0, 0, 0, -36637952370.9662, 36637952370.9662, -64116416649.1909, 0},
		{0, 0, 36637952370.9662, 48850603161.2882, -85488555532.2545, 0, 0, 0, 0, 0, 0, 0, 0, 0, -36637952370.9662, 24425301580.6441, -42744277766.1272, 0},
		{0, 0, -162075600322.660, -85488555532.2545, 378176400752.874, 0, 0, 0, 97959183673.4694, 0, 114285714285.714, 0, 0, 0, 64116416649.1909, -42744277766.1272, 74802486090.7227, 0},
		{-36637952370.9662, 162075600322.660, 0, 0, 0, 427027003914.162, 0, -97959183673.4694, 0, 0, 0, 114285714285.714, 36637952370.9662, -64116416649.1909, 0, 0, 0, 99227787671.3667},
		{-137142857.142857, 0, 0, 0, 0, 0, 137142857.142857, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, -55976676384.8397, 0, 0, 0, -97959183673.4694, 0, 56216676384.8397, 0, 0, 0, -97959183673.4694, 0, -240000000.000000, 0, 0, 0, 0},
		{0, 0, -55976676384.8396, 0, 97959183673.4694, 0, 0, 0, 55976676384.8396, 0, 97959183673.4694, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, -97959183673.4694, 0, 114285714285.714, 0, 0, 0, 97959183673.4694, 0, 228571428571.429, 0, 0, 0, 0, 0, 9.86076131526265e-21, 0},
		{0, 97959183673.4694, 0, 0, 0, 114285714285.714, 0, -97959183673.4694, 0, 0, 0, 228571428571.428, 0, 0, 0, 0, 0, 0},
		{-9108335874.62362, 15731209426.4815, 0, 0, 0, 36637952370.9662, 0, 0, 0, 0, 0, 0, 9108335874.62362, -15731209426.4815, 0, 0, 0, 36637952370.9662},
		{15731209426.4815, -27648689841.5482, 0, 0, 0, -64116416649.1909, 0, -240000000.000000, 0, 0, 0, 0, -15731209426.4815, 27888689841.5482, 0, 0, 0, -64116416649.1909},
		{0, 0, -36637952370.9662, -36637952370.9662, 64116416649.1909, 0, 0, 0, 0, 0, 0, 0, 0, 0, 36637952370.9662, -36637952370.9662, 64116416649.1909, 0},
		{0, 0, 36637952370.9662, 24425301580.6441, -42744277766.1272, 0, 0, 0, 0, 0, 0, 0, 0, 0, -36637952370.9662, 48850603161.2882, -85488555532.2545, 0},
		{0, 0, -64116416649.1909, -42744277766.1272, 74802486090.7227, 0, 0, 0, 0, 0, 9.86076131526265e-21, 0, 0, 0, 64116416649.1909, -85488555532.2545, 149604972181.445, 0},
		{-36637952370.9662, 64116416649.1909, 0, 0, 0, 99227787671.3667, 0, 0, 0, 0, 0, 0, 36637952370.9662, -64116416649.1909, 0, 0, 0, 198455575342.734}
	};

 // error between Matlab results and float precision in C++, all errors are c*1048 with c an interger
 // to prevent this, use BASIC material
	test = arma::abs( expected - builder.GetStiffnessMatrix() )<1E4;
	//std::cout << b3.GetStiffnessMatrix() << std::endl;
	//std::cout << " =================================================================== " << std::endl;
	//std::cout <<  arma::abs( expected - builder.GetStiffnessMatrix() ) << std::endl;
	//std::cout << " =================================================================== " << std::endl;
	//std::cout <<  builder.GetStiffnessMatrix() << std::endl;
	CPPUNIT_ASSERT_EQUAL_MESSAGE(
			"We expect the stiffness matrix for the whole triangle." ,
			18*18,
			static_cast<int>(sum(sum(test,1)))
	);

}

void
StiffnessBuilderTest::frame_beam_structre_building_tests(void){
	/*
	 *             _
	 *     /\     | 1.5m
	 *    /  \    |_
	 *   |    |   | 2m
	 *   |    |   |
	 *  ///  ///   -
	 *
	 *   |----|
	 *     2m
	 *
	 * frame with 8 BarElement
	 *
	 * Numerical solutions have been generated by the Matlab code presented in 
	 * "A 3D Finite Element modeling composite wind tubine wings" by R. DE FRIA LOPE.
	 */
	double cross_sec = 24E-4; // in m^2
	Material m = BASIC; // E = 1;

	// node coordinates
	std::vector<float> x_vect = {0.0, 0.0, 0.0, 0.50, 1.0, 1.50, 2.0, 2.0, 2.0};
	std::vector<float> y_vect = {0.0, 1.0, 2.0, 2.75, 3.5, 2.75, 2.0, 1.0, 0.0};
	std::vector<float> z_vect = {0.0, 0.0, 0.0, 0.00, 0.0, 0.00, 0.0, 0.0, 0.0};

	// Points defining the beams
	Point *start, *end;

	// beam alpha angle
	float alpha = 0.0;

	// variables
	unsigned int i=0, // loop variable
							 N = x_vect.size(); // nbr of nodes

	// Stiffness matrix builder
	BeamStiffnessBuilder builder = BeamStiffnessBuilder(N);

	// construct the structure
	for( i=0; i<N-1; i++){
		start = PointManager::GetInstance().GetPoint( x_vect.at(i), y_vect.at(i), z_vect.at(i) );
		end = PointManager::GetInstance().GetPoint( x_vect.at(i+1), y_vect.at(i+1), z_vect.at(i+1) );

		BeamBarElement bar = BeamBarElement(start, end, cross_sec, m, alpha);

		//std::cout << " ===================================================================================== " << std::endl;
		//std::cout << i << " - s: " << start->x << ", " << start->y << ", " << start->z << "\te: " << end->x <<", " << end->y << ", " <<end->z << std::endl;
		//std::cout << bar.GetStiffnessMatrix() << std::endl;
		//std::cout << " ===================================================================================== " << std::endl;

		builder.Build( bar.GetStiffnessMatrix(), i, i+1 );
	}//end for loop

	StiffnessMatrixType stiffness = builder.GetStiffnessMatrix(),
											expected = StiffnessMatrixType(54,54,arma::fill::zeros);

	expected = {
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0.00240000000000000, 0, 0, 0, 0, 0, -0.00240000000000000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 1.97215226305253e-31, 0, 0, 0, 0, 0, 9.86076131526265e-32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, -0.00240000000000000, 0, 0, 0, 0, 0, 0.00480000000000000, 0, 0, 0, 0, 0, -0.00240000000000000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 9.86076131526265e-32, 0, 0, 0, 0, 0, 3.94430452610506e-31, 0, 0, 0, 0, 0, 9.86076131526265e-32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11.3442741498424, -7.56107439260036, 0, 0, 0, -6.14437140434100, -11.3442741498424, 7.56107439260036, 0, 0, 0, -6.14437140434100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, -0.00240000000000000, 0, 0, 0, 0, -7.56107439260036, 5.04577882267546, 0, 0, 0, 4.09624760289400, 7.56107439260036, -5.04337882267546, 0, 0, 0, 4.09624760289400, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16.3849904115760, 6.14437140434100, -4.09624760289400, 0, 0, 0, -16.3849904115760, 6.14437140434100, -4.09624760289400, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6.14437140434100, 3.07218570217050, -2.04812380144700, 0, 0, 0, -6.14437140434100, 1.53609285108525, -1.02406190072350, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9.86076131526265e-32, 0, 0, 0, -4.09624760289400, -2.04812380144700, 1.36541586763133, 0, 0, 0, 4.09624760289400, -1.02406190072350, 0.682707933815667, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -6.14437140434100, 4.09624760289400, 0, 0, 0, 4.43760156980183, 6.14437140434100, -4.09624760289400, 0, 0, 0, 2.21880078490092, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -11.3442741498424, 7.56107439260036, 0, 0, 0, 6.14437140434100, 22.6885482996848, -15.1221487852007, 0, 0, 0, 0, -11.3442741498424, 7.56107439260036, 0, 0, 0, -6.14437140434100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7.56107439260036, -5.04337882267546, 0, 0, 0, -4.09624760289400, -15.1221487852007, 10.0867576453509, 0, 0, 0, 0, 7.56107439260036, -5.04337882267546, 0, 0, 0, 4.09624760289400, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -16.3849904115760, -6.14437140434100, 4.09624760289400, 0, 0, 0, 32.7699808231520, 0, 0, 0, 0, 0, -16.3849904115760, 6.14437140434100, -4.09624760289400, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6.14437140434100, 1.53609285108525, -1.02406190072350, 0, 0, 0, 0, 6.14437140434100, -4.09624760289400, 0, 0, 0, -6.14437140434100, 1.53609285108525, -1.02406190072350, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -4.09624760289400, -1.02406190072350, 0.682707933815667, 0, 0, 0, 0, -4.09624760289400, 2.73083173526267, 0, 0, 0, 4.09624760289400, -1.02406190072350, 0.682707933815667, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -6.14437140434100, 4.09624760289400, 0, 0, 0, 2.21880078490092, 0, 0, 0, 0, 0, 8.87520313960366, 6.14437140434100, -4.09624760289400, 0, 0, 0, 2.21880078490092, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -11.3442741498424, 7.56107439260036, 0, 0, 0, 6.14437140434100, 22.6885482996848, 0, 0, 0, 0, 12.2887428086820, -11.3442741498424, -7.56107439260036, 0, 0, 0, 6.14437140434100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7.56107439260036, -5.04337882267546, 0, 0, 0, -4.09624760289400, 0, 10.0867576453509, 0, 0, 0, 0, -7.56107439260036, -5.04337882267546, 0, 0, 0, 4.09624760289400, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -16.3849904115760, -6.14437140434100, 4.09624760289400, 0, 0, 0, 32.7699808231520, -12.2887428086820, 0, 0, 0, 0, -16.3849904115760, -6.14437140434100, -4.09624760289400, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6.14437140434100, 1.53609285108525, -1.02406190072350, 0, 0, 0, -12.2887428086820, 6.14437140434100, 0, 0, 0, 0, 6.14437140434100, 1.53609285108525, 1.02406190072350, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -4.09624760289400, -1.02406190072350, 0.682707933815667, 0, 0, 0, 0, 0, 2.73083173526267, 0, 0, 0, 4.09624760289400, 1.02406190072350, 0.682707933815667, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -6.14437140434100, 4.09624760289400, 0, 0, 0, 2.21880078490092, 12.2887428086820, 0, 0, 0, 0, 8.87520313960366, -6.14437140434100, -4.09624760289400, 0, 0, 0, 2.21880078490092, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -11.3442741498424, -7.56107439260036, 0, 0, 0, -6.14437140434100, 22.6885482996848, 15.1221487852007, 0, 0, 0, 0, -11.3442741498424, -7.56107439260036, 0, 0, 0, 6.14437140434100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -7.56107439260036, -5.04337882267546, 0, 0, 0, -4.09624760289400, 15.1221487852007, 10.0867576453509, 0, 0, 0, 0, -7.56107439260036, -5.04337882267546, 0, 0, 0, 4.09624760289400, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -16.3849904115760, 6.14437140434100, 4.09624760289400, 0, 0, 0, 32.7699808231520, 0, 0, 0, 0, 0, -16.3849904115760, -6.14437140434100, -4.09624760289400, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -6.14437140434100, 1.53609285108525, 1.02406190072350, 0, 0, 0, 0, 6.14437140434100, 4.09624760289400, 0, 0, 0, 6.14437140434100, 1.53609285108525, 1.02406190072350, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -4.09624760289400, 1.02406190072350, 0.682707933815667, 0, 0, 0, 0, 4.09624760289400, 2.73083173526267, 0, 0, 0, 4.09624760289400, 1.02406190072350, 0.682707933815667, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6.14437140434100, 4.09624760289400, 0, 0, 0, 2.21880078490092, 0, 0, 0, 0, 0, 8.87520313960366, -6.14437140434100, -4.09624760289400, 0, 0, 0, 2.21880078490092, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -11.3442741498424, -7.56107439260036, 0, 0, 0, -6.14437140434100, 11.3442741498424, 7.56107439260036, 0, 0, 0, -6.14437140434100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -7.56107439260036, -5.04337882267546, 0, 0, 0, -4.09624760289400, 7.56107439260036, 5.04577882267546, 0, 0, 0, -4.09624760289400, 0, -0.00240000000000000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -16.3849904115760, 6.14437140434100, 4.09624760289400, 0, 0, 0, 16.3849904115760, 6.14437140434100, 4.09624760289400, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -6.14437140434100, 1.53609285108525, 1.02406190072350, 0, 0, 0, 6.14437140434100, 3.07218570217050, 2.04812380144700, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -4.09624760289400, 1.02406190072350, 0.682707933815667, 0, 0, 0, 4.09624760289400, 2.04812380144700, 1.36541586763133, 0, 0, 0, 0, 0, 9.86076131526265e-32, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6.14437140434100, 4.09624760289400, 0, 0, 0, 2.21880078490092, -6.14437140434100, -4.09624760289400, 0, 0, 0, 4.43760156980183, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -0.00240000000000000, 0, 0, 0, 0, 0, 0.00480000000000000, 0, 0, 0, 0, 0, -0.00240000000000000, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9.86076131526265e-32, 0, 0, 0, 0, 0, 3.94430452610506e-31, 0, 0, 0, 0, 0, 9.86076131526265e-32, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -0.00240000000000000, 0, 0, 0, 0, 0, 0.00240000000000000, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9.86076131526265e-32, 0, 0, 0, 0, 0, 1.97215226305253e-31, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
	};

	//std::cout << stiffness << std::endl;
	//std::cout << " ================================================================= " << std::endl;
	//std::cout << arma::abs(expected - stiffness)<< std::endl;

	arma::umat test = arma::abs(expected - stiffness)<1E-3;
	CPPUNIT_ASSERT_EQUAL_MESSAGE(
			"We expect the stiffness matrix of a simple frame with Beams." ,
			(int)(N*6*N*6),
			static_cast<int>(sum(sum(test,1)))
	);

}// end frame_beam_structre_building_tests


void StiffnessBuilderTest::beam_building_file_tests(void){
	/*
	 * Study case:
	 *
	 * .---------.---------
	 * /\        /\         
	 *
	 * |_________|_________|
	 *      2m        2m
	 *
	 * BarElementTest::truss_stiffness_tests
	 * Numerical solutions have been generated by the Matlab code presented in 
	 * "A 3D Finite Element modeling composite wind tubine wings" by R. DE FRIA LOPE.
	 */
	Point *p0 = PointManager::GetInstance().GetPoint(0.0,0.0,0.0),
	      *p1 = PointManager::GetInstance().GetPoint(2.0,0.0,0.0),
	      *p2 = PointManager::GetInstance().GetPoint(4.0,0.0,0.0);

	float cross_sec =  2300E-6, // in m^2
				alpha = 0.0;

	int N = 3; // number of points
	arma::umat test;
	StiffnessMatrixType expected;


	InternalBeamElement el_b1 = InternalBeamElement( p0, p1, cross_sec, BASIC, alpha );
	InternalBeamElement el_b2 = InternalBeamElement( p1, p2, cross_sec, BASIC, alpha );

	BeamStiffnessBuilder builder_b = BeamStiffnessBuilder(N);
	builder_b.Build(el_b1.GetLocalStiffnessMatrix(), el_b1.GetTransformationMatrix(), 0, 1 );
	builder_b.Build(el_b2.GetLocalStiffnessMatrix(), el_b2.GetTransformationMatrix(), 1, 2 );

	bool check = expected.load("../tests/data/Kg_two_horizontal_beams.mat");
	CPPUNIT_ASSERT_EQUAL_MESSAGE(
			"We couldn't open the file Kg_two_horizontal_beams, may be you haven't run Matlab script",
			check,
			true
	);

	test = arma::abs(expected - builder_b.GetStiffnessMatrix())<1E-3;

	//std::cout << expected << std::endl;
	//std::cout << "==============================================" << std::endl;
	//std::cout << builder_b.GetStiffnessMatrix() << std::endl;
	//std::cout << "==============================================" << std::endl;
	//std::cout << test << std::endl;

	CPPUNIT_ASSERT_EQUAL_MESSAGE(
			"We expect to find the same stiffness matrix as the file.",
			(int)(N*6*N*6),
			static_cast<int>(sum(sum(test,1)))
	);
	

}

void StiffnessBuilderTest::triangle_beam_structure_building_file_tests(void){
	/*
	 * Study case:
	 *
	 *           _
	 *     /|    |
	 *    / |    | 2m
	 *   /  |    |
	 *   ----    -
	 * /// ///
	 *
	 * |-----|
	 *   3.5m
	 *
	 * Numerical solutions have been generated by the Matlab code presented in 
	 * "A 3D Finite Element modeling composite wind tubine wings" by R. DE FRIA LOPE.
	 */
	double cross_sec = 24E-4; // in m^2
	Material m = BASIC; // E = 1;

	std::vector<float> x_vect = {0.0, 3.5, 3.5 };
	std::vector<float> y_vect = {0.0, 0.0, 2.0 };
	std::vector<float> z_vect = {0.0, 0.0, 0.0 };
	
	// Points defining the beams
	Point *start, *end;

	// beam alpha angle
	float alpha = 0.0;

	// variables
	unsigned int i=0, // loop variable
							 N = x_vect.size(); // nbr of nodes

	StiffnessMatrixType expected;
	arma::umat test;
	BeamStiffnessBuilder builder = BeamStiffnessBuilder(N);

	bool check = expected.load("../tests/data/Kg_triangle_beams.mat");
	CPPUNIT_ASSERT_EQUAL_MESSAGE(
			"We couldn't open the file Kg_triangle_beams, may be you haven't run Matlab script...",
			check,
			true
	);

	// WARNING: cyclic structure -> last point is the first
	for(i=0; i<x_vect.size()-1; i++){
		start = PointManager::GetInstance().GetPoint( x_vect.at(i), y_vect.at(i), z_vect.at(i) );
		end = PointManager::GetInstance().GetPoint( x_vect.at(i+1), y_vect.at(i+1), z_vect.at(i+1) );
		BeamBarElement b = BeamBarElement( start, end, cross_sec, m, alpha );
		builder.Build( b.GetStiffnessMatrix(), i, i+1);
	}

	start = PointManager::GetInstance().GetPoint( x_vect.at(i), y_vect.at(i), z_vect.at(i) );
	end = PointManager::GetInstance().GetPoint( x_vect.at(0), y_vect.at(0), z_vect.at(0) );
	BeamBarElement b3 = BeamBarElement( start, end, cross_sec, m, alpha );
	builder.Build( b3.GetStiffnessMatrix(), i, 0);

	test = arma::abs(expected-builder.GetStiffnessMatrix())<1E-3;
	std::cout << expected << std::endl;
	std::cout << "==============================================" << std::endl;
	std::cout << builder.GetStiffnessMatrix() << std::endl;
	std::cout << "==============================================" << std::endl;
	std::cout << test << std::endl;
	CPPUNIT_ASSERT_EQUAL_MESSAGE(
			"We expect to find the same stiffness matrix as the file.",
			(int)(N*6*N*6),
			static_cast<int>(sum(sum(test,1)))
	);
}

void StiffnessBuilderTest::frame_beam_structre_building_file_tests(void){
	//TODO
}

