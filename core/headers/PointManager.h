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
#include "Point.h"

//TODO: move some where else
// expected coord [0,10[ with 1E-3 precision => 1E4 max points in one direction, lets MAXDIMSPACE=10*max points
const Point::IndexType MAXDIMSPACE=100000.000;

class PointManager{

public:
	static PointManager& GetInstance(){
		static PointManager  instance; // Guaranteed to be destroyed.
													// Instantiated on first use.
		return instance;
	}

	int Test(){
		return 1;
	}

	long GetNumberOfPoints(){ return m_points->size(); }

	Point* GetPoint(float x, float y, float z);


	// TODO:
	// void SetConnexion(Point* a, Point* b);
	// void RemoveConnexion(Point* a, Point* b);
	// ConnexionVectorType* GetPointConnexion(Point a);
	// ConnexionVectorType* GetAllConnexion();

private:
	PointManager();
	~PointManager();

	typedef Point::IndexType IndexType;

	IndexType m_fromCoordToIndex(float x, float y, float z);

	typedef std::map<IndexType,Point*> PointMapType;
	PointMapType * m_points;



};

#endif
