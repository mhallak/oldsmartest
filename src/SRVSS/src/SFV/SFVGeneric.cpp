/*
 * SFVGeneric.cpp
 *
 *  Created on: Jun 8, 2014
 *      Author: userws1
 */

#include "SFV/SFVGeneric.h"
/*
template<class T,ScenarioFeatureType::domain multiplicityFeature>
SFVGeneric<T,multiplicityFeature>::SFVGeneric(DPGroup * dpGroup){

	m_dpGroup=dpGroup;
	m_objects=new std::vector<T*>;
	m_dp=dpGroup->m_objects->at(multiplicityFeature)->clone();
}

template<class T,ScenarioFeatureType::domain multiplicityFeature>
bool SFVGeneric<T,multiplicityFeature>::calc(SFVComponent * sfvComp)
{
	bool ans=false;
	for(int i=0;i<3 && !ans;i++){
		m_dp->calc();
		ans =true;
		for(int i=0; i<m_dp->getResult() && ans;i++)
		{
			T *obj=new T(m_dpGroup);
			obj->setId(i);
			m_objects->push_back(obj);
			ans=obj->calc(sfvComp);
		}
		if(!ans)
		{
			m_objects=new std::vector<T*>();
		}
	}
	return ans;
}

template<class T,ScenarioFeatureType::domain multiplicityFeature>
SFVGeneric<T,multiplicityFeature>::~SFVGeneric() {
	// TODO Auto-generated destructor stub
}

*/
