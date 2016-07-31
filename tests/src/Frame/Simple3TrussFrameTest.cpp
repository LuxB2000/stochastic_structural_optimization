#include "Simple3TrussFrameTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(Simple3TrussFrameTest);

Simple3TrussFrameTest::Simple3TrussFrameTest(){
}

Simple3TrussFrameTest::~Simple3TrussFrameTest(){
}

void Simple3TrussFrameTest::setUp(){
	origin = PointManager::GetInstance().GetPoint(0.0,0.0,0.0);
}

void Simple3TrussFrameTest::tearDown(){
}

void Simple3TrussFrameTest::basic_tests(void){
	Simple3TrussFrame f3 = Simple3TrussFrame();
	CPPUNIT_ASSERT_MESSAGE("We expect the parameter vector beeing initiate",f3.GetParameters());
	CPPUNIT_ASSERT_EQUAL_MESSAGE("We expect 3 parameters",3,(int)f3.GetParameters()->size());
}

void Simple3TrussFrameTest::build_tests(void){
	//
	//     p2
	//     /\
	//  2 /  \ 3
	// p1/    \ p3
	// 1 |    | 4
	// p0|    | p4
	/// ///  ///
	//
	//
	// The structure is composed of 3 Truss: 2 SimpleTruss and 1 TopCornerTruss
	// Two fixed support in p0 and p4.

	// Parameters fit the example presented in "Introduction to Finite Element
	// Analysis Using Matlab and Abaqus", A. Khennane, page 110, 2013.
	// param = {dim_y_SimpleTruss, dim_x_TopCornerTruss, dim_y_TopCornerTruss}
	const unsigned int n_dof = 3, n_pt = 5;

	arma::umat test;

	FrameParametersVectorType params = {5.0, 6.0, 1.0};
	double cross_sec = 5310*1E-6; // in m^2
	Material mat_type = TEST;
	Simple3TrussFrame f3 = Simple3TrussFrame(origin,params,cross_sec,mat_type);
	//TODO use Matlab matrix_builder (valided by UT)
	StiffnessMatrixType expected = {
	{0.000000,0.000000,0.000000,-0.000000,-0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000},
	{0.000000,212400000.000000,0.000000,-0.000000,-212400000.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000},
	{0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000},
	{-0.000000,-0.000000,0.000000,169873029.261038,28312171.543506,0.000000,-169873029.261038,-28312171.543506,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000},
	{-0.000000,-212400000.000000,0.000000,28312171.543506,217118695.257251,0.000000,-28312171.543506,-4718695.257251,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000},
	{0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000},
	{0.000000,0.000000,0.000000,-169873029.261038,-28312171.543506,0.000000,339746058.522077,0.000000,0.000000,-169873029.261038,28312171.543506,0.000000,0.000000,0.000000,0.000000},
	{0.000000,0.000000,0.000000,-28312171.543506,-4718695.257251,0.000000,0.000000,9437390.514502,0.000000,28312171.543506,-4718695.257251,0.000000,0.000000,0.000000,0.000000},
	{0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000},
	{0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,-169873029.261038,28312171.543506,0.000000,169873029.261038,-28312171.543506,0.000000,-0.000000,0.000000,0.000000},
	{0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,28312171.543506,-4718695.257251,0.000000,-28312171.543506,217118695.257251,0.000000,0.000000,-212400000.000000,0.000000},
	{0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000},
	{0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,-0.000000,0.000000,0.000000,0.000000,-0.000000,0.000000},
	{0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,-212400000.000000,0.000000,-0.000000,212400000.000000,0.000000},
	{0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000}
	};
	StiffnessMatrixType k_frame = f3.GetStiffnessMatrix();
	CPPUNIT_ASSERT_EQUAL_MESSAGE("We expect 15 columns in the Simple3TrussStructure",15,(int)k_frame.n_cols);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("We expect 15 rows in the Simple3TrussStructure",15,(int)k_frame.n_rows);
	//std::cout << " *** ACTUAL ** " << std::endl;
	//std::cout << k_frame << std::endl;
	//std::cout << " *** EXPECTED ** " << std::endl;
	//std::cout << expected << std::endl;
	test = (abs(expected - k_frame)<33); //WARNING: 'Huge' error: 33*100/1E8 percent
	//std::cout << " *** DIFFERENCE ** " << std::endl;
	//std::cout << expected - k_frame << std::endl;
	//std::cout << " *** BINARY COMP. ** " << std::endl;
	//std::cout << test << std::endl;
	CPPUNIT_ASSERT_EQUAL_MESSAGE("We expect to find a binary matrix with only 1 values",15*15,static_cast<int>(sum(sum(test,1))));

}

void Simple3TrussFrameTest::exception_tests(){
	FrameParametersVectorType params_wrong_number_of_params = {1.0, 5.0, 6.0, 1.0};
	double cross_sec = 5310*1E-6; // in m^2
	Material mat_type = TEST;
	bool exc_catched = false;

	// catch an expection
	try{
		Simple3TrussFrame f3 = Simple3TrussFrame(origin,params_wrong_number_of_params,cross_sec,mat_type);
	}catch(WrongNumberOfParametersException &exc){
		exc_catched = true;
	}
	CPPUNIT_ASSERT_MESSAGE( "We assume to get an exception due to wrong number of input parameters", exc_catched );
}

