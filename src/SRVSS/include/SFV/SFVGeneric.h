/*
 * SFVGeneric.h
 *
 *  Created on: Jun 8, 2014
 *      Author: userws1
 */

#ifndef SFVGENERIC_H_
#define SFVGENERIC_H_
#include "SFDP/ScenarioFeatureType.h"
#include "SFDP/ScenarioFeatureGroupType.h"
#include "DPGroup.h"
#include "DPObject.h"
#include "utils/ParsableInterface.h"
#include <vector>

class SFVComponent;
template<class T,ScenarioFeatureType::domain multiplicityFeature>
class SFVGeneric : public ParsableInterface{
public:
	SFVGeneric(DPGroup * dpGroup)
	{
		m_dpGroup=dpGroup;
		m_objects=new std::vector<T*>;
		if(dpGroup->m_objects->find(multiplicityFeature)!=dpGroup->m_objects->end())
			m_dp=dpGroup->m_objects->at(multiplicityFeature)->clone();
		was_rolled = false;
	}

	virtual ~SFVGeneric()
	{

	}


	/**
	 * provides a self calculation method for a generic object/set
	 * @param sfvComp the containing object, used for checking the validity of the calculated result
	 * @return true if the calculation is valid after 3 tries
	 **/
	bool calc(SFVComponent * sfvComp)
	{
		bool ans=false;

	//	std::cout << " ###### rolling " << m_dpGroup->m_groupType << std::endl;
		for(int roll_atemp=1;  roll_atemp<=10 && !ans ;  roll_atemp++)
		{
			m_dp->calc();
			ans =true;
			std::cout << " #### rolling " << m_dpGroup->m_groupType << " attempt # " << roll_atemp << " with " << m_dp->getResult() << " sub features groups " << std::endl;
			for(int i=0; i<m_dp->getResult() && ans; i++)
			{
				T *obj=new T(m_dpGroup);
				obj->setId(i);
				m_objects->push_back(obj);

				ans=obj->calc(sfvComp);
				was_rolled = true;
			}
			if (! ans) // the rolling failed probably because Rules violation and shall be performed again from the beginning
			{
				m_objects=new std::vector<T*>(); // the the current rolled values are deleted
			}
			std::cout << " #### rolling " << m_dpGroup->m_groupType << " attempt # " << roll_atemp << " with " << m_dp->getResult() << " sub features groups " << "success = " << ans << std::endl;

		}
		return ans;
	}

	std::vector<T*>* m_objects;
	DPGroup* m_dpGroup;
	DPObject *m_dp;
	bool was_rolled;


	TiXmlElement *toXMLElement()
	{
		std::stringstream ss;
		TiXmlElement * object= new TiXmlElement("Generic");
		object->SetAttribute("type",m_dpGroup->m_groupType.str());
		object->SetAttribute("name",m_dpGroup->m_name);

		for(auto tr: *m_objects)
		{
			object->LinkEndChild(tr->toXMLElement());
		}
		return object;
	}

	void fromXMLElement(TiXmlElement * xmlElement)
	{
		TiXmlNode* pChild;
		TiXmlAttribute* pAttrib;

		// FIX THIS : for now the object will generate its own DP objects
		m_dp=new DPObject(0);
		m_dpGroup=new DPGroup("temp",ScenarioFeatureGroupType::unknown_feature_group,0);
		/////////////////////////////////////////////////////////////

		for ( pAttrib = xmlElement->ToElement()->FirstAttribute(); pAttrib != 0; pAttrib = pAttrib->Next())
		{
			if(pAttrib->NameTStr().compare("type")==0)
			{
				m_dpGroup->m_groupType=ScenarioFeatureGroupType::parseString(pAttrib->Value());
			}
			if(pAttrib->NameTStr().compare("name")==0)
			{
				m_dpGroup->m_name=pAttrib->ValueStr();
			}
		}

		for ( pChild = xmlElement->FirstChild(); pChild != 0; pChild = pChild->NextSibling())
		{
			if(pChild->Type()==XML_ELEMENT){
				T *obj=new T(m_dpGroup);
				obj->fromXMLElement(pChild->ToElement());
				m_objects->push_back(obj);
			}
		}

		m_dp->setResult(m_objects->size());
	}

};
#endif /* SFVGENERIC_H_ */
