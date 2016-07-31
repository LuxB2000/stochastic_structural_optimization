#include "Simple3TrussFrame.h"

/*
 * Simple3TrussFrame
 * =================
 */
Simple3TrussFrame::Simple3TrussFrame(){
	m_trusses = new TrussVector();
	m_truss_params = new FrameParametersVectorType(m_numberOfInputsParams,1.0);
	m_origin = PointManager::GetInstance().GetPoint(0.0,0.0,0.0);
	m_cross_section = 1E-3; // in m^2
	m_material_type = BASIC;
	m_BuildFrame();
}

Simple3TrussFrame::~Simple3TrussFrame(){
}

Simple3TrussFrame::Simple3TrussFrame(Point* origin,
	const FrameParametersVectorType v, double cross_sec, Material mat){

	if( v.size() != m_numberOfInputsParams ){
		throw WrongNumberOfParametersException( "[Simple3TrussFrame] Wrong number of inputs parameters." );
	}

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
	k_builder.Build(t0->GetStiffnessMatrixInGlobalCoordPointer(),{0,1});
	k_builder.Build(t1->GetStiffnessMatrixInGlobalCoordPointer(),{1,2});
	k_builder.Build(t2->GetStiffnessMatrixInGlobalCoordPointer(),{2,3});
	k_builder.Build(t3->GetStiffnessMatrixInGlobalCoordPointer(),{3,4});
	m_stiffness = k_builder.GetStiffnessMatrix();
}// end function Simple3TrussFrame::m_BuildFrame


