/*
 * =====================================================================================
 *
 *       Filename:  Structure.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/06/16 11:08:59
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jerome Plumat (JP)
 *
 * =====================================================================================
 */

#include "Structure.h"

Structure::Structure(){
	this->m_init();
	m_frame_params = new FrameParametersVectorType(m_defaultNbrOfParameters,1.0);
}

Structure::Structure(Point* origin){
	this->m_init();
	m_origin =origin;
}

Structure::~Structure(){
	if( m_frame_params ) delete m_frame_params;
	if( m_bc ) delete m_bc;
	if( m_frames ){
		int l=0;
		l = m_frames->size();
		for( unsigned int i=0; i<l; i++){
			if( m_frames->at(i) ) delete m_frames->at(i);
		}
	}
}

void Structure::SetFrameParameters(const FrameParametersVectorType v, double cross_sec, Material m){
	m_frame_params = new FrameParametersVectorType( v );
	m_crossSection = cross_sec;
	m_material_type = m;
}

void Structure::SetBoundaryConditions( const BoundaryConditionsVectorType bc){
	m_bc = new BoundaryConditionsVectorType(bc);
}

void Structure::m_init(){
	m_origin = PointManager::GetInstance().GetPoint(0.0,0.0,0.0);
	m_frame_params = new FrameParametersVectorType(m_defaultNbrOfParameters,1.0);
	m_frames = new TrussFrameVectorType();
	m_bc = new BoundaryConditionsVectorType();
	m_inputNbrOfFrames = 0;
}

void Structure::GetMaximalDisplacement(Point* loc, double* maxDisp ){
}

void Structure::GetMaximalElementlForce(Point* loc, double* maxElF ){
}

void Structure::Build(){
	int f=0;
	//TODO compute the frames' origins
	for(f=0; f<m_inputNbrOfFrames; f++){
		// TODO: discover the type of Truss based on the number of parameters?
		Simple3TrussFrame* f3 = new Simple3TrussFrame(m_origin,*m_frame_params,m_crossSection, m_material_type);
		m_frames->push_back(f3);
	}
}
