/*
 * =====================================================================================
 *
 *       Filename:  MathToolsTest.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/06/16 18:89:30
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jerome Plumat (JP)
 *
 * =====================================================================================
 */

#ifndef SSO_MATHTOOOLSTEST_H
#define SSO_MATHTOOOLSTEST_H

#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "math_tools.h"

using namespace CppUnit;
using namespace std;

class MathToolsTest : public CPPUNIT_NS::TestFixture{
    CPPUNIT_TEST_SUITE(MathToolsTest);

        CPPUNIT_TEST(basic_tests);

    CPPUNIT_TEST_SUITE_END();

public:
    MathToolsTest();
    virtual ~MathToolsTest();
    void setUp();
    void tearDown();

    void basic_tests(void);

private:
		Point *a, *b;
};

#endif //SSO_SIMPLECORNERTEST_H


