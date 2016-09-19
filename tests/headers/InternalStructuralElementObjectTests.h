//
// Created by plumat on 5/9/16.
//

#ifndef SSO_INTERNALSTRUCTURALELEMENTOBJECTTEST_H
#define SSO_INTERNALSTRUCTURALELEMENTOBJECTTEST_H

#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "InternalStructuralElementObject.h"

using namespace CppUnit;
using namespace std;

class InternalStructuralElementObjectTest : public CPPUNIT_NS::TestFixture{
	CPPUNIT_TEST_SUITE(InternalStructuralElementObjectTest);

		CPPUNIT_TEST(types_test);
		CPPUNIT_TEST(basic_test);
		CPPUNIT_TEST(getter_test);
		CPPUNIT_TEST(length_test);

		CPPUNIT_TEST(truss_transformation_test);
		CPPUNIT_TEST(truss_stiffness_test);

		CPPUNIT_TEST(beam_transformation_test);
		CPPUNIT_TEST(beam_stiffness_test);

	 CPPUNIT_TEST_SUITE_END();

public:
	InternalStructuralElementObjectTest();
	~InternalStructuralElementObjectTest();

	void setUp();
	void tearDown();

	void types_test(void);
	void getter_test(void);
	void basic_test(void);
	void length_test(void);
	void truss_transformation_test(void);
	void truss_stiffness_test(void);
	void beam_transformation_test(void);
	void beam_stiffness_test(void);

private:
	typedef InternalStructuralElementObject<TrussType> InternalTrussElement;
	typedef InternalStructuralElementObject<BeamType>  InternalBeamElement;
};

#endif //SSO_BASICTEST_H

