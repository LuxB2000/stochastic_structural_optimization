#include "TrussStructureBuilderTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TrussStructureBuilderTest);

TrussStructureBuilderTest::TrussStructureBuilderTest(){
}

TrussStructureBuilderTest::~TrussStructureBuilderTest(){
}

void TrussStructureBuilderTest::setUp(){
}

void TrussStructureBuilderTest::tearDown(){
}

void TrussStructureBuilderTest::basic_tests(){
	TrussStructureBuilder trussBuilder = TrussStructureBuilder();
	CPPUNIT_ASSERT_MESSAGE("KO",1==1);
}

void TrussStructureBuilderTest::getter_tests(){
	TrussStructureBuilder trussStructureBuilder = TrussStructureBuilder();
	CPPUNIT_ASSERT_MESSAGE("We expect the structure",
			trussStructureBuilder.GetStructure()!=NULL);
}
