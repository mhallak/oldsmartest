/*
 * SFVLight.h
 *
 *  Created on: Feb 24, 2014
 *      Author: userws1
 */

#ifndef SFVLIGHT_H_
#define SFVLIGHT_H_
#include "SFV/SFVInterface.h"
#include "utils/ParsableInterface.h"

class SFVLight : public SFVInterface , public ParsableInterface{

	int m_Id;
	int m_Type;
	double m_X;
	double m_Y;
	double m_Z;
	double m_DirectionX;
	double m_DirectionY;
	double m_Cone;
	double m_Range;
public:
	SFVLight();
	virtual ~SFVLight();
	void setRolledValue(RolledValue * value);
	TiXmlElement *toXMLElement();
	void fromXMLElement(TiXmlElement * node);

	double getCone() const;
	void setCone(double cone);
	double getDirectionX() const;
	void setDirectionX(double directionX);
	double getDirectionY() const;
	void setDirectionY(double directionY);
	int getId() const;
	void setId(int id);
	double getRange() const;
	void setRange(double range);
	int getType() const;
	void setType(int type);
	double getX() const;
	void setX(double x);
	double getY() const;
	void setY(double y);
	double getZ() const;
	void setZ(double z);
};

#endif /* SFVLIGHT_H_ */
