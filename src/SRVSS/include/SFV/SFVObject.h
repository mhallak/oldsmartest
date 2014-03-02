/*
 * SFVObject.h
 *
 *  Created on: Feb 24, 2014
 *      Author: userws1
 */

#ifndef SFVOBJECT_H_
#define SFVOBJECT_H_

class SFVObject {
public:
	int m_Id;
	int m_Type;
	double m_X;
	double m_Y;
	double m_Z;
	double m_Roll;
	double m_Pitch;
	double m_Yaw;
	double m_Scale;


	SFVObject();
	virtual ~SFVObject();

	double getPitch() const;
	void setPitch(double pitch);
	double getRoll() const;
	void setRoll(double roll);
	double getScale() const;
	void setScale(double scale);
	int getType() const;
	void setType(int type);
	double getX() const;
	void setX(double x);
	double getY() const;
	void setY(double y);
	double getYaw() const;
	void setYaw(double yaw);
	double getZ() const;
	void setZ(double z);
	int getId() const;
	void setId(int id);
};

#endif /* SFVOBJECT_H_ */
