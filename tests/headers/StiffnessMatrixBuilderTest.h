//
// Created by plumat on 20/04/16.
// need to test other Build()?

#ifndef SSO_StiffnessMatrixBuilderTest_H
#define SSO_StiffnessMatrixBuilderTest_H

#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>


using namespace CppUnit;
using namespace std;

class StiffnessMatrixBuilderTest  : public CPPUNIT_NS::TestFixture{

    CPPUNIT_TEST_SUITE(StiffnessMatrixBuilderTest);
        CPPUNIT_TEST(basic_tests);
        CPPUNIT_TEST(building_tests);
        CPPUNIT_TEST(matrix_building_tests);
    CPPUNIT_TEST_SUITE_END();

public:
    StiffnessMatrixBuilderTest();
    virtual ~StiffnessMatrixBuilderTest();
    void setUp();
    void tearDown();

    void basic_tests(void);
		// test the construction of the stiffness matrices in simple scenario
    void building_tests(void);
		// test the combinasion of two stiffness matrices with set of points
		// this method 
    void matrix_building_tests(void);
};


#endif //SSO_StiffnessMatrixBuilderTest_H
