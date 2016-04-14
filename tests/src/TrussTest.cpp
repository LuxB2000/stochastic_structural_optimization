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
    a = new Point(0.0,0.0,0.0);
    b = new Point(1.0,0.0,0.0);
    truss = new Truss(a,b,1.0,Truss::BASIC);
}

void TrussTest::tearDown(){
    // here clean after EACH unit test
    if(truss) delete truss;
    if(a) delete a;
    if(b) delete b;
}

void TrussTest::basic_tests(){

    // check the existence of the matrix and sizes
    CPPUNIT_ASSERT_MESSAGE("The stiffness matrix should be initialized",truss->GetLocalStiffnessMatrix()); // check if pointer is not null
    CPPUNIT_ASSERT_EQUAL_MESSAGE("The stiffness should a 6x6 matrix",36,static_cast<int>(truss->GetLocalStiffnessMatrix()->n_elem)); // should be a 3x3 matrix

    CPPUNIT_ASSERT_MESSAGE("The transformation matrix should be initialized",truss->GetLocalTransformationMatrix()); // check if pointer is not null
    CPPUNIT_ASSERT_EQUAL_MESSAGE("The transformation matrix should a 6x6 matrix",36,static_cast<int>(truss->GetLocalTransformationMatrix()->n_elem)); // should be a 3x3 matrix

}

void TrussTest::getters_tests(){

    // get the basic elements from constructor
    CPPUNIT_ASSERT_EQUAL_MESSAGE("The default length must be 1.0",1.0,truss->GetLength());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("The default cross section must be 1.0",1.0,truss->GetCrossSection());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("The default Young Modulus must be 1.0",1.0,truss->GetYoungModulus());
}

void TrussTest::length_tests() {
    // test different lengths
    Point a = Point(0.0,0.0,0.0);
    Point b = Point(1.0,1.0,0.0);
    Truss t = Truss(&a, &b, 1.0, Truss::BASIC);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("The default length must be sqrt(2)",sqrt(2),t.GetLength());
    Point a2 = Point(0.0,0.0,0.0);
    Point b2 = Point(1.0,1.0,1.0);
    Truss t2 = Truss(&a2, &b2, 1.0, Truss::BASIC);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("The default length must be sqrt(3)",sqrt(3),t2.GetLength());
}


void TrussTest::stiffness_tests() {
    // default values
    double coef = truss->GetCrossSection()*truss->GetYoungModulus()/truss->GetLength(), c=0.0;
    std::ostringstream st_c, st_i, st_j;
    Truss::StiffnessMatrixType* s = truss->GetLocalStiffnessMatrix();

    for(unsigned int i=0; i<s->n_rows; i++) {
        for (unsigned int j = 0; j < s->n_cols; j++) {
            if ((i == 0 & j == 0) | (i == 3 & (j==0 | j==3)) | (j == 3 & (i==0 | i==3))) {
                if ((i != j)) c = -coef;
                else c = coef;
            } else {
                c = 0;
            }
            st_c << c; st_i << i; st_j << j;
            std::string m = "The local stiffness must be " + st_c.str() + " at (" + st_i.str() + "," + st_j.str() + ")"  ;
            CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE(m,
                                                 c,
                                                 truss->GetLocalStiffnessMatrix()->at(i, j),
                                                 1E-3 // delta

            );//
            st_c.str(""); st_i.str("");st_j.str("");
        }
    }

    // test an other configuration
}

void TrussTest::transformation_tests() {

    Truss::TransformationMatrixType expected_basic = {
            {1.0, 0.0, 0.0, 0.0, 0.0, 0.0},
            {0.0, 1.0, 0.0, 0.0, 0.0, 0.0},
            {0.0, 0.0, 1.0, 0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0, 1.0, 0.0, 0.0},
            {0.0, 0.0, 0.0, 0.0, 1.0, 0.0},
            {0.0, 0.0, 0.0, 0.0, 0.0, 1.0} };

    arma::umat test = (expected_basic == *(truss->GetLocalTransformationMatrix()));

    CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("The local transformation must be a fixed one",
                                         0, // TODO: here the expected value
                                         test(0,0),
                                         0.3 // delta
    );//
}
