
template<class StructuralElementType>
Solver<StructuralElementType>::
Solver(){
}

template<class StructuralElementType>
Solver<StructuralElementType>::
Solver(
				StiffnessMatrixType Kg,
				BoundaryConditionsVectorType *bcv,
				ForceVectorType *f_ext,
				DisplacementVectorType *disp,
				ForceVectorType *f_reaction_sup,
				ForceVectorType *f_elem)
{
	m_active_dof = std::vector<unsigned int>();
	// inialize the stiffness matrix
	m_K_reduced = StiffnessMatrixType(Kg);
	m_K = StiffnessMatrixType(Kg);
	// init the pointers
	m_f_ext = f_ext;
	m_f_ext_reduced = ForceVectorType(*f_ext);
	m_f_reaction_sup = f_reaction_sup;
	m_disp = disp;
	m_bc = bcv;
	
	unsigned int i=0, j=0,d=0,r=0,c=0;
	unsigned long R=0,C=0,L=0;
	unsigned int NDOF = StructuralElementType::NDOF;

	/*
	R = m_K_reduced.n_rows;
	C = m_K_reduced.n_cols;
	*/
	L = m_bc->size();

	/*
	for(i=0; i<L; i++){
			j=m_bc->at(i).bc[0]*NDOF; // at joint j
			d=m_bc->at(i).bc[1]; // direction d
			for(c=0;c<C;c++){
					m_K_reduced.at(j+d,c) = 0;
			}
			for(r=0;r<R;r++){
					m_K_reduced.at(r,j+d) = 0;
			}
	}
	*/
	for(i=0; i<L; i++){
			j=m_bc->at(i).bc[0]*NDOF; // at joint j
			d=m_bc->at(i).bc[1]; // direction d
			m_K_reduced.shed_row(j+d-i); // -i since we removed some row or column => the size of the matrix is changing
			m_K_reduced.shed_col(j+d-i);
			m_f_ext_reduced.shed_row(j+d-i);
	}

	// find the active degree of freedom
//	std::cout << "Active dof: ";
	std::vector<unsigned int> constraint_dof = std::vector<unsigned int>(m_K.n_cols,0);
	for( i=0; i<L; i++){
		j=m_bc->at(i).bc[0]*NDOF; // at joint j
		d=m_bc->at(i).bc[1]; // direction d
		constraint_dof.at( j + d ) = 1;
	}
	L = m_K.n_cols;
	for( i=0; i<L; i++ ){
		if( constraint_dof.at(i) == 0 ){
			m_active_dof.push_back( i );
//			std::cout << i << "  ";
		}
	}

//	std::cout << std::endl;

}//end constructor

template<class StructuralElementType>
Solver<StructuralElementType>::
~Solver(){
}

template<class StructuralElementType>
void
Solver<StructuralElementType>::
ComputeNodeDisplacements()
{

	unsigned int L = m_active_dof.size();
	DisplacementVectorType d;

		// solve the system using armadillo
		// check if the matrix is singular (det==0)
		if( det(m_K_reduced) == 0 ){
			// matrix is singular, used the Moore-Penrose pseudoinverse
			LOG(WARNING) << "The matrix is singular, attempt to solve the system with Moore-Penrose pseudoinverse." << std::endl;
			d =  pinv(m_K_reduced)*(m_f_ext_reduced);
		}else{
	    solve(d,m_K_reduced,m_f_ext_reduced,arma::solve_opts::fast);
		}

		for( unsigned int i=0, c=0; i<L; i++, c++ ){
			(*m_disp)[m_active_dof.at(i)] = d[c];
		}
}

template<class StructuralElementType>
void
Solver<StructuralElementType>::ComputeSupportReactions()
{
	// find the support reaction
	(*m_f_reaction_sup) = m_K * (*m_disp);

	// set the support reactions at each active dof to 0
	unsigned int i=0, L=0;
	L=m_active_dof.size();
	for( i=0; i<L; i++ ){
		//std::cout << "TEST: " << i << std::endl;
		(*m_f_reaction_sup)[m_active_dof.at(i)] = 0;
	}
}


