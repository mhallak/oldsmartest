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

#include <stdlib.h>

GazeboPlatformGenerator::GazeboPlatformGenerator() {
	// TODO Auto-generated constructor stub

}

GazeboPlatformGenerator::~GazeboPlatformGenerator() {
	// TODO Auto-generated destructor stub
}

int findElementWithAttribute(sdf::ElementPtr *link, sdf::ElementPtr modelPtr,std::string elementType,std::string attributeType,std::string attributeName)
{
	sdf::ElementPtr res;
	for (res=modelPtr->GetElement(elementType) ; res /*->GetNextElement(elementType)*/ ; res=res->GetNextElement(elementType) )
	{
		if(res->HasAttribute(attributeType))
		{
			if(res->GetAttribute(attributeType)->GetAsString()==attributeName)
			{
			    *link = res;
				return 1;
			}
		}
	}
	return 0;
}



void GazeboPlatformGenerator::generatePlatform(SFVComponent * sfvcomp,std::string filename, std::string nominal_platform_model_url, std::string scenario_models_folder_url)
{
	sdf::SDFPtr sdfptr(new sdf::SDF());
	init(sdfptr);
	sdf::addURIPath("model://", scenario_models_folder_url );
	sdf::readFile(nominal_platform_model_url,sdfptr);

	sdf::ElementPtr modelPtr=sdfptr->root->GetElement("model");
	sdf::ElementPtr link;


	// set mass links
	for(SFVMassLink * mass_link_it : *(sfvcomp->getMassLinks()) )
	{
	if(findElementWithAttribute( &link, modelPtr,"link","name",mass_link_it->getLinkName()))
		{

			sdf::ElementPtr inertial=link->GetElement("inertial");
			sdf::ElementPtr mass=inertial->GetElement("mass");
			sdf::ElementPtr inertia=inertial->GetElement("inertia");
			sdf::ElementPtr inertiaxx=inertia->GetElement("ixx");
			sdf::ElementPtr inertiayy=inertia->GetElement("iyy");
			sdf::ElementPtr inertiazz=inertia->GetElement("izz");
			sdf::ElementPtr pose=link->GetElement("pose");

			sdf::Pose new_pose;
			pose->GetValue()->Get(new_pose);
			new_pose.pos.x += mass_link_it->getLocationXDeviation();
			new_pose.pos.y += mass_link_it->getLocationYDeviation();
			new_pose.pos.z += mass_link_it->getLocationZDeviation();
			sdf::Vector3 quad=new_pose.rot.GetAsEuler();
			quad.x += mass_link_it->getLocationRollDeviation();
			quad.y += mass_link_it->getLocationPitchDeviation();
			quad.z += mass_link_it->getLocationYawDeviation();
			new_pose.rot.SetFromEuler(quad);
			pose->Set(new_pose);


			double new_mass = mass->Get<double>() * mass_link_it->getMassDeviation();
			mass->Set(new_mass);

			double new_Ixx = inertiaxx->Get<double>() * mass_link_it->getInertiaDeviationIxxComponent();
			inertiaxx->Set(new_Ixx);

			double new_Iyy = inertiayy->Get<double>() * mass_link_it->getInertiaDeviationIyyComponent();
			inertiayy->Set(new_Iyy);

			double new_Izz = inertiazz->Get<double>() * mass_link_it->getInertiaDeviationIzzComponent();
			inertiazz->Set(new_Izz);
		}
		else
		{
			std::cout << mass_link_it->getLinkName() << " mass link not found in sdf" << std::endl;
		}
	}

	// set mass friction links
	for(SFVFrictionLink * friction_link_it : *(sfvcomp->getFrictionLinks()) )
	{
		if(findElementWithAttribute( &link, modelPtr,"link","name",friction_link_it->getLinkName()))
		{
			sdf::ElementPtr collision=link->GetElement("collision");
			sdf::ElementPtr surface=collision->GetElement("surface");
			sdf::ElementPtr friction=surface->GetElement("friction");
			sdf::ElementPtr ode=friction->GetElement("ode");
			sdf::ElementPtr mu=ode->GetElement("mu");
			sdf::ElementPtr mu2=ode->GetElement("mu2");

			double new_mu = mu->Get<double>() * friction_link_it->getFrictionDeviation();
			mu->Set<double>(new_mu);

			double new_mu2 = mu2->Get<double>() * friction_link_it->getFrictionDeviation();
			mu2->Set<double>(new_mu2);
		}
		else
		{
			std::cout << friction_link_it->getLinkName() << " friction link not found in sdf" << std::endl;
		}
	}

	// set mass sensors links
  	for(SFVSensorLink * sensor_link_it : *(sfvcomp->getSensorLinks()) )
	{
  		if(findElementWithAttribute( &link, modelPtr,"link","name",sensor_link_it->getLinkName()))
		{
			sdf::ElementPtr pose=link->GetElement("pose");

			sdf::Pose new_pose;
			pose->GetValue()->Get(new_pose);
			new_pose.pos.x += sensor_link_it->getLocationXDeviation();
			new_pose.pos.y += sensor_link_it->getLocationYDeviation();
			new_pose.pos.z += sensor_link_it->getLocationZDeviation();

			sdf::Vector3 quad=new_pose.rot.GetAsEuler();
			quad.x += sensor_link_it->getLocationRollDeviation();
			quad.y += sensor_link_it->getLocationPitchDeviation();
			quad.z += sensor_link_it->getLocationYawDeviation();
			new_pose.rot.SetFromEuler(quad);

			pose->GetValue()->Set(new_pose);
		}
		else
		{
			std::cout << sensor_link_it->getLinkName() << " sensor link not found in sdf" << std::endl;
		}
	}
	sdfptr->Write(filename);
}


