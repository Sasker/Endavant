/*
 * XMLParserPUGI.h
 *
 *  Created on: Sep 28, 2011
 *      Author: Dani
 */

#ifndef XMLPARSERPUGI_H_
#define XMLPARSERPUGI_H_
#include "pugixml/pugixml.hpp"
#include <string>
#include <vector>
#include "Core/CBasicTypes.h"

class CXMLParserPUGI
{
public:
	CXMLParserPUGI(std::string);
	~CXMLParserPUGI();

	bool 			Ready();

	// NodePath in linux dir format, "ROOTNODE/CHILDNODE/CHILDNODE#N"
	std::string		GetStringAttributeValue	(const std::string &NodePath, const std::string &Attribute, const std::string DefaultValue = ""); //Retorna un attribut en forma d'string
	s32				GetIntAttributeValue	(const std::string &NodePath, const std::string &Attribute, const s32 DefaultValue = 0 ); //Retorna un attribut en forma de Int
	f32				GetFloatAttributeValue	(const std::string &NodePath, const std::string &Attribute, const f32 DefaultValue = 0.0F ); //Retorna un atribut en forma de float
	bool			GetBoolAttributeValue	(const std::string &NodePath, const std::string &Attribute, const bool DefaultValue = false );


	u32				GetNodeNameCount		(const std::string &NodePath);	//Cuenta el numero de nodos hijos en la ruta NodePath -> ROOTNODE/CHILDNODE_A/CHILDNODE_b -> devuelve #N de posibles CHILDNODE_B dentro de CHILDONE_A

private:
	inline bool 	GetAttribute( const std::string &NodePath, const std::string &Attribute, pugi::xml_attribute &xmlAttrib );
	inline void 	GetNodes(std::string NodePath, std::vector< std::pair<std::string,int> > &AllNodes);

	pugi::xml_parse_result 	m_resultat;
	pugi::xml_document 		m_doc;

};

#endif /* XMLPARSERPUGI_H_ */
