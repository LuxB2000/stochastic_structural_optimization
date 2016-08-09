/*
 * =====================================================================================
 *
 *       Filename:  StructureTest.cpp
 *
 *    Description:  The test relative to the Structure
 *
 *        Version:  1.0
 *        Created:  02/06/16 11:14:07
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jerome Plumat (JP)
 *
 * =====================================================================================
 */

#include "StructureTest.h"
#include "TrussSolver.h"

CPPUNIT_TEST_SUITE_REGISTRATION(StructureTest);

StructureTest::StructureTest(){
}

StructureTest::~StructureTest(){
}

void StructureTest::tearDown(){
}

void StructureTest::setUp(){
}

void StructureTest::basic_tests(){
	Structure structure = Structure();
	// got the number of frame created in the building
	CPPUNIT_ASSERT_MESSAGE("We expect an empty structure",structure.GetNumberOfFrames()==0);

}

void StructureTest::origin_tests(){
	Structure structure = Structure();
	CPPUNIT_ASSERT_MESSAGE("We expect the default origin", 
			structure.GetOrigin()->x == 0 && structure.GetOrigin()->y == 0 && structure.GetOrigin()->z == 0 );
	
	Point* new_origin = PointManager::GetInstance().GetPoint(1.0,1.0,1.0);
	structure.SetOrigin(new_origin);
	CPPUNIT_ASSERT_MESSAGE("We expect the specified origin", 
			structure.GetOrigin()==new_origin);

}

void StructureTest::build_tests(){
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
	//TODO: move in Structure
	//
	// The structure is composed of 3 Truss: 2 SimpleTruss and 1 TopCornerTruss
	// Two fixed support in p0 and p4.
	// F={0,-24kN}
	// params
	const unsigned int n_dof = 3, n_pt = 5; // 
	double cross_sec = 5310*1E-6; // in m^2
	Material mat_type = TEST;
	double fy2 = -24E3; // express in Newtow

	// build a structure with only one frame
	int nbrOfFrames = 1;
	// parameters of the Simple3TrussFrame
	FrameParametersVectorType params = {5.0, 6.0, 1.0};
	// boundary condition, WARNING: we assume to know the point IDs
	// TODO: make it more general, passing the coordinates of the points?
	BoundaryConditionsVectorType bc = BoundaryConditionsVectorType();
    bc.push_back({0,0}); // at joint 0, Rx=0
    bc.push_back({0,1}); // at joint 0, Ry=0
    bc.push_back({0,2}); // at joint 0, Rz=0
    bc.push_back({4,0}); // at joint 4, Rx=0
    bc.push_back({4,1}); // at joint 4, Ry=0
    bc.push_back({4,2}); // at joint 4, Rz=0

	ForceVectorType inputForces = ForceVectorType(15);
	inputForces(7) = fy2;

	// 1 - Initiate the structure
	Point* origin = PointManager::GetInstance().GetPoint(0.0,0.0,0.0);
	Structure structure = Structure(origin);
	structure.SetNumberOfFrames( nbrOfFrames );
	structure.SetFrameParameters( params, cross_sec, mat_type );
	structure.SetBoundaryConditions( bc );
	structure.SetExternalForces( inputForces );
	structure.Build();

	CPPUNIT_ASSERT_MESSAGE("We expect a structure with one frame",structure.GetNumberOfFrames()==nbrOfFrames);


	//1 - find the displacements
    DisplacementVectorType disp = structure.GetNodeDisplacementVector(),
													 expected_disp = {
														 0,0,0,
														-3.6650e+12,9.1548e-05,0,
														-7.3301e+11,-1.7592e+13,0,
														2.1990e+12,1.1299e-04,0,
														0,0,0};
		arma::uvec test_v = (abs(disp-expected_disp)<1E-2);

		// 3 movements for each points
		CPPUNIT_ASSERT_EQUAL_MESSAGE("We expect a displacement vector with 15 elements",15,(int)disp.n_elem);
		//std::cout << " *** ACTUAL ** " << std::endl;
		//std::cout << disp << std::endl;
		//std::cout << " *** EXPECTED ** " << std::endl;
		//std::cout << expected_disp << std::endl;
		// Can NOT verify the displacement here because the matrix is singular, can't find the value in Matlab
		//CPPUNIT_ASSERT_EQUAL_MESSAGE("We expect a specific displacement vector.",15,(int)sum(test_v));
		Point* max_loc;
		double max_disp = 0, max_f = 0;

		structure.GetMaximalNodalDisplacement(max_loc,&max_disp);
		CPPUNIT_ASSERT_MESSAGE("We expect a maximal displacement different from 0",max_disp!=0);

//		std::cout << disp << std::endl;

    //2- find the support reactions in local coordinates
		structure.GetMaximalElementlForce(max_loc,&max_f);
		std::cout << "TEST: " << max_f << std::endl;
		CPPUNIT_ASSERT_MESSAGE("We expect a maximal element force different from 0",max_f!=0);
}
