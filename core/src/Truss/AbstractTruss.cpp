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
	
	// init all the data
	m_L = 0.0;
	m_A = 0.0;
	m_E = 0.0;
	// create NULL ptr
	m_abstractTrussVector = NULL;
	m_k = NULL;
	m_disp_local_coord = NULL;
	m_c = NULL;
	m_f = NULL;
}

AbstractTruss::~AbstractTruss(){
	if( m_abstractTrussVector ){
		for( unsigned int i=0; i<m_abstractTrussVector->size(); i++){
			if( m_abstractTrussVector->at(i) ){
				delete m_abstractTrussVector->at(i);
			}
		}
	}
	if( m_k ) delete m_k;
	if( m_disp_local_coord ) delete m_disp_local_coord;
	if( m_c ) delete m_c;
	if( m_f ) delete m_f;
}

void AbstractTruss::m_ComputeLength(){
	unsigned int i=0,l=0;
	//TODO manage the error: if m_abstractTrussVector is empty
	l = m_abstractTrussVector->size();
	for(i=0; i<l; i++ ){
		m_L += m_abstractTrussVector->at(i)->GetLength();
	}
}
