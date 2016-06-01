
#include "PointManager.h"

PointManager::PointManager(){

	m_points = new PointMapType();

	std::clog << ">>[PointManager] initialization with " << m_points->size() << " points." << std::endl;
}

PointManager::~PointManager(){
	std::clog << ">> [PointManager] clean the Point data base." << std::endl;

	if( m_points ){
		for(PointMapType::iterator it=m_points->begin(); it!=m_points->end(); ++it){
			if(it->second){
				delete it->second;
			}
		}
		delete m_points;
	}
}

PointManager::IndexType PointManager::m_fromCoordToIndex( float x, float y, float z){
	return x + y * MAXDIMSPACE + z*MAXDIMSPACE*MAXDIMSPACE;
}

Point* PointManager::GetPoint(float x, float y, float z){
	PointMapType::iterator it;
	IndexType id = m_fromCoordToIndex(x,y,z);
	it = m_points->find(id);

	if(it == m_points->end()){
		// the Point doesn't exist, create it
		Point* new_p = new Point(x,y,z,id);
		m_points->insert(std::pair<IndexType,Point*>(id,new_p));
	}

	// return the point 
	return (*m_points)[id];
}


