
template<class StructuralElementType>
StiffnessBuilder<StructuralElementType>::
StiffnessBuilder(unsigned int nbrOfPoints){

	m_nbrOfPts = nbrOfPoints;

	m_stiffnessM = StiffnessMatrixType();
	m_stiffnessM.set_size(StructuralElementType::NDOF*m_nbrOfPts,StructuralElementType::NDOF*m_nbrOfPts);
	m_stiffnessM.fill(arma::fill::zeros);
}

template<class StructuralElementType>
StiffnessBuilder<StructuralElementType>::
~StiffnessBuilder(){
}

/**
 * @public
 * Build with a Stiffness, a Transform and 2 jointId
 */
template<class StructuralElementType>
void
StiffnessBuilder<StructuralElementType>::
Build(
		StiffnessMatrixType kl,
		TransformationMatrixType tm,
		unsigned int j1,
		unsigned int j2
){
	//StiffnessMatrixType kg = tm * kl * tm.t();
	//std::cout << tm << "\n" << std::endl;
	//std::cout << kg << "\n" << std::endl;
	m_build( tm * kl * tm.t(), j1, j2 );
}// end Build

template<class StructuralElementType>
void
StiffnessBuilder<StructuralElementType>::
m_build(StiffnessMatrixType k, JointIdType j1, JointIdType j2){

	unsigned int ndof = StructuralElementType::NDOF;
	unsigned int c=0,r=0,j=0,l1=j1*ndof,l2=j2*ndof;

	for(c=0;c<2*ndof;c++)
	for(r=0;r<2*ndof;r++)
	{
			if(c<ndof && r<ndof){
				m_stiffnessM(l1+r,l1+c) = m_stiffnessM(l1+r,l1+c) + k(r,c);
			}
			else if(c>=ndof && r<ndof){
				m_stiffnessM(l1+r,l2+c-ndof) = m_stiffnessM(l1+r,l2+c-ndof) + k(r,c);
			}
			else if(c>=ndof && r>=ndof){
				m_stiffnessM(l2+r-ndof,l2+c-ndof) = m_stiffnessM(l2+r-ndof,l2+c-ndof) + k(r,c);
			}
			else if(c<ndof && r>=ndof){
				m_stiffnessM(l2+r-ndof,l1+c) = m_stiffnessM(l2+r-ndof,l1+c) + k(r,c);
			}
	}

}// end m_build


