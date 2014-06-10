/*
 * TerrainBoundsRule.h
 *
 *  Created on: Jun 2, 2014
 *      Author: userws1
 */

#ifndef TERRAINBOUNDSRULE_H_
#define TERRAINBOUNDSRULE_H_
#include "Rule.h"
class TerrainBoundsRule : public Rule
{
public:
	TerrainBoundsRule();
	virtual ~TerrainBoundsRule();
	bool isRuleValid(SFVComponent *comp);
};
#endif /* TERRAINBOUNDSRULE_H_ */
