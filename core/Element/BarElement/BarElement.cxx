
template<class StructuralElementType>
BarElement<StructuralElementType>::
BarElement(
		Point* starting_pt,
		Point* ending_pt,
		double cross_section, 
		Material type_material,
		double alpha)
{
	m_start_p = starting_pt;
	m_end_p = ending_pt;
	this->m_A = cross_section;
	this->m_material = type_material;
	this->m_alpha = alpha;

	// create the InteralElement
	InternalElementType* el = new InternalElementType( m_start_p, m_end_p, this->m_A, this->m_material, this->m_alpha );
	this->m_internalElementVector->push_back(el);

	// create the stiffness matrix in global coordinate
	this->m_k = StiffnessMatrixType(this->GetNumberOfNodes()*StructuralElementType::NDOF,this->GetNumberOfNodes()*StructuralElementType::NDOF,arma::fill::zeros);
	// populate the stiffness matrix
	StiffnessBuilder<StructuralElementType> builder = StiffnessBuilder<StructuralElementType>(this->GetNumberOfNodes());
	builder.Build(
			this->m_internalElementVector->at(0)->GetLocalStiffnessMatrix(),
			this->m_internalElementVector->at(0)->GetTransformationMatrix(),
			0,1);// only one InternalElementType element
	this->m_k = builder.GetStiffnessMatrix();

	// Young's modulus
	this->m_E = el->GetYoungModulus();

	// compute the length
	this->m_ComputeLength();
}

template<class StructuralElementType>
BarElement<StructuralElementType>::
~BarElement()
{
}

/*
template<class StructuralElementType>
void
BarElement<StructuralElementType>::
m_ComputeLength(){
}
*/	
