//
// Created by plumat on 4/26/16.
//

#ifndef SSO_TRUSSSOLVERTEST_H
#define SSO_TRUSSSOLVERTEST_H

#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "TrussSolver.h"

using namespace CppUnit;
using namespace std;

class TrussSolverTest : public CPPUNIT_NS::TestFixture{
    CPPUNIT_TEST_SUITE(TrussSolverTest);

        CPPUNIT_TEST(basic_tests);
        CPPUNIT_TEST(compute_displacements_tests);

    CPPUNIT_TEST_SUITE_END();

public:
    TrussSolverTest();
    virtual ~TrussSolverTest();
    void setUp();
    void tearDown();

    void basic_tests(void);
    void compute_displacements_tests(void);

private:
};

#endif //SSO_POINTTEST_H
