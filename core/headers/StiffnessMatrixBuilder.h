//
// Created by plumat on 20/04/16.
//

#ifndef SSO_STIFFNESSMATRIX_H
#define SSO_STIFFNESSMATRIX_H

#include "armadillo"
#include <vector>
#include "Types.h"
#include "Point.h"

class StiffnessMatrixBuilder {
public:
	typedef std::vector<JointIdType> JointIdVectorType;

    /*
     * Constructor
     * Needs the number degrees of freedom to construct the stiffness matrix
     */
    StiffnessMatrixBuilder(int nbr_dof);
    ~StiffnessMatrixBuilder();

    /*
     * Build the GLOBAL stiffness matrix based on 
     * - a truss element local stiffness matrix kl
     * - a truss element local transformation matrix cl
     * - the two joints ID delimiting the truss
     *          ! joindId1 < joindId2
     *          ! (0<=joinId<nbr_dof)
		 * TODO: test error if JoindId are not properly set
		 * WARNING: kl is assumed to be a 6x6 matrix only: SimpleTrussElement or InternalTruss element only
     */
    //void Build(StiffnessMatrixType* kl, TransformationMatrixType* cl, unsigned int jointId1, unsigned int jointId2);
    void Build(StiffnessMatrixType* kl, TransformationMatrixType* cl, JointIdType jointId1, JointIdType jointId2);

    /*
     * Build the GLOBAL stiffness matrix based on 
     * - a truss element stiffness matrix in global coordinates kg 
     * - the two joints ID delimiting the truss
     *          ! joindId1 < joindId2
     *          ! (0<=joinId<nbr_dof)
		 * WARNING: kl is assumed to be a 6x6 matrix only: SimpleTrussElement or InternalTruss element only
     */
    void Build(StiffnessMatrixType* kg, JointIdType jointId1, JointIdType jointId2);

		/*
		 * Construct a stiffness matrix based on two stiffness matrices 
		 * and their respective set of joint Ids, they will be used to identify
		 * rows and columns.
		 * We need to specify two matrices because if a Truss is common to the 
		 * structures we need to take into account only one time.
		 * We identify these commun elements with jointIdList_i if they contain 
		 * a same sequences of ids {id1,id2} then the stiffness row and column
		 * will be taken into consideration only one time while building the 
		 * new Stiffness matrix.
		 */
		void Build(StiffnessMatrixType* kg1, JointIdVectorType jointIdList1);

    // getter
    const StiffnessMatrixType GetStiffnessMatrix();
    StiffnessMatrixType* GetStiffnessMatrixPointer();

private:
    typedef arma::fmat InternalTransformationMatrixType;
    int m_kg_truss_sz;
    StiffnessMatrixType* m_kg_truss;
		void m_build(StiffnessMatrixType* kl, unsigned int id1, unsigned int id2);
};

#endif //SSO_STIFFNESSMATRIX_H
