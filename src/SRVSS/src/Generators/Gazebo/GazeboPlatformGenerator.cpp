/*
 * GazeboPlatformGenerator.cpp
 *
 *  Created on: Mar 27, 2014
 *      Author: userws1
 */

#include <Generators/Gazebo/GazeboPlatformGenerator.h>
#include <SFV/SFVMassLink.h>
#include <sdf/SDFImpl.hh>
#include <sdf/parser.hh>
#include <Resource/ResourceHandler.h>
#include <sdf/sdf.hh>
#include <boost/tokenizer.hpp>
GazeboPlatformGenerator::GazeboPlatformGenerator() {
	// TODO Auto-generated constructor stub

}

GazeboPlatformGenerator::~GazeboPlatformGenerator() {
	// TODO Auto-generated destructor stub
}

sdf::ElementPtr findElementWithAttribute(sdf::ElementPtr modelPtr,std::string elementType,std::string attributeType,std::string attributeName)
{
	sdf::ElementPtr res=modelPtr->GetElement(elementType);
	while(!res && !(res->GetName().empty()))
	{
		if(res->HasAttribute(attributeType))
		{
			if(res->GetAttribute(attributeType)->GetAsString()==attributeName)
			{
				return res;
			}
		}
		res=res->GetNextElement(elementType);
	}
	return res;
}

void GazeboPlatformGenerator::generatePlatform(SFVComponent * sfvcomp,std::string filename, std::string resources_file_path)
{
	sdf::SDFPtr sdfptr(new sdf::SDF());
	init(sdfptr);
	sdf::addURIPath("model://", ResourceHandler::getInstance(resources_file_path).getModelsPath());
	sdf::readFile(ResourceHandler::getInstance(resources_file_path).getPlatformPath(),sdfptr);
	sdf::ElementPtr modelPtr=sdfptr->root->GetElement("model");
	sdf::ElementPtr link;
	// set mass links
	for(std::vector<SFVMassLink*>::iterator it=sfvcomp->m_massLinks->begin();it!=sfvcomp->m_massLinks->end();++it)
	{
		link=findElementWithAttribute(modelPtr,"link","name",(*it)->getLinkName());
		if(!link->GetName().empty())
		{
			sdf::ElementPtr inertial=link->GetElement("inertial");
			sdf::ElementPtr mass=inertial->GetElement("mass");
			sdf::ElementPtr inertia=inertial->GetElement("inertia");
			sdf::ElementPtr inertiaxx=inertia->GetElement("ixx");
			sdf::ElementPtr inertiayy=inertia->GetElement("iyy");
			sdf::ElementPtr inertiazz=inertia->GetElement("izz");
			sdf::ElementPtr pose=link->GetElement("pose");

			sdf::Pose poseParam;
			pose->GetValue()->GetDefault(poseParam);
			poseParam.pos.x+=(*it)->getLocationXDeviation();
			poseParam.pos.y+=(*it)->getLocationYDeviation();
			poseParam.pos.z+=(*it)->getLocationZDeviation();

			sdf::Vector3 quad=poseParam.rot.GetAsEuler();

			quad.x+=(*it)->getLocationRollDeviation();
			quad.y+=(*it)->getLocationPitchDeviation();
			quad.z+=(*it)->getLocationYawDeviation();
			poseParam.rot.SetFromEuler(quad);
			pose->GetValue()->Set(poseParam);


			mass->GetValue()->Set((*it)->getMass());
			inertiaxx->GetValue()->Set((*it)->getInertiaIxxComponent());
			inertiayy->GetValue()->Set((*it)->getInertiaIyyComponent());
			inertiazz->GetValue()->Set((*it)->getInertiaIzzComponent());
		}else
		{
			throw std::string((*it)->getLinkName() +" mass link not found in sdf");
		}
	}

	for(std::vector<SFVFrictionLink*>::iterator it=sfvcomp->m_frictionLinks->begin();it!=sfvcomp->m_frictionLinks->end();++it)
		{
			link=findElementWithAttribute(modelPtr,"link","name",(*it)->getLinkName());
			if(!link->GetName().empty())
			{
				sdf::ElementPtr collision=link->GetElement("collision");
				sdf::ElementPtr surface=collision->GetElement("surface");
				sdf::ElementPtr friction=surface->GetElement("friction");
				sdf::ElementPtr ode=friction->GetElement("ode");
				sdf::ElementPtr mu=ode->GetElement("mu");
				sdf::ElementPtr mu2=ode->GetElement("mu2");

				mu->Set<double>(mu->Get<double>()+(*it)->getFrictionDeviation());
				mu2->Set<double>(mu2->Get<double>()+(*it)->getFrictionDeviation());

			}else
			{
				throw std::string((*it)->getLinkName() +" friction link not found in sdf");
			}
		}
	for(std::vector<SFVSensorLink*>::iterator it=sfvcomp->m_sensorLinks->begin();it!=sfvcomp->m_sensorLinks->end();++it)
		{
			link=findElementWithAttribute(modelPtr,"link","name",(*it)->getLinkName());
			if(!link->GetName().empty())
			{
				sdf::ElementPtr pose=link->GetElement("pose");
				sdf::Pose poseParam;
				pose->GetValue()->GetDefault(poseParam);
				poseParam.pos.x+=(*it)->getLocationXDeviation();
				poseParam.pos.y+=(*it)->getLocationYDeviation();
				poseParam.pos.z+=(*it)->getLocationZDeviation();

				sdf::Vector3 quad=poseParam.rot.GetAsEuler();

				quad.x+=(*it)->getLocationRollDeviation();
				quad.y+=(*it)->getLocationPitchDeviation();
				quad.z+=(*it)->getLocationYawDeviation();
				poseParam.rot.SetFromEuler(quad);
				pose->GetValue()->Set(poseParam);

			}else
			{
				throw std::string((*it)->getLinkName() +" sensor link not found in sdf");
			}
		}

	sdfptr->Write(filename);
}


void GazeboPlatformGenerator::generate(SFVComponent * sfvcomp)
{

}


