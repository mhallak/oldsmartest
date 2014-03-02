/*
 * NumberSampler.cpp
 *
 *  Created on: Feb 5, 2014
 *      Author: userws1
 */

#include <utils/NumberSampler.h>
#include <boost/random/linear_congruential.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/variate_generator.hpp>
#include <boost/generator_iterator.hpp>

NumberSampler::NumberSampler() {
	seed= 0;
}

NumberSampler::~NumberSampler() {
}


int NumberSampler::uniformIntDistribution(int distParam1, int distParam2)
{
	int mini,maxi;
	if(distParam1>distParam2)
	{
		mini=distParam2;
		maxi=distParam1;
	}else{
		mini=distParam1;
		maxi=distParam2;
	}
	boost::uniform_int<> dist(mini,maxi);

	gen.seed((++seed) + time(NULL));
	boost::variate_generator<boost::mt19937&, boost::uniform_int<> > generator(gen, dist);
	return generator();
}

float NumberSampler::uniformRealDistribution(float distParam1, float distParam2)
{
	float mini,maxi;
	if(distParam1>distParam2)
	{
		mini=distParam2;
		maxi=distParam1;
	}else{
		mini=distParam1;
		maxi=distParam2;
	}
	boost::uniform_real<> dist(mini,maxi);
	gen.seed((++seed) + time(NULL));
	boost::variate_generator<boost::mt19937&, boost::uniform_real<> > generator(gen, dist);
	return generator();
}

