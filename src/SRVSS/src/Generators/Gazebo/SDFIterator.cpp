/*
 * SDFHandler.cpp
 *
 *  Created on: Mar 27, 2014
 *      Author: userws1
 */

#include "Generators/Gazebo/SDFIterator.h"

SDFIterator::SDFIterator(std::string fileName)
{
	TiXmlDocument *doc=new TiXmlDocument(fileName);
	if (!doc->LoadFile())
	{
		std::string error("Failed to load file \"");
		error+=fileName;
		error+="\"\n";
		throw error;
	}
	m_pointer=doc->FirstChildElement();
}

SDFIterator::~SDFIterator() {
	// TODO Auto-generated destructor stub
}

std::string SDFIterator::getCurrentPointType()
{
	return m_pointer->ValueStr();
}

void SDFIterator::getCurrentPointAttributes(std::vector<std::pair<std::string,std::string> > &vec)
{
	TiXmlAttribute* pAttrib;
	for ( pAttrib = m_pointer->FirstAttribute(); pAttrib != 0; pAttrib = pAttrib->Next())
	{
		vec.push_back(std::pair<std::string,std::string>(pAttrib->NameTStr(),pAttrib->ValueStr()));
	}
}

TiXmlElement* findByTypeAndAttributeHelper(TiXmlElement* curr,std::string type,std::string attributeName,std::string attributeValue)
{
	if(curr==0)
		return 0;
	if(curr->ValueStr().compare(type)==0){
		if(attributeName.size()!=0)
		{
			for (TiXmlAttribute* pAttrib = curr->FirstAttribute(); pAttrib != 0; pAttrib = pAttrib->Next())
			{
				if(attributeName.compare(pAttrib->NameTStr())==0 && attributeValue.compare(pAttrib->ValueStr())==0)
					return curr;
			}
		}else
		{
			return curr;
		}
	}
	TiXmlElement* res=findByTypeAndAttributeHelper(curr->FirstChildElement(),type,attributeName,attributeValue);
	if(res!=0)
	{
		return res;
	}
	return findByTypeAndAttributeHelper(curr->NextSiblingElement(),type,attributeName,attributeValue);

}

bool SDFIterator::findByTypeAndAttributeInChildren(std::string type,std::string attributeName,std::string attributeValue)
{
	TiXmlElement * curr;
	/*for(curr=m_pointer->FirstChildElement()->ToElement();curr!=0;curr=curr->NextSibling())
	{
		if(curr->ValueStr().compare(type)==0){
			if(attributeName.size()!=0)
			{
				for (TiXmlAttribute* pAttrib = curr->FirstAttribute(); pAttrib != 0; pAttrib = pAttrib->Next())
				{
					if(attributeName.compare(pAttrib->NameTStr())==0 && attributeValue.compare(pAttrib->ValueStr())==0)
					{
						m_pointer=curr;
						return true;
					}
				}
			}else
			{
				m_pointer=curr;
				return true;
			}
		}
	}*/
	false;
}

bool SDFIterator::findByTypeAndAttribute(std::string type,std::string attributeName,std::string attributeValue)
{
	TiXmlDocument * tempDoc=m_pointer->GetDocument();
	TiXmlElement * temp=findByTypeAndAttributeHelper(tempDoc->FirstChildElement(),type,attributeName,attributeValue);
	if(temp!=0)
	{
		m_pointer=temp;
		return true;
	}
	return false;
}

bool SDFIterator::moveToParent()
{
	TiXmlNode * temp=m_pointer->Parent();
	if(temp!=0 && temp->Type()==XML_ELEMENT)
	{
		m_pointer=temp->ToElement();
		return true;
	}
	return false;
}
bool SDFIterator::moveToNext()
{
	TiXmlNode * temp=m_pointer->NextSibling();
	if(temp!=0 && temp->Type()==XML_ELEMENT)
	{
		m_pointer=temp->ToElement();
		return true;
	}
	return false;
}


bool SDFIterator::moveToChild()
{
	TiXmlNode * temp=m_pointer->FirstChild();
	if(temp!=0 && temp->Type()==XML_ELEMENT)
	{
		m_pointer=temp->ToElement();
		return true;
	}
	return false;
}

bool SDFIterator::moveToNextOfType(std::string type)
{

}
