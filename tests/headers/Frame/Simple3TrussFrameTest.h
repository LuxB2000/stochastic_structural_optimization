/*
 * =====================================================================================
 *
 *       Filename:  Simple3TrussFrame.h
 *
 *    Description:  Simple3TrussFrame unit tests
 *
 *        Version:  1.0
 *        Created:  20/07/16 16:09:16
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jerome Plumat (JP), j.plumat@auckland.ac.nz
 *        Company:  UoA, Auckand, NZ
 *
 * =====================================================================================
 */
#ifndef sso_SIMPLE3TRUSSFRAMETEST_H
#define sso_SIMPLE3TRUSSFRAMETEST_H

#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "Simple3TrussFrame.h"
#include "TrussSolver.h"

class Simple3TrussFrameTest :
	public CPPUNIT_NS::TestFixture{

    CPPUNIT_TEST_SUITE(Simple3TrussFrameTest);

			CPPUNIT_TEST(basic_tests);
			CPPUNIT_TEST(build_tests);

    CPPUNIT_TEST_SUITE_END();

public:
		Simple3TrussFrameTest();
		virtual ~Simple3TrussFrameTest();
		void setUp();
		void tearDown();

		// tests
    void basic_tests(void);
		void build_tests(void);

private:
	Point* origin;
};

#endif


