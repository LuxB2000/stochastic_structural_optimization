//
// Created by plumat on 4/13/16.
//

#ifndef SSO_GRAMSCHMIDTPROCESS_H
#define SSO_GRAMSCHMIDTPROCESS_H

#include <armadillo>

class GramSchmidtProcess{
public:

    typedef arma::Col<double> VectorType; // short for Col<double>

    GramSchmidtProcess();
    ~GramSchmidtProcess();

    /*
     * Compute a orthogonal and normal basis {e1,e2,e3} of the vector v
     * The output basis is right handed
     */
    void ComputeOrthonormalBasisFromVector(VectorType* v, VectorType* e1, VectorType* e2, VectorType* e3);

    // compute the projection 'p' of 'v' on 'u'
    void Proj(VectorType* u, VectorType* v, VectorType* p);

private:

};

#endif //SSO_GRAMSCHMIDTPROCESS_H
