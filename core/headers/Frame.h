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
 * A simple 3 trusses frame
 * Truss 1 and 3 are SimpleTruss (1 param: length)
 * Truss 2 is TopCornerTruss (2 params: x and y length)
 *
 */
class Simple3TrussFrame : public TrussFrame{
public: 
	Simple3TrussFrame();
	~Simple3TrussFrame();
};

/*
 * The structure of the SimpleTrussFrame
 * Truss 1 and 5 are SimpleTruss (1 param: length)
 * Truss 2 and 4 are SimpleCornerTruss (3 params: 2 lengths and 1 angle)
 * Truss 3 is a TopCornerTruss (2 params: 1 length and 1 angle)
 * Total params: 2*(1+3+2)
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
	Simple5TrussFrame(Point oritin, FrameParametersVectorType v);
	Simple5TrussFrame(Point origin, float l1, float l2, float a2, float l3, float a3 );
	~Simple5TrussFrame();
private:
	void m_BuildFrame();
	static const unsigned int m_numberOfInputsParams = 5;
};

#endif

