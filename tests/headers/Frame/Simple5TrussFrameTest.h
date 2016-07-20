/*
 * =====================================================================================
 *
 *       Filename:  Simple5TrussFrame.h
 *
 *    Description:  Simple5TrussFrame unit tests
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

#include "Simple5TrussFrame.h"
#include "TrussSolver.h"

class Simple5TrussFrameTest :
	public CPPUNIT_NS::TestFixture{

    CPPUNIT_TEST_SUITE(Simple5TrussFrameTest);

			CPPUNIT_TEST(basic_tests);
			CPPUNIT_TEST(build_tests);

    CPPUNIT_TEST_SUITE_END();

public:
		Simple5TrussFrameTest();
		virtual ~Simple5TrussFrameTest();
		void setUp();
		void tearDown();

		// tests
    void basic_tests(void);
		void build_tests(void);

private:
	Point* origin;
};

#endif


