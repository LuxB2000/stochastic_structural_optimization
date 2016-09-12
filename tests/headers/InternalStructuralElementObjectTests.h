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

	CPPUNIT_TEST(basic_test);

	 CPPUNIT_TEST_SUITE_END();

public:
	InternalStructuralElementObjectTest();
	~InternalStructuralElementObjectTest();

	void setUp();
	void tearDown();

	void types_test(void);
	void basic_test(void);
	void constructor_test(void);
private:
	typedef InternalStructuralElementObject<TrussType> InternalTrussElement;
	typedef InternalStructuralElementObject<BeamType>  InternalBeamElement;
};

#endif //SSO_BASICTEST_H

