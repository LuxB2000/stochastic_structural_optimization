//
// Created by plumat on 20/04/16.
//

#include "StiffnessMatrixBuilderTest.h"
#include "../../core/headers/StiffnessMatrixBuilder.h"
#include "SimpleTruss.h"
#include "math_tools.h"

CPPUNIT_TEST_SUITE_REGISTRATION(StiffnessMatrixBuilderTest);

StiffnessMatrixBuilderTest::StiffnessMatrixBuilderTest() {

}

StiffnessMatrixBuilderTest::~StiffnessMatrixBuilderTest() {

}

void StiffnessMatrixBuilderTest::setUp() {

}

void StiffnessMatrixBuilderTest::tearDown() {

}

void StiffnessMatrixBuilderTest::basic_tests() {
    // construct a system with 3 point
    int N = 3;
    // each point has 3 degrees of freedom - since SimpleTruss only
    int dof = 3;
    StiffnessMatrixBuilder k_builder = StiffnessMatrixBuilder(N*dof);
    CPPUNIT_ASSERT_MESSAGE("We expect the matrix initialized",k_builder.GetStiffnessMatrixPointer());

    StiffnessMatrixType kl = k_builder.GetStiffnessMatrix();
    CPPUNIT_ASSERT_EQUAL_MESSAGE("We expect a matrix with 9 columns",9,static_cast<int>(kl.n_cols));
    CPPUNIT_ASSERT_EQUAL_MESSAGE("We expect a matrix with 9 columns",9,static_cast<int>(kl.n_rows));
}

void StiffnessMatrixBuilderTest::building_tests(){

    arma::umat test;
    StiffnessMatrixType kg ;

    // construct a system with 3 point
    int N = 3;
    // each point has 3 degrees of freedom - since SimpleTruss only
    int dof = 3;
    float A = 2300E-6; // in m^2
    StiffnessMatrixBuilder k_builder = StiffnessMatrixBuilder(N*dof);
    // first truss: from joint 0 and joint 1, coordintes in meters
    Point* a = PointManager::GetInstance().GetPoint(0.0,0.0,0.0);
    Point* b =  PointManager::GetInstance().GetPoint(4.0,0.0,0.0);
    InternalTrussObject truss = InternalTrussObject(a,b,A,TEST);
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


    k_builder.Build(truss.GetLocalStiffnessMatrixPointer(),truss.GetLocalTransformationMatrixPointer(),0,1);
    kg = k_builder.GetStiffnessMatrix();
    //std::cout <<  kg << std::endl;
    test = (expected == kg );
    CPPUNIT_ASSERT_EQUAL_MESSAGE("We expect to find a binary matrix with only 1 values",81,static_cast<int>(sum(sum(test,1))));

    // add an other truss between joint 1 and 2
    Point* b1 =  PointManager::GetInstance().GetPoint(4.0,6.0,0.0);
    InternalTrussObject truss1 = InternalTrussObject(b,b1,A,TEST);
    float coef1 = (float) ( truss1.GetCrossSection()*truss1.GetYoungModulus()/truss1.GetLength() );
		//std::cout << "TEST: " << truss1.GetLocalTransformationMatrix() << std::endl;
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

    k_builder.Build(truss1.GetLocalStiffnessMatrixPointer(),truss1.GetLocalTransformationMatrixPointer(),1,2);
    kg = k_builder.GetStiffnessMatrix();
    //std::cout <<  kg << std::endl;
    //std::cout <<  expected1 << std::endl;
    test = (expected1 == kg );
    CPPUNIT_ASSERT_EQUAL_MESSAGE("We expect to find a binary matrix with only 1 values",81,static_cast<int>(sum(sum(test,1))));

    // add an other truss between joint 0 and 2
    float c = (cos(atan(b1->y/b1->x))), s = ( sin(atan(b1->y/b1->x)) );
    InternalTrussObject truss2 = InternalTrussObject(a,b1,A,TEST);
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


    k_builder.Build(truss2.GetLocalStiffnessMatrixPointer(),truss2.GetLocalTransformationMatrixPointer(),0,2);
    kg = k_builder.GetStiffnessMatrix();
    //std::cout << kg  << std::endl;
    //std::cout <<  expected2 << std::endl;
    test = (expected2 == kg );

    CPPUNIT_ASSERT_EQUAL_MESSAGE("We expect to find a binary matrix with only 1 values",81,static_cast<int>(sum(sum(test,1))));

}

