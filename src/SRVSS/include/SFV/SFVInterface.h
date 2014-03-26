/*
 * SFVInterface.h
 *
 *  Created on: Mar 25, 2014
 *      Author: userws1
 */

#ifndef SFVINTERFACE_H_
#define SFVINTERFACE_H_
#include "utils/RolledValue.h"

class SFVInterface
{
public:
	inline virtual ~SFVInterface(){}
	virtual void setRolledValue(RolledValue * value)=0;
};


#endif /* SFVINTERFACE_H_ */
