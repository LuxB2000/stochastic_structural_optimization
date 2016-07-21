/*
 * =====================================================================================
 *
 *       Filename:  StructureTest.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/06/16 11:10:35
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jerome Plumat (JP)
 *
 * =====================================================================================
 */

#ifndef sso_STRUCTURETEST_H
#define sso_STRUCTURETEST_H

#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "Structure.h"

class StructureTest :
	public CPPUNIT_NS::TestFixture{

    CPPUNIT_TEST_SUITE(StructureTest);

			CPPUNIT_TEST(basic_tests);
			CPPUNIT_TEST(origin_tests);
			CPPUNIT_TEST(build_tests);

    CPPUNIT_TEST_SUITE_END();

public:
		StructureTest();
		virtual ~StructureTest();
    void setUp();
    void tearDown();

		// tests
    void basic_tests(void);
		void origin_tests(void);
		void build_tests(void);
};


#endif
