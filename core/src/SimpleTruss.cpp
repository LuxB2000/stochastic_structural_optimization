/*
 * =====================================================================================
 *
 *       Filename:  SimpleTruss.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/06/16 13:46:18
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jerome Plumat (JP)
 *
 * =====================================================================================
 */

#include "SimpleTruss.h"

SimpleTruss::SimpleTruss(
		Point* starting_pt,
		Point* ending_pt,
		double cross_section, 
		Material type_material)
{

    m_start_p = new Point(*starting_pt);
    m_end_p = new Point(*ending_pt);
    m_material = type_material;
    m_A = cross_section;

		m_numberOfInternalTruss = 1;

		// made of only one TrussObject
		m_abstractTrussVector = new InternalTrussVectorType();
		InternalTrussObject* t = new InternalTrussObject(
				m_start_p, 
				m_end_p, 
				cross_section, 
				m_material);
		m_abstractTrussVector->push_back(t);

		m_L = t->GetLength();
		m_E = t->GetYoungModulus();


		// populate the matrices
    m_c = new TransformationMatrixType( t->GetLocalTransformationMatrix());
    m_k = new StiffnessMatrixType( t->GetLocalStiffnessMatrix() );
    m_disp_local_coord = new DisplacementVectorType( t->GetDisplacementInLocalCoordinates() );
    m_f = new ForceVectorType( t->GetNodalForces() );
}

SimpleTruss::~SimpleTruss(){
	if( m_start_p ) delete m_start_p;
	if( m_end_p ) delete m_end_p;
}

double SimpleTruss::GetCrossSection(){
	return m_A;
}

double SimpleTruss::GetYoungModulus(){
	return m_E;
}

double SimpleTruss::GetLength(){
	return m_L;
}
 
void SimpleTruss::SetDisplacementInGlobalCoordinates(
		DisplacementVectorType disp){
	InternalTrussObject* t = m_abstractTrussVector->at(m_numberOfInternalTruss-1);
	t->SetDisplacementInGlobalCoordinates( disp );
	m_disp_local_coord = new DisplacementVectorType( t->GetDisplacementInLocalCoordinates() );
	m_f = new ForceVectorType( t->GetNodalForces() );
}
