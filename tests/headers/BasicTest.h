//
// Created by plumat on 4/5/16.
//

#ifndef SSO_BASICTEST_H
#define SSO_BASICTEST_H

#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace CppUnit;
using namespace std;

class BasicTest : public CPPUNIT_NS::TestFixture{
	CPPUNIT_TEST_SUITE(BasicTest);

	CPPUNIT_TEST(basic_true_test);

	 CPPUNIT_TEST_SUITE_END();

public:
	BasicTest();
	virtual ~BasicTest();
	void setUp();
        void tearDown();

	void basic_true_test(void);
};

#endif //SSO_BASICTEST_H
