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
	// stiffness
	CPPUNIT_ASSERT_MESSAGE("The stiffness matrix should be initialized",
			ctruss.GetStiffnessMatrixInGlobalCoordPointer()); // check if pointer is not null
	CPPUNIT_ASSERT_EQUAL_MESSAGE("The stiffness should a 9x9 matrix",
			81,static_cast<int>(ctruss.GetStiffnessMatrixInGlobalCoordPointer()->n_elem));
 // force
	CPPUNIT_ASSERT_MESSAGE("The force vector should be initialized",
			ctruss.GetNodalForcesPointer() );
	CPPUNIT_ASSERT_EQUAL_MESSAGE("The force vector should a 1x9 matrix",
			9,static_cast<int>(ctruss.GetNodalForcesPointer()->n_elem));
	// displacements
	CPPUNIT_ASSERT_MESSAGE("The disp. vector should be initialized",
			ctruss.GetDisplacementInLocalCoordinatesPointer());
	CPPUNIT_ASSERT_EQUAL_MESSAGE("The disp. vector should a 1x9 matrix",
			9,static_cast<int>(ctruss.GetDisplacementInLocalCoordinatesPointer()->n_elem));
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

void SimpleCornerTrussTest::stiffness_tests(){
	Point p0 = Point(0.0,0.0,0.0);
	Point p1 = Point(0.5,1.0,0.0);
	Point p2 = Point(2.0,2.3,0.0);
	float area = 0.00002; // in mm^2
	float c0 = 0.0, s0 = 0.0, c1 =0.0, s1 = 0.0,
				 coef0 = 0.0, coef1 = 0.0;
	Material m = TEST;
  arma::umat test;

	// main object
	SimpleCornerTruss ctruss = SimpleCornerTruss( &p0, &p1, &p2, area, m);

	// expected answer
	c0 = cos(atan(sqrt(pow(p1.y-p0.y,2.0))/sqrt(pow(p1.x-p0.x,2)) ));
	s0 = sin(atan(sqrt(pow(p1.y-p0.y,2.0))/sqrt(pow(p1.x-p0.x,2)) ));
	c1 = cos(atan(sqrt(pow(p1.y-p2.y,2.0))/sqrt(pow(p1.x-p2.x,2)) ));
	s1 = sin(atan(sqrt(pow(p1.y-p2.y,2.0))/sqrt(pow(p1.x-p2.x,2)) ));
	coef0 = ctruss.GetYoungModulus()*area/sqrt( pow(p0.x-p1.x,2)+pow(p0.y-p1.y,2) + pow(p0.z-p1.z,2) );
	coef1 = ctruss.GetYoungModulus()*area/sqrt( pow(p2.x-p1.x,2)+pow(p2.y-p1.y,2) + pow(p2.z-p1.z,2) );
	StiffnessMatrixType expected = {
		// U0 V0 W0 U1 V1 W1 U2 V2 W2 
	{c0*coef0*c0,s0*coef0*c0, 0.0, -c0*coef0*c0, -s0*coef0*c0, 0.0, 0.0, 0.0, 0.0},      // U0
	{c0*coef0*s0,s0*coef0*s0, 0.0, -s0*coef0*c0, -s0*coef0*s0, 0.0, 0.0, 0.0, 0.0},      // V0
	{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},      // W0
	{-c0*coef0*c0,-s0*coef0*c0, 0.0, c0*coef0*c0+c1*c1*coef1, s0*coef0*c0+s1*c1*coef1, 0.0, -c1*c1*coef1, -s1*c1*coef1, 0.0},      // U1
	{-c0*coef0*s0,-s0*coef0*s0, 0.0, s0*coef0*c0+s1*coef1*c1, s0*coef0*s0+s1*s1*coef1, 0.0, -c1*s1*coef1, -s1*s1*coef1, 0.0},      // V1
	{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},      // W1
	{ 0.0, 0.0, 0.0, -c1*coef1*c1,-s1*coef1*c1, 0.0,c1*coef1*c1,s1*coef1*c1, 0.0},      // V2
	{ 0.0, 0.0, 0.0, -s1*coef1*c1,-s1*coef1*s1, 0.0,s1*coef1*c1,s1*coef1*s1, 0.0},       // U2
	{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}      // W2
	};

	// We assume a threshold error
	test = (sqrt(pow(ctruss.GetStiffnessMatrixInGlobalCoord() - expected,2))<=1E-3 );

	// WARNING: some calclus error? Lack of precision, could be shown if area=2000
	//std::cout << expected << std::endl;
	//std::cout << ctruss.GetStiffnessMatrixInGlobalCoord() << std::endl;
	//std::cout << test << std::endl;

	CPPUNIT_ASSERT_EQUAL_MESSAGE("We expect to find a binary matrix with only 1 values",81,static_cast<int>(sum(sum(test,1))));

}

void SimpleCornerTrussTest::nodal_forces_tests(){
	// TODO: compute the actual values

	const unsigned int n_dof = 3, n_pt = 3;
	Point p0 = Point(0.0,0.0,0.0);
	Point p1 = Point(0.0,1.0,0.0);
	Point p2 = Point(1.0,2.5,0.0);
	Material m = TEST;
	float area = 200, // in mm^2
				fy2 = -1000; // in N, directed as gravity
	
	// build the global force vector, in format (fx0,fy0,fz0,...,fxN,fyN,fzN)
	ForceVectorType f = ForceVectorType(n_dof*n_pt,arma::fill::zeros);
	f(7) = fy2;
	
	// boundary conditions
	BoundaryConditionsVectorType bc = BoundaryConditionsVectorType();
	bc.push_back({0,0}); // at joint 0, Rx=0
	bc.push_back({0,1}); // at joint 0, Ry=0

	// Truss solver
	TrussSolver solver = TrussSolver();

	// empty displacement matrix
	DisplacementVectorType disp = DisplacementVectorType();

	// main object
	SimpleCornerTruss ctruss = SimpleCornerTruss( &p0, &p1, &p2, area, m);
	
	// 1 - compute the displacements
	solver.ComputeDisplacements( &disp,
			ctruss.GetStiffnessMatrixInGlobalCoordPointer(),
			&f,
			&bc);
	//std::cout << disp << std::endl;
	// support: no displacement
	CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("We expect to find no displacement dx0",0,disp(0),1E-3); // dx1
	CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("We expect to find no displacement dy0",0,disp(2),1E-3); // dx1
	CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("We expect to find no displacement dz0",0,disp(0),1E-3); // dx1

	// 2- find the support reactions in global coord
	solver.ComputeSupportReaction(&disp,
			ctruss.GetStiffnessMatrixInGlobalCoordPointer(),
			&f,
			&bc);
	//std::cout << f << std::endl;

	// 3 - find the diplacements in local coordinates
	ctruss.SetDisplacementInGlobalCoordinates( disp );
	
	// 4 - find the internal forces
}
