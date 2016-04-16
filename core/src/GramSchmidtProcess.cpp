//
// Created by plumat on 4/13/16.
//

#include "../headers/GramSchmidtProcess.h"

GramSchmidtProcess::GramSchmidtProcess() {

}

GramSchmidtProcess::~GramSchmidtProcess() {

}

void GramSchmidtProcess::ComputeOrthonormalBasisFromVector(VectorType *v, VectorType *e1, VectorType *e2,
                                                           VectorType *e3) {

    // find 2 vectors linearly independent of v
    VectorType u1 = {1,0,0}, u2 = {0,1,0};
    // check if they are actually linear independent
    arma::mat M = arma::mat(3,3,arma::fill::zeros);
    unsigned int i=0;
    do{
        if(i==1){
            u1 = {0,1,0}; u2={0,0,1};
        }
        if( i== 2){
            u1 = {0,-(*v)(2), (*v)(2)};
            u2 = {-(*v)(2),0,}();
        }
        if(i>2){
            std::cerr << "GramSchmidtProces::CompoteOrthogonalBasisFromVector Can't find a linear independent set." << std::endl;
            exit(EXIT_FAILURE);
        }
        M = { {(*v)(0), u1(0), u2(0)}, {(*v)(1), u1(1), u2(1)}, {(*v)(2),u1(2),u2(2)} };
        i++;

    }while(det(M)!=0);

    // compute the orthonormal basis
    *e1 = VectorType(*v);



}

void GramSchmidtProcess::Proj(VectorType *u, VectorType *v, VectorType* p) {
    (*p) = (dot(*u,*v)/dot(*u,*u)) * (*u);
}

