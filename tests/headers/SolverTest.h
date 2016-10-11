/*
 * =====================================================================================
 *
 *       Filename:  SolverTest.h
 *
 *    Description:  Test the Solver
 *
 *        Version:  1.0
 *        Created:  30/09/16 15:47:51
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jerome Plumat (JP), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef SSO_SOLVERTEST_H
#define SSO_SOLVERTEST_H

#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "BarElement.h"
#include "Solver.h"

using namespace CppUnit;
using namespace std;

class SolverTest : public CPPUNIT_NS::TestFixture{
    CPPUNIT_TEST_SUITE(SolverTest);
        CPPUNIT_TEST(basic_tests);

				CPPUNIT_TEST(horizontal_beam_test);

        CPPUNIT_TEST(truss_triangle_tests);
        CPPUNIT_TEST(beam_triangle_tests);
				CPPUNIT_TEST(truss_frame_tests);
				CPPUNIT_TEST(beam_frame_tests);
    CPPUNIT_TEST_SUITE_END();

public:
		SolverTest();
		~SolverTest();
    void setUp();
    void tearDown();

    void basic_tests(void);

		void horizontal_beam_test(void);

		void truss_triangle_tests(void);
		void beam_triangle_tests(void);

		void truss_frame_tests(void);
		void beam_frame_tests(void);

private:

	typedef BarElement<TrussType> TrussBarElement;
	typedef BarElement<BeamType>  BeamBarElement;

	typedef StiffnessBuilder<TrussType> TrussStiffnessBuilder;
	typedef StiffnessBuilder<BeamType>  BeamStiffnessBuilder;

	typedef Solver<TrussType> TrussSolverType;
	typedef Solver<BeamType>   BeamSolverType;

	// path designating the folder containing the data to test
	string m_data_path;
};

#endif

