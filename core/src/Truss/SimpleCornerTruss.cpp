/*
 * =====================================================================================
 *
 *       Filename:  SimpleCornerTruss.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/06/16 11:20:10
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jerome Plumat (JP), j.plumat@auckland.ac.nz
 *        Company:  UoA, Auckand, NZ
 *
 * =====================================================================================
 */

#include "SimpleCornerTruss.h"

SimpleCornerTruss::SimpleCornerTruss(Point* starting_pt, Point* middle_pt, Point* ending_pt, double cross_section, Material type_material){

	m_start_p = new Point( *starting_pt );
	m_mid_p = new Point( *middle_pt );
	m_end_p = new Point( *ending_pt );
	m_A = cross_section;
	m_material = type_material;
	m_numberOfInternalTruss = 2;

	// compose of two internal truss object
	m_abstractTrussVector = new InternalTrussVectorType();
	InternalTrussObject* t1 = new InternalTrussObject( 
			m_start_p, 
			m_mid_p, 
			m_A,
			m_material);
	m_abstractTrussVector->push_back( t1 );
	InternalTrussObject* t2 = new InternalTrussObject(
			m_mid_p,
			m_end_p,
			m_A,
			m_material);
	m_abstractTrussVector->push_back( t2 );

	m_E = t1->GetYoungModulus();
	this->m_ComputeLength();
	
	// populate the matrices
	// TODO: use a dedicated function
	// Using the stiffness matrix builder
	// transformation matrix is local to InternalTruss only and can't be global to the CornerTruss
  m_k = new StiffnessMatrixType(9, 9, arma::fill::zeros );
  m_disp_local_coord = new DisplacementVectorType(9, arma::fill::zeros ); // 3 point, 3 directions of displacements
  m_f = new ForceVectorType( 9, arma::fill::zeros );

	StiffnessMatrixBuilder stiffBuilder = StiffnessMatrixBuilder(
			((m_numberOfInternalTruss-1)*2+1)*3 );// 3 points * nbr of dof
	stiffBuilder.Build( t1->GetLocalStiffnessMatrixPointer(), t1->GetLocalTransformationMatrixPointer(), 0, 1 );
	stiffBuilder.Build( t2->GetLocalStiffnessMatrixPointer(), t2->GetLocalTransformationMatrixPointer(), 1, 2);
	m_k = new StiffnessMatrixType( stiffBuilder.GetStiffnessMatrix() );

}

SimpleCornerTruss::~SimpleCornerTruss(){
	if( m_start_p ) delete m_start_p;
	if( m_end_p ) delete m_end_p;
	if( m_mid_p ) delete m_mid_p;
}

void SimpleCornerTruss::SetNodalDisplacementInGlobalCoordinates(
		DisplacementVectorType disp){
	// displacement at each truss
	DisplacementVectorType disp0 = DisplacementVectorType(6,arma::fill::zeros),
												 disp1 = DisplacementVectorType(6,arma::fill::zeros);

	unsigned int i = 0, l = 0;
	l = disp.n_elem;
	for(i=0; i<l-3; i++){
		disp0(i) = disp(i); // truss 1 is made of pt 0 and 1 -> elements 0 to 6
		disp1(i) = disp(i+3); // truss 2 is made of pt 1 and 2 -> elements 3 to 9
	}
	
	m_abstractTrussVector->at(0)->SetNodalDisplacementInGlobalCoordinates( disp0 );
	m_abstractTrussVector->at(1)->SetNodalDisplacementInGlobalCoordinates( disp1 );

	//std::cout << m_abstractTrussVector->at(0)->GetNodalDisplacementInLocalCoordinates() << std::endl;
	//std::cout << m_abstractTrussVector->at(1)->GetNodalDisplacementInLocalCoordinates() << std::endl;
	//std::cout << m_abstractTrussVector->at(0)->GetElementForces() << std::endl;
	//std::cout << m_abstractTrussVector->at(1)->GetElementForces() << std::endl;

	// the nodal forces are local -> fx at pt1 (pt commun to t0 and t1) may be
	// different depending the local coord system
	// The length of the nodal foce vector is equal to the number of 
	// InternalTruss * 2 * 3 (2 pts per Truss, 3 directions for each force)
	//
	
}
