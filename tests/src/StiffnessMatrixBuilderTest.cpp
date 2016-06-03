//
// Created by plumat on 20/04/16.
//

#include "StiffnessMatrixBuilderTest.h"
#include "../../core/headers/StiffnessMatrixBuilder.h"
#include "AbstractTruss.h"

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
    // each point has 3 degrees of freedom - since AbstractTruss only
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
    // each point has 3 degrees of freedom - since AbstractTruss only
    int dof = 3;
    float A = 2300; // in mm^2
    StiffnessMatrixBuilder k_builder = StiffnessMatrixBuilder(N*dof);
    // first truss: from joint 0 and joint 1
    Point a = Point(0.0,0.0,0.0);
    Point b = Point(4000.0,0.0,0.0);
    AbstractTruss truss = AbstractTruss(&a,&b,A,AbstractTruss::TEST);
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
    Point b1 = Point(4000.0,6000.0,0.0);
    AbstractTruss truss1 = AbstractTruss(&b,&b1,A,AbstractTruss::TEST);
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

    k_builder.Build(truss1.GetLocalStiffnessMatrixPointer(),truss1.GetLocalTransformationMatrixPointer(),1,2);
    kg = k_builder.GetStiffnessMatrix();
    //std::cout <<  kg << std::endl;
    //std::cout <<  expected1 << std::endl;
    test = (expected1 == kg );
    CPPUNIT_ASSERT_EQUAL_MESSAGE("We expect to find a binary matrix with only 1 values",81,static_cast<int>(sum(sum(test,1))));

    // add an other truss between joint 0 and 2
    float c = (cos(atan(b1.y/b1.x))), s = ( sin(atan(b1.y/b1.x)) );
    AbstractTruss truss2 = AbstractTruss(&a,&b1,A,AbstractTruss::TEST);
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

