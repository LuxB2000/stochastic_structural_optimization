//
// Created by plumat on 4/6/16.
//

#include "InternalTrussObjectTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(InternalTrussObjectTest);

InternalTrussObjectTest::InternalTrussObjectTest(){
}

InternalTrussObjectTest::~InternalTrussObjectTest(){
}

void InternalTrussObjectTest::setUp(){
    // here set up EACH unit test
    a = PointManager::GetInstance().GetPoint(0.0,0.0,0.0);
    b = PointManager::GetInstance().GetPoint(1.0,0.0,0.0);
    truss = new InternalTrussObject(a,b,1.0,BASIC);
}

void InternalTrussObjectTest::tearDown(){
    // here clean after EACH unit test
    if(truss) delete truss;
}

void InternalTrussObjectTest::basic_tests(){

    // check the existence of the matrix and sizes
    StiffnessMatrixType kl = truss->GetLocalStiffnessMatrix();
    CPPUNIT_ASSERT_MESSAGE("The stiffness matrix should be initialized",truss->GetLocalStiffnessMatrixPointer()); // check if pointer is not null
    CPPUNIT_ASSERT_EQUAL_MESSAGE("The stiffness should a 6x6 matrix",36,static_cast<int>(kl.n_elem)); // should be a 3x3 matrix

    TransformationMatrixType cl = truss->GetLocalStiffnessMatrix();
    CPPUNIT_ASSERT_MESSAGE("The transformation matrix should be initialized",truss->GetLocalTransformationMatrixPointer()); // check if pointer is not null
    CPPUNIT_ASSERT_EQUAL_MESSAGE("The transformation matrix should a 6x6 matrix",36,static_cast<int>(cl.n_elem)); // should be a 3x3 matrix

}

void InternalTrussObjectTest::getters_tests(){

    // get the basic elements from constructor
    CPPUNIT_ASSERT_EQUAL_MESSAGE("The default length must be 1.0",1.0,truss->GetLength());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("The default cross section must be 1.0",1.0,truss->GetCrossSection());
    CPPUNIT_ASSERT_EQUAL_MESSAGE("The default Young Modulus must be 1.0",1.0,truss->GetYoungModulus());
}

void InternalTrussObjectTest::length_tests() {
    // test different lengths
    Point* a = PointManager::GetInstance().GetPoint(0.0,0.0,0.0);
    Point* b =  PointManager::GetInstance().GetPoint(1.0,1.0,0.0);
    InternalTrussObject t = InternalTrussObject(a, b, 1.0,BASIC);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("The default length must be sqrt(2)",sqrt(2),t.GetLength());
    Point* a2 =  PointManager::GetInstance().GetPoint(0.0,0.0,0.0);
    Point* b2 =  PointManager::GetInstance().GetPoint(1.0,1.0,1.0);
    InternalTrussObject t2 = InternalTrussObject(a2, b2, 1.0,BASIC);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("The default length must be sqrt(3)",sqrt(3),t2.GetLength());
}


void InternalTrussObjectTest::stiffness_tests() {
    // default values
    double coef = truss->GetCrossSection()*truss->GetYoungModulus()/truss->GetLength(), c=0.0;
    std::ostringstream st_c, st_i, st_j;
    StiffnessMatrixType kl = truss->GetLocalStiffnessMatrix();

    for(unsigned int i=0; i<kl.n_rows; i++) {
        for (unsigned int j = 0; j < kl.n_cols; j++) {
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
                                                kl(i, j),
                                                 1E-3 // delta

            );//
            st_c.str(""); st_i.str("");st_j.str("");
        }
    }

    // test an other configuration
}

