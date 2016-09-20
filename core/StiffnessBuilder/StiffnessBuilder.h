/*
 * =====================================================================================
 *
 *       Filename:  StiffnessBuilder.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  20/09/16 10:28:10
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jerome Plumat (JP), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef SSO_STIFFNESSBUILDER_H
#define SSO_STIFFNESSBUILDER_H

#include "armadillo"
#include <vector>
#include "Types.h"

template<class StructuralElementType>
class StiffnessBuilder{
public:

	StiffnessBuilder(unsigned int nbrOfPoints);
	~StiffnessBuilder();

	// getter
	/*
	 * @public
	 * get the constructed stiffness matrix
	 */
	StiffnessMatrixType GetStiffnessMatrix(){
		return m_stiffnessM;
	}

	// builder
	/*
	 * @public
	 * default function to construct simple elements with
	 * InternalStructuralElementObject and Points*
	 * Warning: we assume joinId1<jointId2
	 */
    void Build(StiffnessMatrixType kl, TransformationMatrixType cl,
				JointIdType jointId1, JointIdType jointId2);

private:
	StiffnessMatrixType m_stiffnessM;
	unsigned int m_nbrOfPts;

	// private function
	// actually built the stiffness matrix
	void m_build(StiffnessMatrixType k, JointIdType j1, JointIdType j2);
};

#include "StiffnessBuilder.cxx"

#endif


