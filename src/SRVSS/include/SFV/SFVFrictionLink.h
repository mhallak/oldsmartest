/*
 * SFVFrictionLink.h
 *
 *  Created on: Mar 25, 2014
 *      Author: userws1
 */

#ifndef SFVFRICTIONLINK_H_
#define SFVFRICTIONLINK_H_
#include "SFV/SFVInterface.h"
#include "utils/ParsableInterface.h"

class SFVFrictionLink : public SFVInterface , public ParsableInterface{
	int m_id;
	std::string m_link_name;
	double m_frictionDeviation;
public:
	SFVFrictionLink();
	virtual ~SFVFrictionLink();
	void setRolledValue(RolledValue * value);
	TiXmlElement *toXMLElement();
	void fromXMLElement(TiXmlElement * node);

	double getFrictionDeviation() const;
	void setFrictionDeviation(double frictionDeviation);

	int getId() const;
	void setId(int id);
	const std::string& getLinkName() const;
	void setLinkName(const std::string& linkName);
};

#endif /* SFVFRICTIONLINK_H_ */
