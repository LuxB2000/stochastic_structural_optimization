//
// Created by plumat on 20/04/16.
//

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
    CPPUNIT_TEST_SUITE_END();

public:
    StiffnessMatrixBuilderTest();
    virtual ~StiffnessMatrixBuilderTest();
    void setUp();
    void tearDown();

    void basic_tests(void);
    void building_tests(void);
};


#endif //SSO_StiffnessMatrixBuilderTest_H
