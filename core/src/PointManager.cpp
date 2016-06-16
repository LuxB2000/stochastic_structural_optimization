
#include "PointManager.h"

PointManager::PointManager(){

	m_points = new PointMapType();
	m_connexions = new ConnexionMapType();

	std::clog << ">>[PointManager] Point data initialized with " << m_points->size() << " points, Connexions data inialized with " << m_connexions->size() << "." << std::endl;
}

PointManager::~PointManager(){
	std::clog << ">> [PointManager] clean the Point data base (containing " << m_points->size() <<" elements) and the Connexions data base (containing " << m_connexions->size() << ")." << std::endl;

	if( m_points ){
		for(PointMapType::iterator it=m_points->begin(); it!=m_points->end(); ++it){
			if(it->second){
				delete it->second;
			}
		}
		delete m_points;
	}

	if(m_connexions){
		for(ConnexionMapType::iterator it=m_connexions->begin(); it!=m_connexions->end(); ++it){
			if(it->second){
				delete it->second; // delete a vector of pointer
			}
		}
		delete m_connexions;
	}

}

PointManager::IndexType PointManager::m_fromCoordToIndex( float x, float y, float z){
		IndexType id =  x + y * MAXDIMSPACE + z*MAXDIMSPACE*MAXDIMSPACE;
	// std::cout << ">> coord:["<<x<<","<<y<<","<<z<<"] index: " << id << std::endl;
	return id;
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

void PointManager::SetConnexion(Point* a, Point* b){
	ConnexionMapType::iterator pos_a,pos_b;
	pos_a = m_connexions->find(a->index);
	// the point hasn't had any connexion so far, create the vector
	if(pos_a == m_connexions->end()){
		m_connexions->insert(std::pair<IndexType,IndexVectorType*>(a->index,new IndexVectorType()) );
	}
	pos_b = m_connexions->find(b->index);
	if(pos_b == m_connexions->end()){
		m_connexions->insert(std::pair<IndexType,IndexVectorType*>(b->index,new IndexVectorType()) );
	}
	
	// add two connexions: in a to b and in b to a. 
	m_connexions->at(a->index)->push_back(b->index);
	m_connexions->at(b->index)->push_back(a->index);
}

const PointManager::PointVectorType PointManager::GetConnexions(Point* a){
	PointVectorType v = PointVectorType();
	int i=0, l=m_connexions->at(a->index)->size();
	for( i=0; i<l; i++){
		v.push_back( m_points->at(m_connexions->at(a->index)->at(i)) );
	}
	return v;
}
