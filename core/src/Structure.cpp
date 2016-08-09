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
#include "TrussSolver.h"

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
	if( m_stiffnessMatrix ) delete m_stiffnessMatrix;
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
	m_displacements = DisplacementVectorType();
	m_externalForces = ForceVectorType();
	m_stiffnessMatrix = new StiffnessMatrixType();
	m_internalForcesGC = ForceVectorType();
}

void Structure::GetMaximalNodalDisplacement(Point* loc, double* maxDisp ){
	*maxDisp = max(m_displacements);
	loc = PointManager::GetInstance().GetPoint(0,0,0);
}

void Structure::GetMaximalElementlForce(Point* loc, double* maxElF ){
	unsigned int i=0, l=0, j=0, k=0;
	l = m_frames->size();
	double m = 0, mm = 0;
	TrussFrame::ForceVectorVectorType frame_f = TrussFrame::ForceVectorVectorType();
	for( i=0; i<l; i++ ){
		for( j=0; j<m_frames->at(i)->GetElementForcesInLocalCoordinates()->size(); j++){
			for (k=0; k<m_frames->at(i)->GetElementForcesInLocalCoordinates()->at(j)->size(); k++ ){
				mm = max(*m_frames->at(i)->GetElementForcesInLocalCoordinates()->at(j)->at(k) );
				if(mm>m){
					m = mm;
				}
			}
		}
	}
	*maxElF = m;
}

const DisplacementVectorType Structure::GetNodeDisplacementVector(){
	return DisplacementVectorType(m_displacements);
}


// WARNING: ONLY 1 FRAME COULD BE DEFINED FOR NOW
void Structure::Build(){
	const unsigned int n_dof = 3, n_pt = 5 * m_inputNbrOfFrames; // 

	// 1- Instantiates all the Frame the object
	int f=0;
	//TODO compute the frames' origins
	for(f=0; f<m_inputNbrOfFrames; f++){
		// TODO: discover the type of Truss based on the number of parameters?
		Simple3TrussFrame* f3 = new Simple3TrussFrame(m_origin,*m_frame_params,m_crossSection, m_material_type);
		m_frames->push_back(f3);
	}

	// 2 - Construct the global Stiffness matrix
	// TODO: take into consideration the connections
	//TODO use builder
	m_stiffnessMatrix = new StiffnessMatrixType( m_frames->at(0)->GetStiffnessMatrix() );

	// number of forces along directions for each point in the structure
	m_displacements = DisplacementVectorType(m_stiffnessMatrix->n_rows);


	// 3 - find the displacements
	TrussSolver solver = TrussSolver();
	solver.ComputeDisplacements( &m_displacements,m_stiffnessMatrix,&m_externalForces,m_bc);

	// 4 - find the element forces in global coordinate system
	solver.ComputeSupportReaction(&m_displacements,m_stiffnessMatrix,&m_internalForcesGC,m_bc);

	// 5 - find the element forces in the local coordinate system
	// TODO: parse all the frame and find the corresponding internalForces
	m_frames->at(0)->SetElementForcesInGlobalCoordinates(m_internalForcesGC);

	// 6 - find the maximal forces and store a Truss Pointer to designate it


}
