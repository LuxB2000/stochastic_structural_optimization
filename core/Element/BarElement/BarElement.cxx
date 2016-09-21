
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
	m_A = cross_section;
	m_material = type_material;
	m_alpha = alpha;
}

template<class StructuralElementType>
BarElement<StructuralElementType>::
~BarElement()
{
}

