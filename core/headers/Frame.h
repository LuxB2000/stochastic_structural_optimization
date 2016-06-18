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

protected:
	Point* m_origin;
	FrameParametersVectorType* m_truss_params;

};

class TrussFrame : public Frame{
public:
	TrussFrame();
	~TrussFrame();
protected:
	typedef std::vector<AbstractTruss*> TrussVector;
	TrussVector* m_trusses;
};

/*
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
 */
class Simple5TrussFrame : public TrussFrame{
public:
	Simple5TrussFrame();
	Simple5TrussFrame(Point* origin, FrameParametersVectorType v, Material m);
	Simple5TrussFrame(Point* origin, float lv1, float lv21, float lv22, float lh22, float lv3, float lh3, float section, Material m );
	~Simple5TrussFrame();
private:
	typedef std::vector<AbstractTruss*> TrussesVectorType;
	void m_BuildFrame();
	Material m_material;
	static const unsigned int m_numberOfInputsParams = 7;
};

#endif

