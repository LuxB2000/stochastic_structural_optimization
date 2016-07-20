#include "TrussFrame.h"

TrussFrame::TrussFrame(){
	m_trusses = NULL;
}

TrussFrame::~TrussFrame(){
	if( m_trusses ){
		unsigned int l = m_trusses->size();
		for(unsigned int i=0; i<l; i++){
			delete m_trusses->at(i);
		}
	}
}


