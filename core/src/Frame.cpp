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
 */
Frame::Frame(){
	m_truss_params = NULL;
	m_origin = NULL;
}

Frame::~Frame(){
	if( m_truss_params ) delete m_truss_params;
}

/*
 * TrussFrame
 */
TrussFrame::TrussFrame(){
	m_trusses = NULL;
}

TrussFrame::~TrussFrame(){
	if( m_trusses ){
		unsigned int l = m_trusses->size();
		for(unsigned int i=0; i<l; i++){
			delete m_trusses->at(i);
		}
	}
}

/*
 * Simple5Truss
 */
Simple5TrussFrame::Simple5TrussFrame(){
	m_truss_params = new FrameParametersVectorType(m_numberOfInputsParams,0);
}

Simple5TrussFrame::Simple5TrussFrame(Point* origin, float l1, float l2, float a2, float l3, float a3 ){
	m_origin = origin;
	m_truss_params = new FrameParametersVectorType(m_numberOfInputsParams,0);
	m_truss_params->at(1) = l1;
	m_truss_params->at(2) = l2;
	m_truss_params->at(3) = a2;
	m_truss_params->at(4) = l3;
	m_truss_params->at(5) = a3;

	m_BuildFrame();
}

Simple5TrussFrame::Simple5TrussFrame(Point* origin, FrameParametersVectorType v){
	m_origin = PointManager::GetInstance().GetPoint(0.0,0.0,0.0);
	m_truss_params = new FrameParametersVectorType( v );
	m_BuildFrame();
}

Simple5TrussFrame::~Simple5TrussFrame(){
}

void Simple5TrussFrame::m_BuildFrame(){
}
