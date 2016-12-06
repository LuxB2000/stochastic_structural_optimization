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
 *        (2)
 *        /| --> F
 *     2 / |
 *      /  | 1
 *     /   |
 * (0) ----- (1)
 *    /\ 0 |
 *   ///  ///
 * =====================================================================================
 */
// Initialize easylogging
#include "easylogging++.h"
#include "TrussSolver.h"
INITIALIZE_EASYLOGGINGPP

#include "Structure.h"
void BuildStructure(float c1, float c2, double F, float* max_f, float* width, float* height){
	// params
	//const unsigned int n_dof = 3, n_pt = 5; // 
	double cross_sec = 5310*1E-6; // in m^2
	Material mat_type = TEST;
	double fx2 = F; // express in Newtow

	// boundary condition, WARNING: we assume to know the point IDs
	BoundaryConditionsVectorType bc = BoundaryConditionsVectorType();
    bc.push_back({0,0}); // at joint 0, Rx=0
    bc.push_back({0,1}); // at joint 0, Ry=0
    bc.push_back({0,2}); // at joint 0, Rz=0
    bc.push_back({1,1}); // at joint 1, Ry=0
    bc.push_back({1,2}); // at joint 1, Rz=0

	ForceVectorType inputForces = ForceVectorType(9); // 3 points and 3 dof
	inputForces(7) = fx2;

	// 1 - Create the structure
	// Nodes
	Point* p0 = PointManager::GetInstance().GetPoint(0.0,0.0,0.0),
				*p1 = PointManager::GetInstance().GetPoint(0.0 + c1,0.0,0.0),
				*p2 = PointManager::GetInstance().GetPoint(0.0 + c1,0.0 + c2,0.0);
	// Truss elements
	SimpleTruss t0 = SimpleTruss(p0,p1,cross_sec,mat_type);
	SimpleTruss t1 = SimpleTruss(p0,p2,cross_sec,mat_type);
	SimpleTruss t2 = SimpleTruss(p1,p2,cross_sec,mat_type);

	// 2 - Create the stiffness matrix
	const int nbrDOF = 3, nbrPt = 3;
	StiffnessMatrixBuilder k_builder = StiffnessMatrixBuilder(nbrDOF*nbrPt);
	k_builder.Build(t0.GetStiffnessMatrixInGlobalCoordPointer(),0,1);
	k_builder.Build(t1.GetStiffnessMatrixInGlobalCoordPointer(),0,2);
	k_builder.Build(t2.GetStiffnessMatrixInGlobalCoordPointer(),1,2);
	StiffnessMatrixType stiffness = k_builder.GetStiffnessMatrix();

	// compute the displacements
	DisplacementVectorType displacements = DisplacementVectorType(stiffness.n_rows);
	TrussSolver solver = TrussSolver();
	solver.ComputeDisplacements( &displacements,k_builder.GetStiffnessMatrixPointer(),
															&inputForces,&bc);

	// 3 - find the diplacements in local coordinates
	DisplacementVectorType disp_glob_coord0 = DisplacementVectorType(6,arma::fill::zeros);
	DisplacementVectorType disp_glob_coord1 = DisplacementVectorType( disp_glob_coord0 );
	DisplacementVectorType disp_glob_coord2 = DisplacementVectorType( disp_glob_coord0 );
	disp_glob_coord0(0) = displacements(0); // pt0
	disp_glob_coord0(1) = displacements(1);
	disp_glob_coord0(2) = displacements(2);
	disp_glob_coord0(3) = displacements(3); // pt1
	disp_glob_coord0(4) = displacements(4);
	disp_glob_coord0(5) = displacements(5);

	disp_glob_coord1(0) = displacements(3); // pt1
	disp_glob_coord1(1) = displacements(4);
	disp_glob_coord1(2) = displacements(5);
	disp_glob_coord1(3) = displacements(6); // pt2
	disp_glob_coord1(4) = displacements(7);
	disp_glob_coord1(5) = displacements(8);

	disp_glob_coord2(0) = displacements(0); // pt0
	disp_glob_coord2(1) = displacements(1);
	disp_glob_coord2(2) = displacements(2);
	disp_glob_coord2(3) = displacements(6); // pt2
	disp_glob_coord2(4) = displacements(7);
	disp_glob_coord2(5) = displacements(8);

	t0.SetNodalDisplacementInGlobalCoordinates(disp_glob_coord0);
	t1.SetNodalDisplacementInGlobalCoordinates(disp_glob_coord1);
	t2.SetNodalDisplacementInGlobalCoordinates(disp_glob_coord2);

//	DisplacementVectorType disp_local_coord = t0.GetNodeDisplacements();
//	DisplacementVectorType disp_local_coord1 = t1.GetNodeDisplacements();
//	DisplacementVectorType disp_local_coord2 = t2.GetNodeDisplacements();

	//4 - find the internal forces
	ElementForceVectorType* f0 = t0.GetElementForces();
	ElementForceVectorType* f1 = t1.GetElementForces();
	ElementForceVectorType* f2 = t2.GetElementForces();

	// find the maximal internal force
	double m = 0.0;
	unsigned int i=0;
	InternalForceVectorType abs_v;

	for( i=0; i<f0->size(); i++ ){
		abs_v = arma::abs( *f0->at(i) );
		if( m<abs_v.max()) m = (double)abs_v.max();
	}
	for( i=0; i<f1->size(); i++ ){
		abs_v = arma::abs( *f1->at(i) );
		if( m<abs_v.max()) m = (double)abs_v.max();
	}
	for( i=0; i<f2->size(); i++ ){
		abs_v = arma::abs( *f2->at(i) );
		if( m<abs_v.max()) m = (double)abs_v.max();
	}

	*max_f = (float)m;

}

