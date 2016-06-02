/*
 * =====================================================================================
 *
 *       Filename:  TrussStructureBuilder.h
 *
 *    Description:  A building structure builder, contains all the global
 *			information to construct the building.
 *
 *        Version:  1.0
 *        Created:  01/06/16 21:48:12
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jerome Plumat (JP)
 *
 * =====================================================================================
 */

#ifndef sso_TRUSSSTRUCTUREBUILDER_H
#define sso_TRUSSSTRUCTUREBUILDER_H

#include <vector>

#include "Structure.h"

class TrussStructureBuilder{
public:
	typedef std::vector<float> VectorParameterType;

	TrussStructureBuilder();
	~TrussStructureBuilder();

	// create a frame and add it to the building. The new frame will be added 
	// at the `end` of the building. The `end` is defined as far as possible of
	// the origin.
	// The first frame will be set at the origin.
	void Push6TrussFrame(VectorParameterType params);

	// getter
	Structure* GetStructure(){ return m_structure; }

private:
	Structure* m_structure;
};

#endif
