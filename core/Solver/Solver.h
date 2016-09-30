/*
 * =====================================================================================
 *
 *       Filename:  Solver.h
 *
 *    Description:  An object to solve the matrix equation to find the displacements 
 *									and the forces.
 *
 *        Version:  1.0
 *        Created:  30/09/16 15:41:50
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jerome Plumat (JP), 
 *        Company:  
 *
 * =====================================================================================
 */


#ifndef SSO_SOLVER_H
#define SSO_SOVLER_H

template<class StructuralElementType>
class Solver {
public:

	// constructor
	Solver();
	~Solver();


	void ComputeNodeDisplacements( 
			DisplacementVectorType* disp, 
			StiffnessMatrixType K,
			ForceVectorType *f,
			BoundaryConditionsVectorType* bcv);

	void ComputeElementForces(
			DisplacementVectorType* disp, 
			StiffnessMatrixType K,
			ForceVectorType *f,
			BoundaryConditionsVectorType* bcv);

private:


};

#include "Solver.cxx"
#endif
