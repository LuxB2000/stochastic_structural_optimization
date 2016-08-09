/*
 * =====================================================================================
 *
 *       Filename:  Simple5TrussFrame.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  20/07/16 13:34:06
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jerome Plumat (JP)
 *
 * The structure of the SimpleTrussFrame
 * similar truss are identical: 1 & 5, 2 & 4
 * Truss 1 and 5 are SimpleTruss (1 param: length vertical)
 * Truss 2 and 4 are SimpleCornerTruss (3 params: 2 vectical dimension and 1 horizontal length)
 * Truss 3 is a TopCornerTruss  (2 params: vectical dimension and horizontal length)
 * Total params: 1 + 3 + 2
 *    3/\
 *    o  o
 * 2 /    \ 4
 *   |    |
 *   o    o
 * 1 |    | 5
 *   |    |
 * symetric frame
 * =====================================================================================
 */

#ifndef sso_SIMPLE5TRUSSFRAME_H
#define sso_SIMPLE5TRUSSFRAME_H

#include "TrussFrame.h"

class Simple5TrussFrame : public TrussFrame{
public:
	Simple5TrussFrame();
	Simple5TrussFrame(Point* origin, FrameParametersVectorType v, Material m);
	Simple5TrussFrame(Point* origin, float lv1, float lv21, float lv22, float lh22, float lv3, float lh3, float section, Material m );
	~Simple5TrussFrame();
	void SetElementForcesInGlobalCoordinates(ForceVectorType fext);
private:
	typedef std::vector<AbstractTruss*> TrussesVectorType;
	void m_BuildFrame();
	Material m_material;
	static const unsigned int m_numberOfInputsParams = 7;
};

#endif

