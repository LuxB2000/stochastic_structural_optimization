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
	AbstractElement();
	~AbstractElement();

private:
  double m_A, m_E, m_L;
	unsigned int m_numberOfInternalTruss, m_numberOfNodes, m_numberOfDOF;

	// will contains the internal truss objects
	typedef std::vector<InternalTrussObject*> InternalTrussVectorType;
	InternalTrussVectorType* m_internalTrussVector;

	// arma object, pure matrices
	StiffnessMatrixType* m_k;
	TransformationMatrixType* m_c;

	ElementForceVectorType* m_elementForces;
	NodeDisplacementVectorType* m_nodeDisplacements;

	// populate the force and displacement vectors
	void m_PopulateForceDisplacementvectors();

	// compute the length
	virtual void m_ComputeLength();

};

#include "AbstractElement.cxx"

#endif

