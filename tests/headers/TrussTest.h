//
// Created by plumat on 4/6/16.
//
// Here are the tests relative to the Truss element

#ifndef SSO_TRUSSTEST_H
#define SSO_TRUSSTEST_H

#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "../../core/headers/Truss.h"

using namespace CppUnit;
using namespace std;

class TrussTest : public CPPUNIT_NS::TestFixture{
    CPPUNIT_TEST_SUITE(TrussTest);

        CPPUNIT_TEST(basic_test);
        CPPUNIT_TEST(stiffness_test);
        CPPUNIT_TEST(transformation_test);

    CPPUNIT_TEST_SUITE_END();

public:
    TrussTest();
    virtual ~TrussTest();
    void setUp();
    void tearDown();

    void basic_test(void);
    void stiffness_test(void);
    void transformation_test(void);

private:
    Point *a, *b;
    Truss *truss;
};

#endif //SSO_TRUSSTEST_H