void StiffnessMatrixBuilderTest::matrix_building_tests(){
	/*
	 * Two structures having two stiffness matrices and some joints in commun
	 * Each structure could be seem as a Frame. And the final stiffness matrix
	 * corresponds to a Structure stiffness matrix.
	 *
	 * Structure 1
	 *     p2
	 *    /|
	 *   / |
	 * p0---p1
	 *
	 * Structure 2
	 *   p3
	 *   --- p2
	 *   |
	 *   |
	 *  p0
	 *  WARNING: We can NOT add an element between joints located at po and p2.
	 *  If we considered adding two stiffness matrices with an element in commun
	 *  then there is no way to know exactly which part of the stiffness matrix
	 *  (expressed in global coord) would be count two time during the addition.
	 *  So we won't add two stiffness matrices with elements in commun. However,
	 *  it is OK to add two structures with nodes in commun.
	 */

	// constants
	unsigned int nbrPt1=3, nbrPt2=3, nbrPtTot=4, nbrDOF=3;
	Material material_type = TEST;
	float cross_section = 2300E-6; // in m^2

	// define the system
	Point *p0 = PointManager::GetInstance().GetPoint(0.0,0.0,0.0),
				*p1 = PointManager::GetInstance().GetPoint(4.0,0.0,0.0),
				*p2 = PointManager::GetInstance().GetPoint(4.0,6.0,0.0),
				*p3 = PointManager::GetInstance().GetPoint(0.0,6.0,0.0);

	SimpleTruss t0 = SimpleTruss(p0,p1,cross_section,material_type);
	SimpleTruss t1 = SimpleTruss(p0,p2,cross_section,material_type);
	SimpleTruss t2 = SimpleTruss(p1,p2,cross_section,material_type);
	SimpleTruss t3 = SimpleTruss(p0,p3,cross_section,material_type);
	SimpleTruss t4 = SimpleTruss(p3,p2,cross_section,material_type);
	// define the joint ids vectors for each sub-structure
	// TODO define proper object JointIdSet ?
	StiffnessMatrixBuilder::JointIdVectorType joint_id1, joint_id2;
	joint_id1 = {0,1,2};
	joint_id2 = {0,2,3};

	// define the expected matrices
	arma::umat test;
	float ym = t0.GetYoungModulus();
  float coef0 = (float) ( cross_section*ym/t0.GetLength() ),
				coef1 = (float) ( cross_section*ym/t1.GetLength() ),
				coef2 = (float) ( cross_section*ym/t2.GetLength() ),
				coef3 = (float) ( cross_section*ym/t3.GetLength() ),
				coef4 = (float) ( cross_section*ym/t4.GetLength() ),
				angl1 = ComputeAnglePlaneXY(p0,p2),
				c1 = cos(angl1), s1 = sin(angl1),
				angl2 = ComputeAnglePlaneXY(p0,p2), //angl2 will be equal to angl1
				c2 = cos(angl2), s2 = sin(angl2);
  StiffnessMatrixType expected1, expected2, expectedTot;
	expected1 = {
		 //  U0   V0   W0   U1   V1   W1   U2   V2   W2
				{coef0+c1*c1*coef1,s1*c1*coef1,0.0, -coef0,0.0,0.0, -c1*coef1*c1,-s1*coef1*c1,0.0},      // U0
				{c1*s1*coef1,s1*s1*coef1,0.0, 0.0,0.0,0.0, -s1*coef1*c1,-s1*coef1*s1,0.0},      // V0
				{0.0,0.0,0.0, 0.0,0.0,0.0, 0.0,0.0,0.0},      // W0
				{-coef0,0.0,0.0, coef0,0.0,0.0, 0.0,0.0,0.0},      // U1
				{0.0,0.0,0.0, 0.0,coef2,0.0, 0.0,-coef2,0.0},      // V1
				{0.0,0.0,0.0, 0.0,0.0,0.0, 0.0,0.0,0.0},      // W1
				{-c1*coef1*c1,-s1*coef1*c1,0.0, 0.0,0.0,0.0, c1*coef1*c1,s1*coef1*c1,0.0},      // U2
				{-s1*coef1*c1,-s1*coef1*s1,0.0, 0.0,-coef2,0.0, s1*coef1*c1,s1*coef1*s1+coef2,0.0},      // V2
				{0.0,0.0,0.0, 0.0,0.0,0.0, 0.0,0.0,0.0}       // W2
    };
	expected2 = {
		 //  U0   V0   W0   U2   V2   W2   U3   V3   W3
				{0.0,0.0,0.0, 0.0,0.0,0.0, 0.0,0.0,0.0},      // U0
				{0.0,coef3,0.0, 0.0,0.0,0.0, 0.0,-coef3,0.0},      // V0
				{0.0,0.0,0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},      // W0
				{0.0,0.0,0.0, coef4,0.0,0.0, -coef4,0.0,0.0},      // U2
				{0.0,0.0,0.0, 0.0,0.0,0.0, 0.0,0.0,0.0},      // V2
				{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},      // W2
				{0.0,0.0,0.0, -coef4,0.0,0.0, coef4,0.0,0.0},      // U3
				{0.0,-coef3, 0.0, 0.0,0.0,0.0, 0.0,coef3,0.0},      // V3
				{0.0,0.0,0.0, 0.0,0.0,0.0, 0.0,0.0,0.0}       // W3
	};
	//expectedTot = StiffnessMatrixType();
	//expectedTot.set_size(nbrDOF*nbrPtTot,nbrDOF*nbrPtTot);
	//expectedTot.fill(arma::fill::zeros);
	// U0->{U1,U2} V0->V3
	// U1->U0 V1->V2
	// U2->{U0,U3} V2->{V0,V1}
	expectedTot = {
		//U0,V0,W0, U1,V1,W1, U2,V2,W2, U3,V3,W3
		{coef0+c1*c1*coef1,s1*c1*coef1,0.0, -coef0,0.0,0.0, -c1*coef1*c1,-s1*coef1*c1,0.0, 0.0,0.0,0.0},      // U0
		{c2*s2*coef1,s2*s2*coef1+coef3,0.0, 0.0,0.0,0.0,  -s2*coef1*c2,-s2*coef1*s2,0.0, 0.0,-coef3,0.0},      // V0
		{0.0,0.0,0.0, 0.0,0.0,0.0, 0.0,0.0,0.0, 0.0,0.0,0.0},       // W0
		{-coef0,0.0,0.0, coef0,0.0,0.0, 0.0,0.0,0.0, 0.0,0.0,0.0},      // U1
		{0.0,0.0,0.0, 0.0,coef2,0.0, 0.0,-coef2,0.0, 0.0,0.0,0.0},      // V1
		{0.0,0.0,0.0, 0.0,0.0,0.0, 0.0,0.0,0.0, 0.0,0.0,0.0},       // W1
		{-c2*coef1*c2,-s2*coef1*c2,0.0, 0.0,0.0,0.0, coef4+c2*coef1*c2,s2*coef1*c2,0.0, -coef4,0.0,0.0},      // U2
		{-s2*coef1*c2,-s2*coef1*s2,0.0, 0.0,-coef2,0.0, s2*coef1*c2,s2*coef1*s2+coef2,0.0, 0.0,0.0,0.0},      // V2
		{0.0,0.0,0.0, 0.0,0.0,0.0, 0.0,0.0,0.0, 0.0,0.0,0.0},      // W2
		{0.0,0.0,0.0, 0.0,0.0,0.0, -coef4,0.0,0.0, coef4,0.0,0.0},      // U3
		{0.0,-coef3, 0.0,0.0,0.0, 0.0, 0.0,0.0,0.0, 0.0,coef3,0.0},      // V3
		{0.0,0.0,0.0, 0.0,0.0,0.0, 0.0,0.0,0.0, 0.0,0.0,0.0}       // W3
	};

	// compute the stiffness matrices for isolated structures
	StiffnessMatrixBuilder k_builder1 = StiffnessMatrixBuilder(nbrDOF*nbrPt1);
	k_builder1.Build(t0.GetStiffnessMatrixInGlobalCoordPointer(),0,1);
	k_builder1.Build(t1.GetStiffnessMatrixInGlobalCoordPointer(),0,2);
	k_builder1.Build(t2.GetStiffnessMatrixInGlobalCoordPointer(),1,2);

	//std::cout << expected1 << std::endl;
	//std::cout << " =========================== " << std::endl;
	//std::cout << k_builder1.GetStiffnessMatrix() << std::endl;
	//std::cout << " =========================== " << std::endl;
	//std::cout << expected1-k_builder1.GetStiffnessMatrix() << std::endl;
	//std::cout << " =========================== " << std::endl;

	test = (abs(expected1-k_builder1.GetStiffnessMatrix())<1E1); //strange huge error, "huge" matrix elements are 1E7, epsilon 1E1
	//std::cout << test << std::endl;

  CPPUNIT_ASSERT_EQUAL_MESSAGE("We expect to find a binary matrix with only 1 values",81,static_cast<int>(sum(sum(test,1))));

	// test the new method in a dumy case
	StiffnessMatrixBuilder k_builder12 = StiffnessMatrixBuilder(nbrDOF*nbrPt1);
	k_builder12.Build(t0.GetStiffnessMatrixInGlobalCoordPointer(),{0,1});
	k_builder12.Build(t1.GetStiffnessMatrixInGlobalCoordPointer(),{0,2});
	k_builder12.Build(t2.GetStiffnessMatrixInGlobalCoordPointer(),{1,2});
	test = (abs(expected1-k_builder12.GetStiffnessMatrix())<1E1); //strange huge error, "huge" matrix elements are 1E7, epsilon 1E1
  CPPUNIT_ASSERT_EQUAL_MESSAGE("We expect to find a binary matrix with only 1 values",81,static_cast<int>(sum(sum(test,1))));

	StiffnessMatrixBuilder k_builder2 = StiffnessMatrixBuilder(nbrDOF*nbrPt2);
	//k_builder2.Build(t1.GetStiffnessMatrixInGlobalCoordPointer(),0,1);//WARNING ids here are local to structur 2 and must be 0,1,2 since we have 3 points in the structure 2.
	k_builder2.Build(t3.GetStiffnessMatrixInGlobalCoordPointer(),0,2);
	k_builder2.Build(t4.GetStiffnessMatrixInGlobalCoordPointer(),1,2);

	//std::cout << expected2 << std::endl;
	//std::cout << " =========================== " << std::endl;
	//std::cout << k_builder2.GetStiffnessMatrix() << std::endl;
	//std::cout << " =========================== " << std::endl;
	//std::cout << expected2-k_builder2.GetStiffnessMatrix() << std::endl;
	//std::cout << " =========================== " << std::endl;
	test = (abs(expected2-k_builder2.GetStiffnessMatrix())<10); //strange huge error, "huge" matrix elements are 1E7, epsilon 1E1
	//std::cout << test << std::endl;

  CPPUNIT_ASSERT_EQUAL_MESSAGE("We expect to find a binary matrix with only 1 values",81,static_cast<int>(sum(sum(test,1))));

	// Build the global Stiffness matrix, it will contain the two structures
	StiffnessMatrixBuilder k_builderTot = StiffnessMatrixBuilder(nbrPtTot*nbrDOF);
	k_builderTot.Build(k_builder1.GetStiffnessMatrixPointer(),joint_id1);//,
	k_builderTot.Build(k_builder2.GetStiffnessMatrixPointer(),joint_id2);//,
//			k_builder2.GetStiffnessMatrixPointer(),joint_id2);

	//std::cout << " =========================== " << std::endl;
	//std::cout << k_builderTot.GetStiffnessMatrix() << std::endl;
	//std::cout << " =========================== " << std::endl;
	//std::cout << expectedTot << std::endl;
	//std::cout << " =========================== " << std::endl;
	//std::cout << expectedTot-k_builderTot.GetStiffnessMatrix() << std::endl;
	//std::cout << " =========================== " << std::endl;

	test=(abs(expectedTot-k_builderTot.GetStiffnessMatrix())<10);
	//std::cout << test << std::endl;

  CPPUNIT_ASSERT_EQUAL_MESSAGE("We expect to find the total stiffness matrix",(int)pow(nbrPtTot*nbrDOF,2),static_cast<int>(sum(sum(test,1))));
}

