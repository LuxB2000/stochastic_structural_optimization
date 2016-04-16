//
// Created by plumat on 20/04/16.
//

#ifndef SSO_STIFFNESSMATRIX_H
#define SSO_STIFFNESSMATRIX_H

#include "armadillo"

class StiffnessMatrixBuilder {
public:

    typedef arma::fmat StiffnessMatrixType;
    typedef arma::fmat TransformationMatrixType;

    StiffnessMatrixBuilder();
    ~StiffnessMatrixBuilder();

    /*
     * Build the GLOBAL stiffness matrix based on 
     * - a truss element local stiffness matrix kl
     * - a truss element local transformation matrix cl
     */
    void Build(StiffnessMatrixType* kl, TransformationMatrixType* cl);

    // getter
    const StiffnessMatrixType GetStiffnessMatrix();
    StiffnessMatrixType* GetStiffnessMatrixPointer();

private:
    int m_kg_truss_sz;
    StiffnessMatrixType* m_kg_truss;
};

#endif //SSO_STIFFNESSMATRIX_H
