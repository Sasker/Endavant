#ifndef CGLSHADER_H_
#define CGLSHADER_H_

#include <GL/glew.h>
#include <string>

class CGLShader
{
public:
	enum GLShaderType
	{
		VERTEX = 0,
		FRAGMENT
	};

	CGLShader();
	~CGLShader();

	bool			LoadFile(std::string &fileName, GLShaderType ShaderType);	//<! Load Shader from file
	void			PrintInfoLog();												//<! Print Shader compilation log
	inline GLuint	GetID();													//<! Get Shader id


	// TODO
	// Load shader from code directly
	//bool			LoadCode(std::string &shadercode, GLShaderType ShaderType);

private:
	bool			Compile();													//<! Generate shader & upload shader code & compile

	GLenum			m_Type;
	GLuint			m_ID;

	std::string		m_ShaderCode;
	bool			m_LoadedAndCompiled;



};

#endif
