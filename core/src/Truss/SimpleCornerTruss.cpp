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

	// TODO: use a dedicated function
	m_L = t1->GetLength() + t2->GetLength();
	
	// populate the matrices
	// TODO: use a dedicated function
	// Using the stiffness matrix builder
	// transformation matrix is local to InternalTruss only and can't be global to the CornerTruss
	// TODO: remove access to transformation matrix
  m_k = new StiffnessMatrixType(9, 9, arma::fill::zeros );
  m_disp_local_coord = new DisplacementVectorType(9, arma::fill::zeros ); // 3 point, 3 directions of displacements
  m_f = new ForceVectorType( 9, arma::fill::zeros );

	StiffnessMatrixBuilder stiffBuilder = StiffnessMatrixBuilder(
			((m_numberOfInternalTruss-1)*2+1)*3 );// 3 points * nbr of dof

}

SimpleCornerTruss::~SimpleCornerTruss(){
	if( m_start_p ) delete m_start_p;
	if( m_end_p ) delete m_end_p;
	if( m_mid_p ) delete m_mid_p;
}

void SimpleCornerTruss::SetDisplacementInGlobalCoordinates(
		DisplacementVectorType disp){
	// TODO
}
