
#ifndef SSO_POINTMANAGERTEST_H
#define SSO_POINTMANAGERTEST_H

#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "PointManager.h"

using namespace CppUnit;
using namespace std;

class PointManagerTest : public CPPUNIT_NS::TestFixture{
    CPPUNIT_TEST_SUITE(PointManagerTest);

        CPPUNIT_TEST(basic_tests);
				CPPUNIT_TEST(add_point_test);
				CPPUNIT_TEST(add_connextion_test);

    CPPUNIT_TEST_SUITE_END();

public:
    PointManagerTest();
    virtual ~PointManagerTest();
    void setUp();
    void tearDown();

    void basic_tests(void);
		void add_point_test(void);
		void add_connextion_test(void);


private:
};

#endif //SSO_POINTTEST_H
