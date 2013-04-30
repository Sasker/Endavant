/*
 * Conversions.h
 *
 *  Created on: 09/03/2012
 *      Author: dani
 */

#ifndef CONVERSIONS_H_
#define CONVERSIONS_H_
#include <sstream>
#include <vector>
#include <string>

//Passa Qualsevol tipus de dades a String
template <class T> inline std::string to_string (const T& t)
{
	std::stringstream ss;
	ss << t;
	return ss.str();
}

inline void StringExplode(std::string InputString, std::vector<std::string> &AllTokens, char TokenChar)
{
    std::istringstream iss(InputString);
    while (!iss.eof())
    {
      std::string token;
      getline( iss, token, TokenChar );
      AllTokens.push_back( token );
    }
}
#endif /* CONVERSIONS_H_ */
