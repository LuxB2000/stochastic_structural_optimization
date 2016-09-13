
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
	InternalStructuralElementObject(Point* starting_pt, Point* ending_pt, double cross_section, Material type_material);

	// destructors
	~InternalStructuralElementObject();

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
	// variables
	Point *m_start, *m_end;
	const unsigned int m_nbrOfPoints = 2;
	double m_L /*length*/, m_A /*cross section*/;
	Material m_material;

	// structural vectors and matrices
	StiffnessMatrixType m_k;
	DisplacementVectorType m_disp_local_coord;
	ForceVectorType m_f;

	// private functions
	void m_init();

};

#include "InternalStructuralElementObject.cpp"

#endif
