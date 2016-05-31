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
	virtual void SetNodalDisplacementInGlobalCoordinates(DisplacementVectorType disp) =0;

	// getters
	// =======
	// get Displacement 
	const DisplacementVectorType GetDisplacementInLocalCoordinates(){
		return DisplacementVectorType(*m_disp_local_coord);
	}
	DisplacementVectorType* GetDisplacementInLocalCoordinatesPointer(){
		return m_disp_local_coord;
	}
	// get nodal forces
	virtual const ForceVectorType GetNodalForces() {
		return ForceVectorType(*m_f);
	}
	ForceVectorType* GetNodalForcesPointer() {
		return m_f;
	}
	// get Stifness
  StiffnessMatrixType* GetStiffnessMatrixInGlobalCoordPointer(){
		return m_k; 
	}
  const StiffnessMatrixType GetStiffnessMatrixInGlobalCoord(){
		return StiffnessMatrixType(*m_k); 
	}

	// we don't want to give access to the transformation matrix since
	// the Truss can be corner etc. The transformation matrix is local to 
	// InternalTrussObject
	// TODO: Is really usefull to give access to nodal forces in local coord.?
	// Due to local coord system, the length of the force vector is equal
	// to #InernalTruss*2*3 (2pts per InternalTruss and 3 dof).
	
protected:
  double m_A, m_E, m_L;
	unsigned int m_numberOfInternalTruss;
	typedef std::vector<InternalTrussObject*> InternalTrussVectorType;
	InternalTrussVectorType* m_abstractTrussVector;
	StiffnessMatrixType* m_k;
	DisplacementVectorType* m_disp_local_coord;
	TransformationMatrixType* m_c;
	ForceVectorType* m_f;

	// compute the length
	virtual void m_ComputeLength();
	// populat the different matrices
	//virtual void m_PopulateMatrices() = 0;

};

#endif