void InternalTrussObjectTest::transformation_tests() {

    TransformationMatrixType cl = truss->GetLocalTransformationMatrix();
    TransformationMatrixType expected = {
            {1.0, 0.0, 0.0, 0.0, 0.0, 0.0},
            {0.0, 1.0, 0.0, 0.0, 0.0, 0.0},
            {0.0, 0.0, 1.0, 0.0, 0.0, 0.0},
            {0.0, 0.0, 0.0, 1.0, 0.0, 0.0},
            {0.0, 0.0, 0.0, 0.0, 1.0, 0.0},
            {0.0, 0.0, 0.0, 0.0, 0.0, 1.0} };

    //std::cout << cl << std::endl;
    arma::umat test = (expected == cl); // all elements should be equal to 1


    CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("We expect the binary matrix to have the element 1 at each position",
                                         36.0, // we expect all element equal to 1, sum of all raw and columns == dim1*dim2
                                         sum(sum(test,1)),
                                         0 // delta
    );//

    Point* b1 =  PointManager::GetInstance().GetPoint(0.0,1.0,0.0);
    InternalTrussObject truss1 = InternalTrussObject(a,b1,1.0,BASIC);
    TransformationMatrixType cl1 = truss1.GetLocalTransformationMatrix();
    expected = {
            {0.0, -1.0, 0.0, 0.0,  0.0, 0.0},
            {1.0,  0.0, 0.0, 0.0,  0.0, 0.0},
            {0.0,  0.0, 1.0, 0.0,  0.0, 0.0},
            {0.0,  0.0, 0.0, 0.0, -1.0, 0.0},
            {0.0,  0.0, 0.0, 1.0,  0.0, 0.0},
            {0.0,  0.0, 0.0, 0.0,  0.0, 1.0}
    };
    //std::cout << cl1 << std::endl;
    test = (expected == cl1); // all elements should be equal to 1
    CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("We expect the binary matrix to have the element 1 at each position",
                                         36.0, // we expect all element equal to 1, sum of all raw and columns == dim1*dim2
                                         sum(sum(test,1)),
                                         0 // delta
    );

    float px = 4.0, py = 6.0, pz = 0.0;
    Point* b2 =  PointManager::GetInstance().GetPoint(px,py,pz);
    InternalTrussObject truss2 = InternalTrussObject(a,b2,1.0,BASIC);
    TransformationMatrixType cl2 = truss2.GetLocalTransformationMatrix();
    expected = {
            {cos(atan(py/px)),-sin(atan(py/px)) , 0.0, 0.0,  0.0, 0.0},
            {sin(atan(py/px)), cos(atan(py/px)), 0.0, 0.0,  0.0, 0.0},
            {0.0,  0.0, 1.0, 0.0,  0.0, 0.0},
            {0.0,  0.0, 0.0, cos(atan(py/px)),-sin(atan(py/px)), 0.0},
            {0.0,  0.0, 0.0, sin(atan(py/px)), cos(atan(py/px)), 0.0},
            {0.0,  0.0, 0.0, 0.0,  0.0, 1.0}
    };
    //std::cout << cl2 << std::endl;
    test = (expected == cl2); // all elements should be equal to 1
    CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("We expect the binary matrix to have the element 1 at each position",
                                         36.0, // we expect all element equal to 1, sum of all raw and columns == dim1*dim2
                                         sum(sum(test,1)),
                                         0 // delta
    );

    // a point position shouldn't have any influence on the result
    Point* a3= PointManager::GetInstance().GetPoint(1,1,1);
    Point* b3= PointManager::GetInstance().GetPoint(px+a3->x, py+a3->y, pz+a3->z);
    InternalTrussObject truss3 = InternalTrussObject(a3,b3,1.0,BASIC);
    TransformationMatrixType cl3 = truss3.GetLocalTransformationMatrix();
    test = (expected == cl2); // all elements should be equal to 1, a point shouldn't have an influce, we expect the same matrix as previously
    CPPUNIT_ASSERT_DOUBLES_EQUAL_MESSAGE("We expect the binary matrix to have the element 1 at each position",
                                         36.0, // we expect all element equal to 1, sum of all raw and columns == dim1*dim2
                                         sum(sum(test,1)),
                                         0 // delta
    );

}
