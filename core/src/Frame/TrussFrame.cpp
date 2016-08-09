#include "TrussFrame.h"

TrussFrame::TrussFrame(){
	m_trusses = NULL;
	m_elementForceLC = NULL;
}

TrussFrame::~TrussFrame(){
	if( m_trusses ){
		unsigned int l = m_trusses->size();
		for(unsigned int i=0; i<l; i++){
			delete m_trusses->at(i);
		}
	}
	if( m_elementForceLC ){
		//unsigned int l= m_elementForceLC->size(), i=0;
		//for(i=0; i<l; i++){
		//	if( m_elementForceLC->at(i) ) delete m_elementForceLC;
		//}
		delete m_elementForceLC;
	}
}


