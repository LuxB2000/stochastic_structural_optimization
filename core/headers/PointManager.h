/*
 * =====================================================================================
 *
 *       Filename:  PointManager.h
 *
 *    Description:  Singleton dealing with Point, 
 *			- given a coordinate it returns a Point*
 *			- records the links between points
 *
 *        Version:  1.0
 *        Created:  16/06/16 22:03:17
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jerome Plumat (JP)
 *
 * =====================================================================================
 */

#ifndef sso_POINTMANAGER_H
#define sso_SIMPLECORNERTRUSS_H

#include <iostream>
#include <map>
#include <vector>
#include "Point.h"

//TODO: move some where else
// expected coord [0,10[ with 1E-3 precision => 1E3 max points in one direction, lets MAXDIMSPACE=10*max points
const Point::IndexType MAXDIMSPACE=1000.000;

class PointManager{

public:

	// typedefs
	typedef std::vector<Point*> PointVectorType;

	// Singleton instance
	static PointManager& GetInstance(){
		static PointManager  instance; // Guaranteed to be destroyed.
																	// Instantiated on first use.
		return instance;
	}


	long GetNumberOfPoints(){ return m_points->size(); }

	Point* GetPoint(float x, float y, float z);


	void SetConnexion(Point* a, Point* b);
	void RemoveConnexion(Point* a, Point* b);
	const PointVectorType GetConnexions(Point* a);

private:
	PointManager();
	~PointManager();

	// typedef
	typedef Point::IndexType IndexType;
	typedef std::vector<IndexType> IndexVectorType;
	typedef std::map<IndexType,IndexVectorType*> ConnexionMapType;
	typedef std::map<IndexType,Point*> PointMapType;

	IndexType m_fromCoordToIndex(float x, float y, float z);

	PointMapType * m_points;
	ConnexionMapType* m_connexions;
	



};

#endif
