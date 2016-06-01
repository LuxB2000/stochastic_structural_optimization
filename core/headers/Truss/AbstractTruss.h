/*
 * =====================================================================================
 *
 *       Filename:  AbstractTruss.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/06/16 13:39:55
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jerome Plumat (JP)
 *
 * =====================================================================================
 */


#ifndef sso_TRUSSOBJECT_H
#define sso_TRUSSOBJECT_H

#include "InternalTrussObject.h"

class AbstractTruss{
public:
	AbstractTruss();
	~AbstractTruss();
	
	// getters
	// virtual
	virtual double GetLength(){ return m_L;}
	virtual double GetCrossSection(){ return m_A;}
	virtual double GetYoungModulus(){ return m_E;}

	// setters
	// =======
	void SetNodalDisplacementInGlobalCoordinates(DisplacementVectorType disp);

	// getters
	// =======
	// get Displacement 
	const DisplacementVectorType GetNodalDisplacementInLocalCoordinates(){
		return DisplacementVectorType(*m_disp_local_coord);
	}
	DisplacementVectorType* GetNodalDisplacementInLocalCoordinatesPointer(){
		return m_disp_local_coord;
	}
	// get Stifness
  StiffnessMatrixType* GetStiffnessMatrixInGlobalCoordPointer(){
		return m_k; 
	}
  const StiffnessMatrixType GetStiffnessMatrixInGlobalCoord(){
		return StiffnessMatrixType(*m_k); 
	}

	// get elements forces
	// return a number of elements * ndof vector with encoing is (F0x,F0y,F0z,F1x,...,FNz) where N is the number
	// of elements
	 ElementVectorType GetElementForcesInLocalCoord(){
		  ElementVectorType(*m_elementForces);
	 }
	 ElementVectorType* GetElementForcesInLocalCoordPointer(){
		 return m_elementForces;
	 }

	
protected:
  double m_A, m_E, m_L;
	unsigned int m_numberOfInternalTruss, m_numberOfNodes, m_numberOfDOF;
	typedef std::vector<InternalTrussObject*> InternalTrussVectorType;
	InternalTrussVectorType* m_internalTrussVector;
	StiffnessMatrixType* m_k;
	DisplacementVectorType* m_disp_local_coord;
	TransformationMatrixType* m_c;
	ElementVectorType* m_elementForces;

	void m_PopulateForceDisplacementvectors();

	// compute the length
	virtual void m_ComputeLength();
	// populat the different matrices
	//virtual void m_PopulateMatrices() = 0;

};

#endif
