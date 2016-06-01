/*
 * =====================================================================================
 *
 *       Filename:  AbstractTruss.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/06/16 13:40:07
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jerome Plumat (JP)
 *
 * =====================================================================================
 */

#include "AbstractTruss.h"

AbstractTruss::AbstractTruss(){
	
	// TRUSS HAVE 3 DEGREES OF FREEDOM BY DEFINITION: U, V, W: translation along the three axis
	m_numberOfDOF = 3;

	// init all the data
	m_L = 0.0;
	m_A = 0.0;
	m_E = 0.0;
	// create NULL ptr
	m_internalTrussVector = NULL;
	m_k = NULL;
	m_c = NULL;
	m_elementForces = NULL;
	m_nodeDisplacements = NULL;
}

AbstractTruss::~AbstractTruss(){
	if( m_internalTrussVector ){
		for( unsigned int i=0; i<m_internalTrussVector->size(); i++){
			if( m_internalTrussVector->at(i) ){
				delete m_internalTrussVector->at(i);
			}
		}
	}
	if( m_k ) delete m_k;
	if( m_c ) delete m_c;
	if( m_elementForces ) delete m_elementForces;
	if( m_nodeDisplacements ) delete m_nodeDisplacements;
}

void AbstractTruss::m_ComputeLength(){
	unsigned int i=0,l=0;
	l = m_internalTrussVector->size();
	for(i=0; i<l; i++ ){
		m_L += m_internalTrussVector->at(i)->GetLength();
	}
}

void AbstractTruss::SetNodalDisplacementInGlobalCoordinates( DisplacementVectorType disp_g ){
	unsigned int i=0,l=0,j=0;
	DisplacementVectorType disp_g_i = DisplacementVectorType(m_numberOfDOF*2,arma::fill::zeros); // *2 because two nodes per truss
	l = m_internalTrussVector->size();
	// for each internal truss
	for( i=0; i<l; i++){
		// set the displacement to each node
		// create vector of displacement for each truss: need diplacements of each points
		for( j=0; j<m_numberOfDOF*2; j++){
			disp_g_i(j) = disp_g((i)*m_numberOfDOF+j);
		}
		m_internalTrussVector->at(i)->SetNodalDisplacementInGlobalCoordinates( disp_g_i );
	}

	// populate the element and node vectors;
	m_PopulateForceDisplacementvectors();
}

void AbstractTruss::m_PopulateForceDisplacementvectors(){
	unsigned int i=0,l=0;
	l = m_internalTrussVector->size();
	// reinit the element force because it will contains pointers // useful?
	m_elementForces = new ElementForceVectorType();
	m_nodeDisplacements = new NodeDisplacementVectorType();

	for( i=0; i<l; i++){
		m_elementForces->push_back(m_internalTrussVector->at(i)->GetInternalForcesPointer());
		m_nodeDisplacements->push_back(m_internalTrussVector->at(i)->GetNodeDisplacementsPointer());
	}
}

