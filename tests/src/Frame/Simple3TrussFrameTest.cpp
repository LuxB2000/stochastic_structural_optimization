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
	//      F
	//      |
	//      |
	//     \/
	//     p2
	//     /\
	//  2 /  \ 3
	// p1/    \ p3
	// 1 |    | 4
	// p0|    | p4
	/// ///  ///
	//
	// The structure is composed of 3 Truss: 2 SimpleTruss and 1 TopCornerTruss
	// Two fixed support in p0 and p4.
	// F={0,24kN}

	// Parameters fit the example presented in "Introduction to Finite Element
	// Analysis Using Matlab and Abaqus", A. Khennane, page 110, 2013.
	// param = {dim_y_SimpleTruss, dim_x_TopCornerTruss, dim_y_TopCornerTruss}
	const unsigned int n_dof = 3, n_pt = 5;
	double fy2 = -24E3; // express in Newtow

	FrameParametersVectorType params = {5.0, 6.0, 1.0};
	double cross_sec = 5310*1E-6; // in m^2
	Material mat_type = TEST;
	Simple3TrussFrame f3 = Simple3TrussFrame(origin,params,cross_sec,mat_type);
	//TODO
	StiffnessMatrixType expected = {
		{0,0,0, 0,0,0, 0,0,0, 0,0,0, 0,0,0 }, // U0=0 since encastre
		{0,0,0, 0,0,0, 0,0,0, 0,0,0, 0,0,0 }, // V0=0 since encastre
		{0,0,0, 0,0,0, 0,0,0, 0,0,0, 0,0,0 }  // W0=0 since encastre
	};
	StiffnessMatrixType k_frame = f3.GetStiffnessMatrix();
	CPPUNIT_ASSERT_EQUAL_MESSAGE("We expect 15 columns in the Simple3TrussStructure",15,(int)k_frame.n_cols);
	CPPUNIT_ASSERT_EQUAL_MESSAGE("We expect 15 rows in the Simple3TrussStructure",15,(int)k_frame.n_rows);
	//std::cout << k_frame.n_cols << "x" << k_frame.n_rows << std::endl;
	//std::cout << k_frame << std::endl;

	// compute internal forces
	ForceVectorType f = ForceVectorType(n_dof*n_pt,arma::fill::zeros);
	f(7) = fy2;
	
	// Boundary conditions
	BoundaryConditionsVectorType bc = BoundaryConditionsVectorType();
    bc.push_back({0,0}); // at joint 0, Rx=0
    bc.push_back({0,1}); // at joint 0, Ry=0
    bc.push_back({0,2}); // at joint 0, Rz=0
    bc.push_back({4,0}); // at joint 4, Rx=0
    bc.push_back({4,1}); // at joint 4, Ry=0
    bc.push_back({4,2}); // at joint 4, Rz=0

    //1 - find the displacements
    DisplacementVectorType disp = DisplacementVectorType(),
													 expected_disp = {}; //TODO
    TrussSolver solver = TrussSolver();
    solver.ComputeDisplacements( &disp,&k_frame,&f,&bc);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("We expect to have the same size",n_dof*n_pt,(unsigned int)disp.n_elem);
//		std::cout << disp << std::endl;

    //2- find the support reactions
    solver.ComputeSupportReaction(&disp,&k_frame,&f,&bc);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("We expect to have the same size",n_dof*n_pt,(unsigned int)f.n_elem);
//		std::cout << f << std::endl;
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

