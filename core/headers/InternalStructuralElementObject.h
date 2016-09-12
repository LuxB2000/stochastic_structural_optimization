
#ifndef sso_INTERNALSTRUCTURALELEMENTOBJECT_H
#define sso_INTERNALSTRUCTURALELEMENTOBJECT_H

#include <vector>
#include "Types.h"
#include "Point.h"
#include "Material.h"
#include "PointManager.h"

template<class StructuralElementType>
class InternalStructuralElementObject{
public:

	// constructor
	InternalStructuralElementObject(Point* starting_pt, Point* ending_pt, double cross_section, Material type_material){
		m_start = starting_pt;
		m_end = ending_pt;
    m_material = type_material;
		this->m_init();
	}

	// destructors
	~InternalStructuralElementObject(){
	}

	// getters
	int GetNumberOfPoints(){
		return m_nbrOfPoints;
	}

	StiffnessMatrixType GetLocalStiffnessMatrix(){
		return m_k;
	}

	DisplacementVectorType GetNodalDisplacementInLocalCoordinates(){
		return m_disp_local_coord;
	}

	ForceVectorType GetElementForcesInLocalCoordinates(){
		return m_f;
	}

private:
	// private variables
	// properties
	Point *m_start, *m_end;
	const unsigned int m_nbrOfPoints = 2;
	double m_L /*length*/, m_A /*cross section*/;
	Material m_material;
	// structural vectors and matrices
	StiffnessMatrixType m_k;
	DisplacementVectorType m_disp_local_coord;
	ForceVectorType m_f;

	// private functions
	void m_init(){
		// create a connexion in PointManager
		PointManager::GetInstance().SetConnexion(m_start,m_end);
		m_k = StiffnessMatrixType(m_nbrOfPoints*StructuralElementType::NDOF,m_nbrOfPoints*StructuralElementType::NDOF,arma::fill::zeros);
		m_L = sqrt(pow(m_start->x-m_end->x,2) + pow(m_start->y-m_end->y,2) + pow(m_start->z-m_end->z,2));
		m_disp_local_coord = DisplacementVectorType(m_nbrOfPoints*StructuralElementType::NDOF);
		m_f = ForceVectorType(StructuralElementType::NDOF);
	}

};

// TODO: include "InternalStructuralElementObject.cpp" ?

#endif
