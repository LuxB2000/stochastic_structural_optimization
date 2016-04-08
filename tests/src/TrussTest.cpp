//
// Created by plumat on 4/6/16.
//

#include "TrussTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TrussTest);

TrussTest::TrussTest(){
}

TrussTest::~TrussTest(){
}

void TrussTest::setUp(){
    // here set up EACH unit test
}

void TrussTest::tearDown(){
    // here clean after EACH unit test
    if(truss) delete truss;
    if(a) delete a;
    if(b) delete b;
}

void TrussTest::basic_test(){
    a = new Point(0.0,0.0,0.0);
    b = new Point(1.0,0.0,0.0);
    truss = new Truss(a,b);

    CPPUNIT_ASSERT_MESSAGE("The stiffness matrix should be initialized",truss->GetLocalStiffnessMatrix()); // check if pointer is not null
    CPPUNIT_ASSERT_EQUAL_MESSAGE("The stiffness should a 3x3 matrix",9,static_cast<int>(truss->GetLocalStiffnessMatrix()->n_elem)); // should be a 3x3 matrix

    CPPUNIT_ASSERT_MESSAGE("The transformation matrix should be initialized",truss->GetLocalTransformationMatrix()); // check if pointer is not null
    CPPUNIT_ASSERT_EQUAL_MESSAGE("The transformation matrix should a 6x6 matrix",36,static_cast<int>(truss->GetLocalTransformationMatrix()->n_elem)); // should be a 3x3 matrix

}

void TrussTest::stiffness_test() {
    a = new Point(0.0,0.0,0.0);
    b = new Point(1.0,0.0,0.0);
    truss = new Truss(a,b);
    Truss::StiffnessMatrixType expected_stiffness = Truss::StiffnessMatrixType(3,3,arma::fill::zeros);

    // TODO: compare vector?
    CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("The local stiffness must be a fixed one",
                                        0, // TODO: here the expected value
                                        truss->GetLocalStiffnessMatrix()->at(0,0),
                                        0.3 // delta
                                        );//

}

void TrussTest::transformation_test() {
    a = new Point(0.0,0.0,0.0);
    b = new Point(1.0,0.0,0.0);
    truss = new Truss(a,b);

    Truss::TransformationMatrixType expected = Truss::TransformationMatrixType(6,6,arma::fill::zeros);

    CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("The local transformation must be a fixed one",
                                         0, // TODO: here the expected value
                                         truss->GetLocalTransformationMatrix()->at(0,0),
                                         0.3 // delta
    );//

}
