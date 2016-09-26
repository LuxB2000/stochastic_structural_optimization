/*
 * =====================================================================================
 *
 *       Filename:  StiffnessBuilderTest.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  20/09/16 10:35:30
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jerome Plumat (JP), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef SSO_StiffnessBuilderTest_H
#define SSO_StiffnessBuilderTest_H

#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "StiffnessBuilder.h"
#include "InternalStructuralElementObject.h"
#include "Types.h"

using namespace CppUnit;
using namespace std;

class StiffnessBuilderTest  : public CPPUNIT_NS::TestFixture{

    CPPUNIT_TEST_SUITE(StiffnessBuilderTest);
        CPPUNIT_TEST(basic_tests);
        CPPUNIT_TEST(getter_tests);
        CPPUNIT_TEST(truss_building_tests);
        CPPUNIT_TEST(beam_building_tests);
        CPPUNIT_TEST(simple_truss_structure_building_tests);
    CPPUNIT_TEST_SUITE_END();

public:
    StiffnessBuilderTest();
    virtual ~StiffnessBuilderTest();
    void setUp();
    void tearDown();

    void basic_tests(void);
    void getter_tests(void);
		// test the construction of the stiffness matrices in simple scenario
    void truss_building_tests(void);
    void beam_building_tests(void);
    void simple_truss_structure_building_tests(void);

private:
	typedef InternalStructuralElementObject<TrussType> InternalTrussElement;
	typedef InternalStructuralElementObject<BeamType>  InternalBeamElement;

	typedef StiffnessBuilder<TrussType> TrussStiffnessBuilder;
	typedef StiffnessBuilder<BeamType>  BeamStiffnessBuilder;
};


#endif //SSO_StiffnessBuilderTest_H

