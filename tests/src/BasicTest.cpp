//
// Created by plumat on 4/5/16.
//

#include "BasicTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(BasicTest);

BasicTest::BasicTest(){
}

BasicTest::~BasicTest(){
}

void BasicTest::setUp(){
}

void BasicTest::tearDown(){
}

void BasicTest::basic_true_test(){
	CPPUNIT_ASSERT(true);
	CPPUNIT_ASSERT(1==1);
	CPPUNIT_ASSERT(1+1==2);
}
