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
     */
    //void Build(StiffnessMatrixType* kl, TransformationMatrixType* cl, unsigned int jointId1, unsigned int jointId2);
    void Build(StiffnessMatrixType* kl, TransformationMatrixType* cl, unsigned int jointId1, unsigned int jointId2);

    /*
     * Build the GLOBAL stiffness matrix based on 
     * - a truss element stiffness matrix in global coordinates kg 
     * - the two joints ID delimiting the truss
     *          ! joindId1 < joindId2
     *          ! (0<=joinId<nbr_dof)
     */
    void Build(StiffnessMatrixType* kg, Point::IndexType jointId1, Point::IndexType jointId2);

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
