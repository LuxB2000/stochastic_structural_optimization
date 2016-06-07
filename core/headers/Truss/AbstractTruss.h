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
	virtual void SetDisplacementInGlobalCoordinates(DisplacementVectorType disp) =0;
	virtual ForceVectorType GetNodalForces() {return ForceVectorType(*m_f);}

	// generic
	const DisplacementVectorType GetDisplacementInLocalCoordinates(){return DisplacementVectorType(*m_disp_local_coord);}
  StiffnessMatrixType*      GetLocalStiffnessMatrixPointer(){ return m_k; }
  const StiffnessMatrixType GetLocalStiffnessMatrix() { return StiffnessMatrixType(*m_k); }
  TransformationMatrixType*  GetLocalTransformationMatrixPointer(){ 
    return m_c; }
  const TransformationMatrixType  GetLocalTransformationMatrix(){ return TransformationMatrixType(*m_c); }
	
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
	//virtual void m_ComputeLength() = 0;
	// populat the different matrices
	//virtual void m_PopulateMatrices() = 0;

};

#endif
