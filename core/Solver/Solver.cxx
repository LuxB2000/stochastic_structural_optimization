
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
		BoundaryConditionsVectorType* bcv){
}

void ComputeElementForces(
		DisplacementVectorType* disp, 
		StiffnessMatrixType K,
		ForceVectorType *f,
		BoundaryConditionsVectorType* bcv){
}

