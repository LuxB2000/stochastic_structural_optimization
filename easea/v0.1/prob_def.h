/*
 * =====================================================================================
 *
 *       Filename:  prob_def.cpp
 *
 *    Description:  Here is a simple definition of the stochastic structure optimization
 *
 *        Version:  1.0
 *        Created:  11/08/16 11:44:30
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jerome Plumat (JP), 
 *        Company:  
 *
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
	//
	// The structure is composed of 3 Truss: 2 SimpleTruss and 1 TopCornerTruss
	// Two fixed support in p0 and p4.
	// F={0,-24kN}
 * =====================================================================================
 */
// Initialize easylogging
#include "easylogging++.h"
INITIALIZE_EASYLOGGINGPP

#include "Structure.h"
void BuildStructure(float p1, float p2, float p3, float* max_f, float* width, float* height){
	// params
	//const unsigned int n_dof = 3, n_pt = 5; // 
	double cross_sec = 5310*1E-6; // in m^2
	Material mat_type = TEST;
	double fy2 = -24E3; // express in Newtow

	Point *p;

	// build a structure with only one frame
	int nbrOfFrames = 1;
	// parameters of the Simple3TrussFrame
	FrameParametersVectorType params = {p1, p2, p3};
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
	double m = 0.0;
	structure.GetMaximalElementForce(p,&m);
	*max_f = (float)m;

}

