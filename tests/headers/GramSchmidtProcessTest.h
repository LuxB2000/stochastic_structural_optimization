//
// Created by plumat on 4/13/16.
//

#ifndef SSO_GRAMSCHMIDTPROCESSTEST_H
#define SSO_GRAMSCHMIDTPROCESSTEST_H

#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "../../core/headers/GramSchmidtProcess.h"

using namespace CppUnit;
using namespace std;

class GramSchmidtProcessTest : public CPPUNIT_NS::TestFixture{
CPPUNIT_TEST_SUITE(GramSchmidtProcessTest);

        CPPUNIT_TEST(projection_tests);

    CPPUNIT_TEST_SUITE_END();

public:
    GramSchmidtProcessTest();
    virtual ~GramSchmidtProcessTest();
    void setUp();
    void tearDown();

    void projection_tests(void);

private:
    GramSchmidtProcess* m_gsp;
};

#endif //SSO_GRAMSCHMIDTPROCESSTEST_H
