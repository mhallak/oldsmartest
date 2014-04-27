/*
 * SDFHandler.h
 *
 *  Created on: Mar 27, 2014
 *      Author: userws1
 */

#ifndef SDFHANDLER_H_
#define SDFHANDLER_H_

#include <utils/TinyXmlDef.h>
#include <vector>

class SDFIterator {
public:
	TiXmlElement* m_pointer;
	SDFIterator(std::string fileName);
	virtual ~SDFIterator();
	std::string getCurrentPointType();
	void getCurrentPointAttributes(std::vector<std::pair<std::string,std::string> > &vec);
	bool findByTypeAndAttribute(std::string type,std::string attributeName,std::string attributeValue);
	bool findByTypeAndAttributeInChildren(std::string type,std::string attributeName,std::string attributeValue);
	bool moveToParent();
	bool moveToNext();
	bool moveToChild();
	bool moveToNextOfType(std::string type);
};

#endif /* SDFHANDLER_H_ */
