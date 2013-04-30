#include "CGLShader.h"
#include "CCoreEngine.h"
#include "CLogManager.h"
#include <iostream>
#include <fstream>


CGLShader::CGLShader():
m_Type(GL_INVALID_ENUM),
m_ID(GL_ZERO),
m_ShaderCode(""),
m_LoadedAndCompiled(false)
{
}

CGLShader::~CGLShader()
{
	glDeleteShader(m_ID);
}



bool CGLShader::Compile()
{
	m_ID = glCreateShader(m_Type);
	if (m_ID)
	{
		GLchar * l_code =(GLchar *) m_ShaderCode.c_str();

		glShaderSource(m_ID, 1, (const GLchar **) &l_code, NULL);
		glCompileShader(m_ID);



		GLint l_compileresult = GL_FALSE;
		glGetShaderiv(m_ID, GL_COMPILE_STATUS, &l_compileresult);
		if(l_compileresult == GL_TRUE)
		{
			m_LoadedAndCompiled = true;
			return true;
		}
		else
			PrintInfoLog();


		return false;
	}
	else
	{
		CCoreEngine::Instance().GetLogManager().LogOutput(LOG_ERROR, LOGSUB_VIDEO, "Failed creating shader");
		return false;
	}
}

bool CGLShader::LoadFile(std::string &fileName, GLShaderType ShaderType)
{

	if (!m_LoadedAndCompiled)
	{

		std::ifstream l_file(fileName.c_str());
		if (l_file.good())
		{
			//http://insanecoding.blogspot.com.es/2011/11/how-to-read-in-file-in-c.html
			l_file.seekg(0, std::ios::end);
		    m_ShaderCode.resize(l_file.tellg());
		    l_file.seekg(0, std::ios::beg);
		    l_file.read(&m_ShaderCode[0], m_ShaderCode.size());
		    //TODO potser al m_Shadercode se li ha de sumar 1 al size i posar a lultima
		    // posicio el caracter \0
		    l_file.close();

		    return Compile();

		}
		else
			CCoreEngine::Instance().GetLogManager().LogOutput(LOG_ERROR, LOGSUB_VIDEO, "CGLShader::LoadFile File %s not found.",fileName.c_str());

	}

	return false;
}




void CGLShader::PrintInfoLog()
{
	GLint l_loglength;
	glGetShaderiv(m_ID, GL_INFO_LOG_LENGTH, &l_loglength);

	if (l_loglength)
	{
		std::string l_log(l_loglength, 0);
		glGetShaderInfoLog(m_ID, l_loglength, 0, &l_log[0]);
		CCoreEngine::Instance().GetLogManager().LogOutput(LOG_ERROR, LOGSUB_VIDEO, "CGLShader::PrintInfoLog: %s",l_log.c_str());
	}


}

inline GLuint CGLShader::GetID()
{
	return m_ID;
}


