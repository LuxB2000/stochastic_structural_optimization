//
// Created by plumat on 20/04/16.
//

#include "../headers/StiffnessMatrixBuilder.h"


StiffnessMatrixBuilder::StiffnessMatrixBuilder() {
    m_kg = new StiffnessMatrixType();
}

StiffnessMatrixBuilder::~StiffnessMatrixBuilder() {
    if(m_kg) delete m_kg;
}

void StiffnessMatrixBuilder::Build(StiffnessMatrixType* kl) {

}

const StiffnessMatrixBuilder::StiffnessMatrixType StiffnessMatrixBuilder::GetStiffnessMatrix() {
    return StiffnessMatrixType(*m_kg);
}

StiffnessMatrixBuilder::StiffnessMatrixType *StiffnessMatrixBuilder::GetStiffnessMatrixPointer() {
    return m_kg;
}



