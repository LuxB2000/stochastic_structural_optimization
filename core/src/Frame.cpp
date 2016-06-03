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
}

Frame::~Frame(){
}

/*
 * TrussFrame
 */
TrussFrame::TrussFrame(){
}

TrussFrame::~TrussFrame(){
}

/*
 * Simple5Truss
 */
Simple5TrussFrame::Simple5TrussFrame(){
	m_origin = new Point(0.0,0.0,0.0);
	m_truss_params = new FrameParametersVectorType(3,0);
}

Simple5TrussFrame::Simple5TrussFrame(Point origin, 
		FrameParametersVectorType params) : Simple5TrussFrame() {
}

Simple5TrussFrame::~Simple5TrussFrame(){
	if( m_origin ) delete m_origin;
	if( m_truss_params ) delete m_truss_params;
}
