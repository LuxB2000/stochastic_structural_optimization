//
// Created by plumat on 4/26/16.
//
// A simple solver for truss only problem

#ifndef SSO_TRUSSSOLVER_H
#define SSO_TRUSSSOLVER_H

#include "armadillo"

class TrussSolver{
public:
    typedef arma::fvec     DisplacementVectorType;
    typedef arma::fmat     StiffnessMatrixType;
    typedef arma::fvec     ForceVectorType;
    typedef struct BoundaryConditionsTyped  {unsigned  int bc[2];} BoundaryConditionsType;
    typedef std::vector<BoundaryConditionsType>   BoundaryConditionsVectorType;

    TrussSolver();
    ~TrussSolver();

    /*
     * ComputeDisplacements
     * Compute the displacements of the joints that are not restrained by boundary conditions
     * @inputs DisplacementVectorType *disp
     * @input StiffnessMatrixType *K
     * @input ForceVectorType *f
     * @input BoundaryConditionVectorType* bcv
     */
    void ComputeDisplacements(DisplacementVectorType* disp, StiffnessMatrixType* K, ForceVectorType* f, BoundaryConditionsVectorType* bcp);

};

#endif //SSO_POINT_H