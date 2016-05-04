
#ifndef sso_TRUSSSTRUCTUREBUILDER_H
#define sso_TRUSSSTRUCTUREBUILDER_H

#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "TrussStructureBuilder.h"

class TrussStructureBuilderTest :
	public CPPUNIT_NS::TestFixture{

    CPPUNIT_TEST_SUITE(TrussStructureBuilderTest);

			CPPUNIT_TEST(basic_tests);

    CPPUNIT_TEST_SUITE_END();
public:
		TrussStructureBuilderTest();
		virtual ~TrussStructureBuilderTest();
    void setUp();
    void tearDown();

		// tests
    void basic_tests(void);
};

#endif
