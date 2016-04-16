//
// Created by plumat on 20/04/16.
//

#include "StiffnessMatrixBuilderTest.h"
#include "../../core/headers/StiffnessMatrixBuilder.h"

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
    StiffnessMatrixBuilder k_builder = StiffnessMatrixBuilder();
    CPPUNIT_ASSERT_MESSAGE("We expect the matrix initialized",k_builder.GetStiffnessMatrixPointer());

    StiffnessMatrixBuilder::StiffnessMatrixType kl = k_builder.GetStiffnessMatrix();
    CPPUNIT_ASSERT_EQUAL_MESSAGE("We expect a matrix with 6 columns",6,static_cast<int>(kl.n_cols));
    CPPUNIT_ASSERT_EQUAL_MESSAGE("We expect a matrix with 6 columns",6,static_cast<int>(kl.n_rows));
}

void StiffnessMatrixBuilderTest::building_tests(){

    StiffnessMatrixBuilder k_builder = StiffnessMatrixBuilder();

}