void CopyModelConfigAndMashes(std::string model_source_folder_url, std::string destenation_model_folder_url)
{
		std::string create_model_folder_command = "mkdir -p " + destenation_model_folder_url;
		//std::cout << " create_model_folder_command = " << create_model_folder_command << std::endl;
		system(create_model_folder_command.c_str());

		std::string copy_meshes_folder_command = "cp -r " + model_source_folder_url + "/meshes " + destenation_model_folder_url;
		//std::cout << " copy_meshes_folder_command = " << copy_meshes_folder_command << std::endl;
		system(copy_meshes_folder_command.c_str());

		std::string copy_config_file_command = "cp -r " + model_source_folder_url + "/model.config " + destenation_model_folder_url;
		//std::cout << " copy_meshes_folder_command = " << copy_config_file_command << std::endl;
		system(copy_config_file_command.c_str());
}


void GazeboPlatformGenerator::generate(SFVComponent * sfvComp, std::string scenario_folder_url, std::string resource_file_url)
{

	std::string nominal_models_folder_url = ResourceHandler::getInstance(resource_file_url).getSysModelsPath();
	std::string nominal_platform_model_folder_url = nominal_models_folder_url + "/" +  ResourceHandler::getInstance(resource_file_url).getPlatformName() ;
	std::string nominal_platform_model_url = nominal_platform_model_folder_url + "/model.sdf";

	std::string scenario_models_folder_url = scenario_folder_url + "/scenarioSystemModels" ;
	std::string scenario_platform_model_folder_url = scenario_models_folder_url + "/" + ResourceHandler::getInstance(resource_file_url).getPlatformName();
	std::string scenario_platform_model_url = scenario_platform_model_folder_url + "/model.sdf";

	CopyModelConfigAndMashes(nominal_platform_model_folder_url, scenario_platform_model_folder_url);


	std::string nominal_gpu_sick_model_folder_url = nominal_models_folder_url + "/" + "gpu_sick";
	std::string copy_gpu_sick_folder_command = "cp -r " + nominal_gpu_sick_model_folder_url + " " + scenario_models_folder_url;
	//std::cout << " copy_gpu_sick_folder_command = " << copy_gpu_sick_folder_command << std::endl;
	system(copy_gpu_sick_folder_command.c_str());

	std::string nominal_GPS_INS_model_folder_url = nominal_models_folder_url + "/" + "GPS_INS";
	std::string copy_GPS_INS_folder_command = "cp -r " + nominal_GPS_INS_model_folder_url + " " + scenario_models_folder_url;
	//std::cout << " copy_GPS_INS_folder_command = " << copy_GPS_INS_folder_command << std::endl;
	system(copy_GPS_INS_folder_command.c_str());


	generatePlatform(sfvComp, scenario_platform_model_url ,nominal_platform_model_url, scenario_models_folder_url);





	std::cout << " Producing " << scenario_platform_model_url << std::endl;
}



