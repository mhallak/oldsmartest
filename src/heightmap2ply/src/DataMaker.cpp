/*
 * DataMaker.cpp
 *
 *  Created on: Feb 27, 2014
 *      Author: userws1
 */

#include "DataMaker.h"

DataMaker::DataMaker():
doc("data.xml")
{
	TiXmlDeclaration* decl = new TiXmlDeclaration( "1.0", "", "" );
	doc.LinkEndChild( decl );
	elem=new TiXmlElement("data");
	doc.LinkEndChild(elem);
}

void DataMaker::addData(std::string data,std::string value)
{
	TiXmlElement* xdata = new TiXmlElement(data);
	elem->LinkEndChild( xdata );
	xdata->LinkEndChild(new TiXmlText(value));
}

void DataMaker::output(std::string filename)
{
	doc.SaveFile(filename.c_str());
}

DataMaker::~DataMaker() {
	// TODO Auto-generated destructor stub
}

