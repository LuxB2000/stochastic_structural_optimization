/*
 * =====================================================================================
 *
 *       Filename:  FrameTest.h
 *
 *    Description:  Unit tests for the Frame Class
 *
 *        Version:  1.0
 *        Created:  02/06/16 13:04:20
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jerome Plumat (JP)
 *
 * =====================================================================================
 */

#ifndef sso_FRAMETEST_H
#define sso_FRAMETEST_H

#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "Frame.h"

class FrameTest :
	public CPPUNIT_NS::TestFixture{

    CPPUNIT_TEST_SUITE(FrameTest);

			CPPUNIT_TEST(basic_tests);
			CPPUNIT_TEST(parameters_tests);
			CPPUNIT_TEST(build_Simple3TrussFrame_tests);

    CPPUNIT_TEST_SUITE_END();

public:
		FrameTest();
		virtual ~FrameTest();
		void setUp();
		void tearDown();

		// tests
    void basic_tests(void);
		void parameters_tests(void);
		void build_Simple5TrussFrame_tests(void);
		void build_Simple3TrussFrame_tests(void);

private:
	Point* origin;
};

#endif
