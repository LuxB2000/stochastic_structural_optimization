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


	/*
	 * Basic Solver functions
	 * Find the nodal displacements based on the external forces
	 * ForceVectorType with size equals to K.n_col
	 * BoundaryConditionsVectorType contains a certain number of Boundary.
	 * Each boundary will restrict the stiffness matrix and the force vector
	 *	bcv.at(i) := std::vector with size=1
	 *	bcv.at(i).at(o) = node_id
	 *	bcv.at(i).at(1) = dof
	 */
	void ComputeNodeDisplacements( 
			DisplacementVectorType* disp, 
			StiffnessMatrixType K,
			ForceVectorType *f_ext,
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
