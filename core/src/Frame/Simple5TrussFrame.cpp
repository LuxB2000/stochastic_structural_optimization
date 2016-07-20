#include "Simple5TrussFrame.h"


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

