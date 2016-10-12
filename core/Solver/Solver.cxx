
template<class StructuralElementType>
Solver<StructuralElementType>::
Solver(){
}

template<class StructuralElementType>
Solver<StructuralElementType>::
~Solver(){
}

template<class StructuralElementType>
void
Solver<StructuralElementType>::
ComputeNodeDisplacements( 
		DisplacementVectorType* disp, 
		StiffnessMatrixType K,ForceVectorType *f,
		BoundaryConditionsVectorType* bcv)
{

    unsigned int i=0, j=0,d=0,r=0,c=0;
    unsigned long R=0,C=0,L=0;
		unsigned int NDOF = StructuralElementType::NDOF;

    StiffnessMatrixType K_reduced = StiffnessMatrixType(K);

    R = K_reduced.n_rows;
    C = K_reduced.n_cols;
    L = bcv->size();

    for(i=0; i<L; i++){
        j=bcv->at(i).bc[0]*NDOF; // at joint j
        d=bcv->at(i).bc[1]; // direction d
        for(c=0;c<C;c++){
            K_reduced.at(j+d,c) = 0;
        }
        for(r=0;r<R;r++){
            K_reduced.at(r,j+d) = 0;
        }
    }

		// solve the system using armadillo
		// check if the matrix is singular (det==0)
		if( det(K_reduced) == 0 ){
			// matrix is singular, used the Moore-Penrose pseudoinverse
			*disp = pinv(K_reduced)*(*f);
		}else{
	    solve(*disp,K_reduced,*f,arma::solve_opts::fast);
		}
}

void ComputeElementForces(
		DisplacementVectorType* disp, 
		StiffnessMatrixType K,
		ForceVectorType *f,
		BoundaryConditionsVectorType* bcv){
}

