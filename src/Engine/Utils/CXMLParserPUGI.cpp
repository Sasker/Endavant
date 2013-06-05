/*
 * XMLParserPUGI.cpp
 *
 *  Created on: Sep 28, 2011
 *      Author: Dani
 */

#include "CXMLParserPUGI.h"
#include "pugixml/pugixml.hpp"
#include "Core/CCoreEngine.h"
#include "Core/CLogManager.h"
#include "Utils/CConversions.h"

using namespace std;

CXMLParserPUGI::CXMLParserPUGI(string l_XMLFile)
{
	m_resultat = m_doc.load_file(l_XMLFile.c_str());
	if (!m_resultat)
	{
		CCoreEngine::Instance().GetLogManager().LogOutput( LOG_ERROR, LOGSUB_PARSER,"[ %s ] not found!",l_XMLFile.c_str());
	}
}

CXMLParserPUGI::~CXMLParserPUGI()
{
	m_doc.reset();
	m_resultat.status = pugi::status_file_not_found;
}

string CXMLParserPUGI::GetStringAttributeValue(const string &NodePath, const string &Attribute, const string DefaultValue)
{
	string retValue(DefaultValue);
	pugi::xml_attribute xmlAttrib;
	if ( GetAttribute( NodePath, Attribute, xmlAttrib))
	{
		retValue = xmlAttrib.value();
	}
	return retValue;
}

int CXMLParserPUGI::GetIntAttributeValue(const string &NodePath, const string &Attribute, const int DefaultValue)
{
	int retValue(DefaultValue);
	pugi::xml_attribute xmlAttrib;
	if ( GetAttribute( NodePath, Attribute, xmlAttrib))
	{
		retValue = xmlAttrib.as_int();
	}
	return retValue;
}

float CXMLParserPUGI::GetFloatAttributeValue(const string &NodePath, const string &Attribute, const float DefaultValue)
{
	float retValue(DefaultValue);
	pugi::xml_attribute xmlAttrib;
	if ( GetAttribute( NodePath, Attribute, xmlAttrib))
	{
		retValue = xmlAttrib.as_float();
	}
	return retValue;
}

bool CXMLParserPUGI::GetBoolAttributeValue(const string &NodePath, const string &Attribute, const bool DefaultValue)
{
	bool retValue(DefaultValue);
	pugi::xml_attribute xmlAttrib;
	if ( GetAttribute( NodePath, Attribute, xmlAttrib))
	{
		retValue = xmlAttrib.as_bool();
	}
	return retValue;
}

inline bool CXMLParserPUGI::GetAttribute(const string &NodePath, const string &Attribute, pugi::xml_attribute &xmlAttrib)
{
	vector< pair<string,int> > Nodes;
	GetNodes(NodePath, Nodes);
	if (Nodes.size() > 0)
	{
		//Siempre necesitamos como minimo el ROOTNODE
		vector< pair<string,int> >::iterator ItNode = Nodes.begin();
		pugi::xml_node xmlsubnode = m_doc.child( ItNode->first.c_str() );
		ItNode++;
		while ( ItNode != Nodes.end() )
		{
			//Recorremos todos los subnodos
			xmlsubnode = xmlsubnode.child( ItNode->first.c_str() );
			int count = 0;
			while (count < ItNode->second && xmlsubnode)
			{
				xmlsubnode = xmlsubnode.next_sibling( ItNode->first.c_str() );
				count++;
			}
			if (!xmlsubnode)
				return false;

			ItNode++;
		}
		xmlAttrib = xmlsubnode.attribute( Attribute.c_str() );
		return true;
	}
	return false;
}

u32 CXMLParserPUGI::GetNodeNameCount(const string& NodePath)
{
	int retValue = 0;
	vector< pair<string,int> > Nodes;
	GetNodes(NodePath, Nodes);
	if (Nodes.size() > 0)
	{
		//Siempre necesitamos como minimo el ROOTNODE
		vector< pair<string,int> >::iterator ItNode = Nodes.begin();
		pugi::xml_node xmlsubnode = m_doc.child( ItNode->first.c_str() );
		ItNode++;
		while ( ItNode != Nodes.end() )
		{
			//Recorremos todos los subnodos
			xmlsubnode = xmlsubnode.child( ItNode->first.c_str() );
			int count = 0;
			while (count < ItNode->second && xmlsubnode )
			{
				xmlsubnode = xmlsubnode.next_sibling( ItNode->first.c_str() );
				count++;
			}
			if (!xmlsubnode)
				return retValue;
			ItNode++;
		}

		while ( xmlsubnode )
		{
			xmlsubnode = xmlsubnode.next_sibling( xmlsubnode.name() );
			retValue++;
		}

		return retValue;
	}
	return retValue;
}

bool CXMLParserPUGI::Ready()
{
	return (m_resultat.status == pugi::status_ok);
}

inline void CXMLParserPUGI::GetNodes(string NodePath, vector< pair<string,int> > &AllNodes)
{
	vector<string> Nodes;

	StringExplode( NodePath, Nodes, '/' );

	vector<string>::iterator NodesIt = Nodes.begin();
	while (NodesIt != Nodes.end())
	{
		vector<string> TagNode;
		StringExplode( *NodesIt, TagNode, '#' );

		if ( TagNode.size() > 0 )
		{
			pair<string,int> NodePair(TagNode[0], 0);
			if ( TagNode.size() > 1 )
			{
				stringstream convert(TagNode[1]);
				if ( !(convert >> NodePair.second) )
					NodePair.second = 0;
			}
			AllNodes.push_back( NodePair);
		}
		NodesIt++;
	}

}
