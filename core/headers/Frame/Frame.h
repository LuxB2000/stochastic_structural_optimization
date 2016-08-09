/*
 * =====================================================================================
 *
 *       Filename:  Frame.h
 *
 *    Description:  A frame constituting the building
 *
 *        Version:  1.0
 *        Created:  02/06/16 12:59:22
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jerome Plumat (JP)
 *
 * =====================================================================================
 */

#ifndef sso_FRAME_H
#define sso_FRAME_H

#include "Types.h"
#include "Point.h"
#include "SimpleCornerTruss.h"
#include "SimpleTruss.h"

class Frame{
public:
	Frame();
	~Frame();
	FrameParametersVectorType* GetParameters(){
		return m_truss_params;
	}

	const StiffnessMatrixType GetStiffnessMatrix();
	StiffnessMatrixType* GetStiffnessMatrixPointer();

protected:
	Point* m_origin;
	FrameParametersVectorType* m_truss_params;
	double m_cross_section;
	Material m_material_type;
	StiffnessMatrixType m_stiffness; // in global coordinates

};

#endif

