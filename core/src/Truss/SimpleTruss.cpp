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

    m_start_p =starting_pt;
    m_end_p = ending_pt;
    m_material = type_material;
    m_A = cross_section;

		m_numberOfInternalTruss = 1;

		// made of only one TrussObject
		m_internalTrussVector = new InternalTrussVectorType();
		InternalTrussObject* t = new InternalTrussObject(
				m_start_p, 
				m_end_p, 
				cross_section, 
				m_material);
		m_internalTrussVector->push_back(t);

		m_E = t->GetYoungModulus();

		this->m_ComputeLength();


		// populate the matrices
		StiffnessMatrixBuilder stiffBuilder = StiffnessMatrixBuilder(
			2*3);// 3 points * nbr of dof
		stiffBuilder.Build( t->GetLocalStiffnessMatrixPointer(), t->GetLocalTransformationMatrixPointer(), 0, 1 );
		m_k = new StiffnessMatrixType( stiffBuilder.GetStiffnessMatrix() );
    m_c = new TransformationMatrixType( t->GetLocalTransformationMatrix());
		m_PopulateForceDisplacementvectors();
}

SimpleTruss::~SimpleTruss(){
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
