/*
 * =====================================================================================
 *
 *       Filename:  BarElementTest.h
 *
 *    Description:  :
 *
 *        Version:  1.0
 *        Created:  21/09/16 14:47:19
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jerome Plumat (JP), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef SSO_ELEMENTBARTEST_H
#define SSO_ELEMENTBARTEST_H

#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "BarElement.h"

using namespace CppUnit;
using namespace std;

class BarElementTest : public CPPUNIT_NS::TestFixture{
    CPPUNIT_TEST_SUITE(BarElementTest);
        CPPUNIT_TEST(basic_tests);
        CPPUNIT_TEST(getter_tests);
        CPPUNIT_TEST(truss_stiffness_tests);
        CPPUNIT_TEST(beam_stiffness_tests);
    CPPUNIT_TEST_SUITE_END();

public:
		BarElementTest();
		~BarElementTest();
    void setUp();
    void tearDown();

    void basic_tests(void);
		void getter_tests(void);
		void truss_stiffness_tests(void);
		void beam_stiffness_tests(void);

private:
	typedef BarElement<TrussType> TrussBarElement;
	typedef BarElement<BeamType>  BeamBarElement;
};
#endif
