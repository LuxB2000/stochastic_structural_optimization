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
