/*
 * ResourceHandler.h
 *
 *  Created on: Feb 24, 2014
 *      Author: userws1
 */

#ifndef RESOURCEHANDLER_H_
#define RESOURCEHANDLER_H_
#include <string>
#include <map>

class ResourceHandler {

private:

	std::map <std::string, std::map<int,std::string>*>* m_resourceMap;
	std::string m_modelsPath;
	std::string m_platformPath;
	std::string m_platformModel;
	std::string m_platformName;
	std::string getResource(std::string name,int id);
    // Private Constructor
	ResourceHandler();
	virtual ~ResourceHandler();
    // Stop the compiler generating methods of copy the object
	ResourceHandler(ResourceHandler const& copy);            // Not Implemented
	ResourceHandler& operator=(ResourceHandler const& copy); // Not Implemented

public:
    static ResourceHandler& getInstance()
    {
        static ResourceHandler instance;
        return instance;
    }

    std::string getTerrainById(int id);
    std::string getObjectById(int id);
    std::string getLightById(int id);
	const std::string& getModelsPath() const;
	const std::string& getPlatformPath() const;
	const std::string& getPlatformModel() const;
	const std::string& getPlatformName() const;
};

#endif /* RESOURCEHANDLER_H_ */



