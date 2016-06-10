/*
 * =====================================================================================
 *
 *       Filename:  SimpleCornerTrussTest.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/06/16 11:39:06
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jerome Plumat (JP)
 *
 * =====================================================================================
 */

#ifndef SSO_SIMPLECORNERTEST_H
#define SSO_SIMPLECORNERTEST_H

#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "SimpleCornerTruss.h"
#include "TrussSolver.h"

using namespace CppUnit;
using namespace std;

class SimpleCornerTrussTest : public CPPUNIT_NS::TestFixture{
    CPPUNIT_TEST_SUITE(SimpleCornerTrussTest);

        CPPUNIT_TEST(basic_tests);
        CPPUNIT_TEST(getters_tests);
        CPPUNIT_TEST(length_tests);
        CPPUNIT_TEST(stiffness_tests);
        CPPUNIT_TEST(nodal_forces_tests);

    CPPUNIT_TEST_SUITE_END();

public:
    SimpleCornerTrussTest();
    virtual ~SimpleCornerTrussTest();
    void setUp();
    void tearDown();

    void basic_tests(void);
    void getters_tests(void);
    void length_tests(void);

    void stiffness_tests(void);
    void nodal_forces_tests(void);

private:
};

#endif //SSO_SIMPLECORNERTEST_H

