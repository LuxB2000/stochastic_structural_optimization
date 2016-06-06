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
 *         Author:  Jerome Plumat (JP), j.plumat@auckland.ac.nz
 *        Company:  UoA, Auckand, NZ
 *
 * =====================================================================================
 */

#ifndef SSO_SIMPLECORNERTEST_H
#define SSO_SIMPLECORNERTEST_H

#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "SimpleCornerTruss.h"

using namespace CppUnit;
using namespace std;

class SimpleCornerTrussTest : public CPPUNIT_NS::TestFixture{
    CPPUNIT_TEST_SUITE(SimpleCornerTrussTest);

        CPPUNIT_TEST(basic_tests);
        //CPPUNIT_TEST(getters_tests);
        //CPPUNIT_TEST(length_tests);
        //CPPUNIT_TEST(stiffness_tests);
        //CPPUNIT_TEST(transformation_tests);

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
    void transformation_tests(void);

private:
    Point *a, *b;
    SimpleCornerTruss *truss;
};

#endif //SSO_TRUSSTEST_H

