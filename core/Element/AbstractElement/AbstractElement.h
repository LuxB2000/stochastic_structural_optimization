/*
 * =====================================================================================
 *
 *       Filename:  AbstractElement.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  21/09/16 16:14:55
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jerome Plumat (JP), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef SSO_ABSTRACTELEMENT_H
#define SSO_ABSTRACTELEMENT_H

#include "InternalStructuralElementObject.h"

template<class StructuralElementType>
class AbstractElement{
public:
	// constructor
	AbstractElement();
	~AbstractElement();
	
	// getters
	double GetLength(){
		return m_L;
	}
	double GetCrossSection(){
		return m_A;
	}
	double GetYoungModulus(){
		return m_E;
	}
  StiffnessMatrixType GetStiffnessMatrix(){
		return m_k; 
	}

	virtual unsigned int GetNumberOfNodes(){ return 0; }
	unsigned int GetNumberOfElements(){ return this->GetNumberOfNodes() - 1; }

	// set the displacement in local coordinate system
	void SetDisplacementInGlobalCoord(DisplacementVectorType disp_gc);
	// return a 2xNDOF vector
	DisplacementVectorType GetDisplacementInLocalCoord();
	// return a 2xNDOF vector
	ForceVectorType GetForceInLocalCoord();

protected:
  double m_A, m_E, m_L, m_alpha;
	Material m_material;
	unsigned int m_numberOfInternalElement, m_numberOfNodes;

	// will contains the internal truss objects
	typedef InternalStructuralElementObject<StructuralElementType> InternalElementType;
	typedef std::vector<InternalElementType*> InternalElementVectorType;

	// internal Element vector
	InternalElementVectorType* m_internalElementVector;

	// arma object, pure matrices
	StiffnessMatrixType m_k;
	TransformationMatrixType m_c;

	//std::vector<float> m_elementForces;
	NodeDisplacementVectorType* m_nodeDisplacements;

	// populate the force and displacement vectors
	void m_PopulateForceDisplacementvectors();

	// compute the length
	void m_ComputeLength();

	// displacements and foces
	DisplacementVectorType m_disp_gc, m_disp_lc;
	ForceVectorType m_f_elem_lc;

};

#include "AbstractElement.cxx"

#endif

