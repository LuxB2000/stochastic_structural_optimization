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

	//std::cout << " ============================= " << std::endl;
	//std::cout << "TEST p0:" << *p0 << " p1:" << *p1
	//	<< " p2:" << *p2 << " p3:" << *p3 << " p4: " << *p4<< std::endl;
	//std::cout << " ============================= " << std::endl;

	// truss 1
	SimpleTruss* t0 = new SimpleTruss(p0,p1,m_cross_section,m_material_type);
	// top corner truss 2
	SimpleTruss* t1 = new SimpleTruss(p1,p2,m_cross_section,m_material_type);
	SimpleTruss* t2 = new SimpleTruss(p2,p3,m_cross_section,m_material_type);
	// truss 3
	SimpleTruss* t3 = new SimpleTruss(p3,p4,m_cross_section,m_material_type);

	//std::cout << t1->GetStiffnessMatrixInGlobalCoord() << std::endl;

	m_trusses->push_back(t0);
	m_trusses->push_back(t1);
	m_trusses->push_back(t2);
	m_trusses->push_back(t3);
	
	// Create the global stiffness matrix
	// the builder takes in input a stiffness matrix in GLOBAL coordinate and two points ids
	// the Frame object is responsible of the point id management to construct the global 
	// Frame Stiffness matrix in global coordinates.
	StiffnessMatrixBuilder k_builder = StiffnessMatrixBuilder(m_dof*m_nbrOfPoint);
	k_builder.Build(t0->GetStiffnessMatrixInGlobalCoordPointer(),0,1);
	k_builder.Build(t1->GetStiffnessMatrixInGlobalCoordPointer(),1,2);
	k_builder.Build(t2->GetStiffnessMatrixInGlobalCoordPointer(),2,3);
	k_builder.Build(t3->GetStiffnessMatrixInGlobalCoordPointer(),3,4);
	m_stiffness = k_builder.GetStiffnessMatrix();
}// end function Simple3TrussFrame::m_BuildFrame

/*
 * Simple5TrussFrame
 * =================
 */
Simple5TrussFrame::Simple5TrussFrame(){
	m_origin = PointManager::GetInstance().GetPoint(0.0,0.0,0.0);
	m_truss_params = new FrameParametersVectorType(m_numberOfInputsParams,0);
}

Simple5TrussFrame::Simple5TrussFrame(Point* origin, float lv1, float lv21, float lv22, float lh22, float lv3, float lh3, float section, Material m ){
	m_origin = origin;
	m_truss_params = new FrameParametersVectorType(m_numberOfInputsParams,0);
	m_truss_params->at(0) = lv1;
	m_truss_params->at(1) = lv21;
	m_truss_params->at(2) = lv22;
	m_truss_params->at(3) = lh22;
	m_truss_params->at(4) = lv3;
	m_truss_params->at(5) = lh3;
	m_truss_params->at(6) = section;


	m_material = m;

	m_trusses = new TrussesVectorType();
	m_BuildFrame();
}

Simple5TrussFrame::Simple5TrussFrame(Point* origin, FrameParametersVectorType v, Material m){
	// TODO: Check the size of the input vector and return error is not correct
	m_origin = origin;
	m_truss_params = new FrameParametersVectorType( v );

	m_material = m;

	m_trusses = new TrussesVectorType();
	m_BuildFrame();
}

Simple5TrussFrame::~Simple5TrussFrame(){
}

void Simple5TrussFrame::m_BuildFrame(){
	// create the coordinates for the points
	Point* t11 = m_origin;
	Point* t12 = PointManager::GetInstance().GetPoint(
			m_origin->x,m_origin->y+m_truss_params->at(0),m_origin->z);
	m_trusses->push_back( new SimpleTruss(t11,t12,m_truss_params->at(6), m_material) );

	Point *t21 = t12;
	Point *t22 = PointManager::GetInstance().GetPoint(
			t21->x, t21->y + m_truss_params->at(1), t21->z );
	Point *t23 = PointManager::GetInstance().GetPoint(
			t22->x+m_truss_params->at(3), t22->y + m_truss_params->at(2), t22->z );
	m_trusses->push_back( new SimpleCornerTruss(t21,t22,t21,m_truss_params->at(6), m_material) );

	Point *t31 = t23;
	Point *t32 = PointManager::GetInstance().GetPoint(
			t31->x+m_truss_params->at(5), t31->y+m_truss_params->at(4), t31->z );
	Point *t33 = PointManager::GetInstance().GetPoint(
			t31->x+m_truss_params->at(5)*2, t31->y, t31->z );
	m_trusses->push_back( new SimpleCornerTruss( t31, t32, t33, m_truss_params->at(6), m_material) );

	Point *t41 = t33;
	Point *t42 = PointManager::GetInstance().GetPoint(
			t41->x+m_truss_params->at(3), t41->y - m_truss_params->at(2), t22->z );
	Point *t43 = PointManager::GetInstance().GetPoint(
			t43->x, t43->y-m_truss_params->at(1), t43->z);
	// !! The corner still need to know the point from buttom to top, whatever the notation counter-clock wise
	m_trusses->push_back( new SimpleCornerTruss( t43, t42, t41, m_truss_params->at(6), m_material) );

	Point *t51 = t43;
	Point *t52 = PointManager::GetInstance().GetPoint(
			t51->x, t52->y-m_truss_params->at(1), t52->z );
	m_trusses->push_back( new SimpleTruss( t52, t51, m_truss_params->at(6), m_material) );

}
