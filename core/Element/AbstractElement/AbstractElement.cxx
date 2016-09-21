
template<class StructuralElementType>
AbstractElement<StructuralElementType>::
AbstractElement()
{
	m_L = 0.0;
	m_A = 0.0;
	m_alpha = 0.0;

	m_internalElementVector = NULL;

	m_internalElementVector = new InternalElementVectorType();
	m_k = StiffnessMatrixType(0,0,arma::fill::zeros);
	m_c = TransformationMatrixType(0,0,arma::fill::zeros);
	m_elementForces = new ElementForceVectorType();
	m_nodeDisplacements = new NodeDisplacementVectorType();
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
	if( m_elementForces ) delete m_elementForces;
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
