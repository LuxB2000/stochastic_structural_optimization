#include "SolverTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(SolverTest);

SolverTest::SolverTest(){
}

SolverTest::~SolverTest(){
}

void
SolverTest::setUp(){
}

void
SolverTest::tearDown(){
}

void
SolverTest::basic_tests(){
	TrussSolverType solver_t = TrussSolverType();
	BeamSolverType  solver_b = BeamSolverType();
}

void
SolverTest::truss_triangle_tests(void){
}

void
SolverTest::beam_triangle_tests(void){
}

void
SolverTest::truss_frame_tests(void){
}

void
SolverTest::beam_frame_tests(void){
}
