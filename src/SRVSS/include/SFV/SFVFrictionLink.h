/*
 * SFVFrictionLink.h
 *
 *  Created on: Mar 25, 2014
 *      Author: userws1
 */

#ifndef SFVFRICTIONLINK_H_
#define SFVFRICTIONLINK_H_
#include "utils/ParsableInterface.h"
#include "SFVBase.h"
class SFVFrictionLink : public SFVBase
{

public:
	void setStructure();

	SFVFrictionLink(DPGroup * dpGroup);
	virtual ~SFVFrictionLink();

	double getFrictionDeviation() const;
	void setFrictionDeviation(double frictionDeviation);

	int getId() const;
	void setId(int id);
	const std::string& getLinkName() const;
	void setLinkName(const std::string& linkName);
};

#endif /* SFVFRICTIONLINK_H_ */
