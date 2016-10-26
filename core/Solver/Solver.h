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
	Solver(
				StiffnessMatrixType Kg,
				BoundaryConditionsVectorType *bc,
				ForceVectorType *f_ext,
				DisplacementVectorType *disp,
				ForceVectorType *f_reaction_sup,
				ForceVectorType *f_elem);
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
	 *
	 * These functions are not dedicated to compute forces in elements since
	 * the solver doesn't have access to transformation matrix
	 */
	void ComputeNodeDisplacements();
			/*
			DisplacementVectorType* disp, 
			StiffnessMatrixType K,
			ForceVectorType *f_ext,
			BoundaryConditionsVectorType* bcv);
			*/

	void ComputeSupportReactions();
			/*
			DisplacementVectorType* disp, 
			StiffnessMatrixType K,
			ForceVectorType *f_ext,
			BoundaryConditionsVectorType* bcv);
			*/

private:
	ForceVectorType *m_f_ext, m_f_ext_reduced, *m_f_reaction_sup, m_f_elem;
	DisplacementVectorType *m_disp;
	StiffnessMatrixType m_K_reduced, m_K;
	BoundaryConditionsVectorType *m_bc;
	std::vector< unsigned int > m_active_dof;



};

#include "Solver.cxx"
#endif
