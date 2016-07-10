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

/*
 * TrussFrame
 * ==========
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
 * Simple3TrussFrame
 * =================
 */
Simple3TrussFrame::Simple3TrussFrame(){
	m_trusses = new TrussVector();
	m_truss_params = new FrameParametersVectorType(m_numberOfInputsParams,0);
	m_origin = PointManager::GetInstance().GetPoint(0.0,0.0,0.0);
	m_cross_section = 1000; // in mm^2
	m_material_type = BASIC;
	m_BuildFrame();
}

Simple3TrussFrame::~Simple3TrussFrame(){
}

Simple3TrussFrame::Simple3TrussFrame(Point* origin,
	const FrameParametersVectorType v, double cross_sec, Material mat){

	m_trusses = new TrussVector();

	m_origin = origin;
	m_truss_params = new FrameParametersVectorType( v.begin(), v.end() );
	m_cross_section = cross_sec;
	m_material_type = mat;
	m_BuildFrame();
}

void Simple3TrussFrame::m_BuildFrame(){
	// Create the set of Point
	Point* p0 = m_origin;
	Point* p1 = PointManager::GetInstance().GetPoint(
									m_origin->x,
									m_origin->y+m_truss_params->at(0),
									m_origin->z);
	Point* p2 = PointManager::GetInstance().GetPoint(
									p1->x + m_truss_params->at(1),
									p1->y + m_truss_params->at(2),
									p1->z );
	Point* p3 = PointManager::GetInstance().GetPoint(
									p2->x + m_truss_params->at(1),
									p2->y - m_truss_params->at(2),
									p2->z );
	Point* p4 = PointManager::GetInstance().GetPoint(
									p3->x,
									p3->y - m_truss_params->at(0),
									p3->z );

	std::cout << " ============================= " << std::endl;
	std::cout << "TEST p0:" << *p0 << " p1:" << *p1
		<< " p2:" << *p2 << " p3:" << *p3 << " p4: " << *p4<< std::endl;
	std::cout << " ============================= " << std::endl;

	// truss 1
	SimpleTruss* t0 = new SimpleTruss(p0,p1,m_cross_section,m_material_type);
	// top corner truss 2
	SimpleTruss* t1 = new SimpleTruss(p1,p2,m_cross_section,m_material_type);
	SimpleTruss* t2 = new SimpleTruss(p2,p3,m_cross_section,m_material_type);
	// truss 3
	SimpleTruss* t3 = new SimpleTruss(p3,p4,m_cross_section,m_material_type);

	m_trusses->push_back(t0);
	m_trusses->push_back(t1);
	m_trusses->push_back(t2);
	m_trusses->push_back(t3);
	
	// Create the global stiffness matrix
	//StiffnessMatrixBuilder k_builder = StiffnessMatrixBuilder(m_dof*m_nbrOfPoint);
	//k_builder.Build(t0->GetStiffnessMatrixInGlobalCoord(),t0->GetLocalTransformationMatrixPointer(),0,1);
}

/*
 * Simple5TrussFrame
 * =================
 */
Simple5TrussFrame::Simple5TrussFrame(){
	m_origin = PointManager::GetInstance().GetPoint(0.0,0.0,0.0);
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
	m_origin = origin;
	m_truss_params = new FrameParametersVectorType( v );
	m_BuildFrame();
}

Simple5TrussFrame::~Simple5TrussFrame(){
}

void Simple5TrussFrame::m_BuildFrame(){
}
