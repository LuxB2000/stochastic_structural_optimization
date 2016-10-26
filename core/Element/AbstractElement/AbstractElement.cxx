
template<class StructuralElementType>
AbstractElement<StructuralElementType>::
AbstractElement()
{
	m_L = 0.0;
	m_A = 0.0;
	m_alpha = 0.0;
	m_E = 0.0;

	m_internalElementVector = NULL;

	m_internalElementVector = new InternalElementVectorType();
	m_k = StiffnessMatrixType(0,0,arma::fill::zeros);
	m_c = TransformationMatrixType(0,0,arma::fill::zeros);
	m_nodeDisplacements = new NodeDisplacementVectorType();

	//m_elementForces = std::vector<float>(this->GetNumberOfNodes()*StructuralElementType::NDOF);
}

template<class StructuralElementType>
AbstractElement<StructuralElementType>::
~AbstractElement()
{
	unsigned int i=0;
	if( m_internalElementVector ){
		for( i=0; i<m_internalElementVector->size(); i++ ){
			if( m_internalElementVector->at(i) ){
				delete m_internalElementVector->at(i);
			}
		}
	}
	//if( m_elementForces ) delete m_elementForces;
	if( m_nodeDisplacements ) delete m_nodeDisplacements;
}

template<class StructuralElementType>
void
AbstractElement<StructuralElementType>::
m_ComputeLength()
{
	unsigned int i=0,l=0;
	l = m_internalElementVector->size();

	m_L = 0;
	for(i=0; i<l; i++ ){
		m_L += m_internalElementVector->at(i)->GetLength();
	}
}

template<class StructuralElementType>
void
AbstractElement<StructuralElementType>::
SetDisplacementInGlobalCoord(DisplacementVectorType disp_gc){
	// record the displacement in global coordinates
	m_disp_gc = disp_gc;

	unsigned int i=0, L=0, n=0, ndof = StructuralElementType::NDOF;
	L = m_internalElementVector->size();
	// 2 points per internal element
	DisplacementVectorType disp_i_gc = DisplacementVectorType(2*StructuralElementType::NDOF, arma::fill::zeros);
	DisplacementVectorType disp_i_lc = DisplacementVectorType(2*StructuralElementType::NDOF, arma::fill::zeros);
	ForceVectorType f_elem_i_lc;

	// set the global displacement for each internal element
	for( i=0; i<L; i++){
		for( n=0; n<2*ndof; n++ ){
			disp_i_gc[n] = m_disp_gc[n+i*ndof];
		}
		m_internalElementVector->at(i)->SetDisplacementInGlobalCoord(disp_i_gc);
		disp_i_lc = m_internalElementVector->at(i)->GetDisplacementInLocalCoord();
		f_elem_i_lc = m_internalElementVector->at(i)->GetElementForcesInLocalCoordinates();
		// collect the internal displacements and forces
		/*
		std::cout << "test - length disp_i_lc: " << disp_i_lc.n_elem << std::endl;
		std::cout << "test - length f_elem_i_lc: " << f_elem_i_lc.n_elem << std::endl;
		std::cout << "test - length f_elem_lc: " << m_f_elem_lc.n_elem << std::endl;
		std::cout << "test - length m_disp_lc: " << m_disp_lc.n_elem << std::endl;
		*/
		for( n=0; n<2*ndof; n++ ){
			// std::cout << "n= " << n << " ind1: " << n+i*ndof << std::endl;
			m_disp_lc[n+i*ndof] = disp_i_lc[n];
			m_f_elem_lc[n+i*ndof] = f_elem_i_lc[n];
		}
	} // end for i

}// end SetDisplacementInGlobalCoord


template<class StructuralElementType>
DisplacementVectorType
AbstractElement<StructuralElementType>::
GetDisplacementInLocalCoord(){
	return m_disp_lc;
}

template<class StructuralElementType>
ForceVectorType
AbstractElement<StructuralElementType>::
GetForceInLocalCoord(){
	return m_f_elem_lc;
}

