/*
 * XMLParserPUGI.h
 *
 *  Created on: Sep 28, 2011
 *      Author: Dani
 */

#ifndef XMLPARSERPUGI_H_
#define XMLPARSERPUGI_H_
#include "pugixml/pugixml.hpp"
#include "CBaseEngine.h"
#include <string>
#include <vector>

class XMLParserPUGI
{
public:
	XMLParserPUGI(std::string);
	~XMLParserPUGI();

	bool 			Ready();

	// NodePath in linux dir format, "ROOTNODE/CHILDNODE/CHILDNODE#N"
	std::string		GetStringAttributeValue	(const std::string &NodePath, const std::string &Attribute, const std::string DefaultValue = ""); //Retorna un attribut en forma d'string
	int				GetIntAttributeValue	(const std::string &NodePath, const std::string &Attribute, const int DefaultValue = 0 ); //Retorna un attribut en forma de Int
	float			GetFloatAttributeValue	(const std::string &NodePath, const std::string &Attribute, const float DefaultValue = 0.0F ); //Retorna un atribut en forma de float
	bool			GetBoolAttributeValue	(const std::string &NodePath, const std::string &Attribute, const bool DefaultValue = false );


	uint			GetNodeNameCount		(const std::string &NodePath);	//Cuenta el numero de nodos hijos en la ruta NodePath -> ROOTNODE/CHILDNODE_A/CHILDNODE_b -> devuelve #N de posibles CHILDNODE_B dentro de CHILDONE_A

private:
	inline bool 	GetAttribute( const std::string &NodePath, const std::string &Attribute, pugi::xml_attribute &xmlAttrib );
	inline void 	GetNodes(std::string NodePath, std::vector< std::pair<std::string,int> > &AllNodes);

	pugi::xml_parse_result 	m_resultat;
	pugi::xml_document 		m_doc;

};

#endif /* XMLPARSERPUGI_H_ */
