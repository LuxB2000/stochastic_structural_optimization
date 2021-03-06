//
// Created by plumat on 4/6/16.
//
// Here are the tests relative to the InternalTrussObject element

#ifndef SSO_TRUSSTEST_H
#define SSO_TRUSSTEST_H

#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "InternalTrussObject.h"
#include "Types.h"

using namespace CppUnit;
using namespace std;

class InternalTrussObjectTest : public CPPUNIT_NS::TestFixture{
    CPPUNIT_TEST_SUITE(InternalTrussObjectTest);

        CPPUNIT_TEST(basic_tests);
        CPPUNIT_TEST(getters_tests);
        CPPUNIT_TEST(length_tests);
        CPPUNIT_TEST(stiffness_tests);
        CPPUNIT_TEST(transformation_tests);

    CPPUNIT_TEST_SUITE_END();

public:
    InternalTrussObjectTest();
    virtual ~InternalTrussObjectTest();
    void setUp();
    void tearDown();

    void basic_tests(void);
    void getters_tests(void);
    void length_tests(void);

    void stiffness_tests(void);
    void transformation_tests(void);

private:
    Point *a, *b;
    InternalTrussObject *truss;
};

#endif //SSO_TRUSSTEST_H
