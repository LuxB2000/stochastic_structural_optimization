#include "TrussStructureBuilder.h"

TrussStructureBuilder::TrussStructureBuilder()
{
	m_structure = new Structure();
}

TrussStructureBuilder::~TrussStructureBuilder()
{
	if(m_structure) delete m_structure;
}

void TrussStructureBuilder::Push6TrussFrame(
		VectorParameterType params){

}
