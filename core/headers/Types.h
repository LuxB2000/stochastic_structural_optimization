//
// Created by plumat on 3/05/16.
//

#ifndef SSO_TYPES_H
#define SSO_TYPES_H

#include "armadillo"
#include <vector>

typedef arma::fmat StiffnessMatrixType;
typedef arma::fmat TransformationMatrixType;
typedef arma::fvec ForceVectorType;
typedef arma::fvec InternalForceVectorType;

typedef arma::fvec DisplacementVectorType;
typedef struct BoundaryConditionsTyped  {unsigned  int bc[2];} BoundaryConditionsType;
typedef std::vector<BoundaryConditionsType>   BoundaryConditionsVectorType;

// Truss types
typedef std::vector<InternalForceVectorType*> ElementForceVectorType;
typedef std::vector<DisplacementVectorType*> NodeDisplacementVectorType;

// Frame types
typedef std::vector<float> FrameParametersVectorType;

// Joint types
typedef unsigned int JointIdType;
#endif //SSO_TYPES_H
