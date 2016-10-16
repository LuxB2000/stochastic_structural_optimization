
#ifndef sso_INTERNALSTRUCTURALELEMENTOBJECT_H
#define sso_INTERNALSTRUCTURALELEMENTOBJECT_H

#include <vector>
#include "Types.h"
#include "Point.h"
#include "Material.h"
#include "PointManager.h"
#include "TrussType.h"
#include "BeamType.h"
#include "GramSchmidtProcessTest.h"


template<class StructuralElementType>
class InternalStructuralElementObject{
public:

	// constructor
	InternalStructuralElementObject(Point* starting_pt, Point* ending_pt, double cross_section, Material type_material, double alpha = 0.0 );

	// destructors
	~InternalStructuralElementObject();

	// getters
	double GetLength(){
		return m_L;
	}

	int GetNumberOfPoints(){
		return m_nbrOfPoints;
	}

	float GetYoungModulus(){
		return m_E;
	}

	float GetCrossSection(){
		return m_A;
	}

	StiffnessMatrixType GetLocalStiffnessMatrix(){
		return m_k;
	}

	TransformationMatrixType GetTransformationMatrix(){
		return m_c;
	}

	//TODO: remove
	DisplacementVectorType GetNodalDisplacementInLocalCoordinates(){
		return m_disp_lc;
	}

	DisplacementVectorType GetDisplacementInLocalCoord(){
		return m_disp_lc;
	}

	// TODO: change name to have the same as in AbstractElement
	ForceVectorType GetElementForcesInLocalCoordinates(){
		return m_f;
	}

	void SetDisplacementInGlobalCoord(DisplacementVectorType disp_gc);

private:
	// variables
	Point *m_start, *m_end;
	const unsigned int m_nbrOfPoints = 2;
	double m_L /*length*/, m_A /*cross section*/, m_E /*Young's modulus*/,
				 m_alpha /*the angle between the local X and global X*/,
				 m_GJ /**/, m_Iy /**/, m_Iz/**/, m_Iyz/**/ ;
	Material m_material;

	// structural vectors and matrices
	StiffnessMatrixType m_k;
	DisplacementVectorType m_disp_lc, m_disp_gc;
	ForceVectorType m_f;
  TransformationMatrixType m_c;

	// private functions
	void m_init();

};

#include "InternalStructuralElementObject.cxx"

#endif
