//
// Created by plumat on 4/8/16.
//

#ifndef SSO_POINTTEST_H
#define SSO_POINTTEST_H

#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "../../core/headers/Point.h"

using namespace CppUnit;
using namespace std;

class PointTest : public CPPUNIT_NS::TestFixture{
    CPPUNIT_TEST_SUITE(PointTest);

        CPPUNIT_TEST(basic_tests);

    CPPUNIT_TEST_SUITE_END();

public:
    PointTest();
    virtual ~PointTest();
    void setUp();
    void tearDown();

    void basic_tests(void);

private:
};

#endif //SSO_POINTTEST_H
