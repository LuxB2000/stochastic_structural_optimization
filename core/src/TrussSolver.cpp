
#include "TrussSolver.h"

TrussSolver::TrussSolver(){

}

TrussSolver::~TrussSolver(){
}

void TrussSolver::ComputeDisplacements(DisplacementVectorType *disp, StiffnessMatrixType *K, ForceVectorType *f, BoundaryConditionsVectorType* bcv) {
    unsigned int i=0, j=0,d=0,r=0,c=0;
    unsigned long R=0,C=0,L=0;

    StiffnessMatrixType K_reduced = StiffnessMatrixType(*K);

    R = K_reduced.n_rows;
    C = K_reduced.n_cols;
    L = bcv->size();

    for(i=0; i<L; i++){
        j=bcv->at(i).bc[0]*3; // at joint j
        d=bcv->at(i).bc[1]; // direction d
        for(c=0;c<C;c++){
            K_reduced.at(j+d,c) = 0;
        }
        for(r=0;r<R;r++){
            K_reduced.at(r,j+d) = 0;
        }
    }

    solve(*disp,K_reduced,*f,arma::solve_opts::fast);
}
void TrussSolver::ComputeSupportReaction(DisplacementVectorType *disp, StiffnessMatrixType *K, ForceVectorType *f,
                                         BoundaryConditionsVectorType *bcv) {
    unsigned int i = 0, j = 0, d = 0, r = 0, c = 0;
    unsigned long R = 0, C = 0, L = 0;

    StiffnessMatrixType K_reduced = StiffnessMatrixType(*K);

    R = K_reduced.n_rows;
    C = K_reduced.n_cols;
    L = bcv->size();

    bool found = false;
    for (c = 0; c < C; c++) {
        for (i = 0; i < L; i++) {
            j = bcv->at(i).bc[0] * 3; // at joint j
            d = bcv->at(i).bc[1]; // direction d
            if ( j+d == c ) {
                found = true;
                break;
            }
        }
        if(found){
            for (r = 0; r < R; r++) {
                    K_reduced.at(r, c) = 0;
            }
        }
        found = false;
    }

    *f = K_reduced * (*disp);
}
