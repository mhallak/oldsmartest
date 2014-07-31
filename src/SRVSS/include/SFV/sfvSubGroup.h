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

class sfvSubGroup
{
	private :
		ScenarioFeatureGroupType my_type;


	public:

		inline sfvSubGroup(ScenarioFeatureGroupType type)
			{
			my_type = type;
			}


		inline ScenarioFeatureGroupType get_Type()
			{return(my_type);}


		inline virtual ~sfvSubGroup() {};

		inline virtual void roll() {};

//		TiXmlElement *toXMLElement();

};

#endif /* SFVSUBGROUP_H_ */
