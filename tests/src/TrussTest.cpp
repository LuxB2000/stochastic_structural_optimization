//
// Created by plumat on 4/6/16.
//

#include "TrussTest.h"
#include "../../core/headers/Truss.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TrussTest);

TrussTest::TrussTest(){
}

TrussTest::~TrussTest(){
}

void TrussTest::setUp(){
}

void TrussTest::tearDown(){
}

void TrussTest::basic_test(){
    Point* a = new Point(0.0,0.0,0.0);
    Point* b = new Point(1.0,0.0,0.0);
    Truss* truss = new Truss(a,b);

    CPPUNIT_ASSERT_MESSAGE("The stiffness matrix should be initialized",truss->GetLocalStiffnessMatrix()); // check if pointer is not null
    CPPUNIT_ASSERT_EQUAL_MESSAGE("The stiffness should a 3x3 matrix",9,static_cast<int>(truss->GetLocalStiffnessMatrix()->size())); // should be a 3x3 matrix

    CPPUNIT_ASSERT_MESSAGE("The transformation matrix should be initialized",truss->GetLocalTransformationMatrix()); // check if pointer is not null
    CPPUNIT_ASSERT_EQUAL_MESSAGE("The transformation matrix should a 6x6 matrix",36,static_cast<int>(truss->GetLocalTransformationMatrix()->size())); // should be a 3x3 matrix

    if(truss) delete truss;
    if(a) delete a;
    if(b) delete b;
}

void TrussTest::stiffness_test() {
    Point* a = new Point(0.0,0.0,0.0);
    Point* b = new Point(1.0,0.0,0.0);
    Truss* truss = new Truss(a,b);
    // TODO: compare vector?
    CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("The local stiffness must be a fixed one",
                                        0, // TODO: here the expected value
                                         truss->GetLocalStiffnessMatrix()->at(0),
                                         0.3 // delta
                                        );//

    if(truss) delete truss;
    if(a) delete a;
    if(b) delete b;
}

void TrussTest::transformation_test() {
    Point* a = new Point(0.0,0.0,0.0);
    Point* b = new Point(1.0,0.0,0.0);
    Truss* truss = new Truss(a,b);

    CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("The local transformation must be a fixed one",
                                         0, // TODO: here the expected value
                                         truss->GetLocalTransformationMatrix()->at(0),
                                         0.3 // delta
    );//

    if(truss) delete truss;
    if(a) delete a;
    if(b) delete b;
}
