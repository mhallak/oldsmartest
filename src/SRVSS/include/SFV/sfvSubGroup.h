/*
 * sfvSubGroup.h
 *
 *  Created on: Jul 28, 2014
 *      Author: userws3
 */

#ifndef SFVSUBGROUP_H_
#define SFVSUBGROUP_H_

#include "SFDP/ScenarioFeatureGroup.h"
#include "SFDP/ScenarioFeature.h"
#include <vector>
#include <string>
#include <tinyxml.h>
#include "SFV/SFV.h"

class SFV;
class sfvSubGroup
{
	private :
		ScenarioFeatureGroupType my_type;
		SFV * my_parent_SFV;


	public:

		inline sfvSubGroup(ScenarioFeatureGroupType type, SFV * parent_SFV)
			{
			my_type = type;
			my_parent_SFV = parent_SFV;
			}

		inline ScenarioFeatureGroupType get_Type()
			{return(my_type);}

		inline SFV * get_ParentSFV()
			{return (my_parent_SFV); }


		inline virtual ~sfvSubGroup() {};

		inline virtual bool roll() {return(false);};

		inline virtual TiXmlElement * ToXmlElement(int id) {return(0);};

//		TiXmlElement *toXMLElement();

};

#endif /* SFVSUBGROUP_H_ */
