
#ifndef sso_TRUSSSTRUCTUREBUILDER_H
#define sso_TRUSSSTRUCTUREBUILDER_H

#include <vector>

class TrussStructureBuilder{
public:
	typedef std::vector<float> VectorParameterType;

	TrussStructureBuilder();
	~TrussStructureBuilder();

	// building the structure
	void Build6TrussFrame(VectorParameterType params);

	//TODO: Push6TrussesFrame // add a frame at the `end` of the building
	//TODO: Structure* GetStructure();

private:
	//TODO: m_structure;
};

#endif
