/*
 * =====================================================================================
 *
 *       Filename:  Frame.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/05/15 12:59:40
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jerome Plumat (JP)
 *
 * =====================================================================================
 */

#include "Frame.h"

/*
 * Frame
 * =====
 */
Frame::Frame(){
	m_truss_params = NULL;
	m_origin = NULL;
}

Frame::~Frame(){
	if( m_truss_params ) delete m_truss_params;
}

const StiffnessMatrixType Frame::GetStiffnessMatrix(){
    return StiffnessMatrixType(m_stiffness);
}

StiffnessMatrixType* Frame::GetStiffnessMatrixPointer(){
	return &m_stiffness;
}
