#include "CGLError.h"
#include "cstdio"
#include "GL/glew.h"

bool InitGLDebugFunctions()
{

	if (glewIsSupported("GL_ARB_debug_output"))
	{
		glDebugMessageCallbackARB(DebugCallbackARB,stderr);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB);
		return true;
	}

	if (glewIsSupported("GL_AMD_debug_output"))
	{
		glDebugMessageCallbackAMD(DebugCallbackAMD,stderr);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB);
		return true;
	}

	return false;
}



void DebugCallbackARB(GLenum source, GLenum type, GLuint id, GLenum severity,GLsizei length, const GLchar *message, GLvoid *userParam)
{
	(void)length;
	FILE *outFile = (FILE*)userParam;
	char finalMessage[256];
	FormatDebugOutputARB(finalMessage, 256, source, type, id, severity, message);
	fprintf(outFile, "%s\n", finalMessage);
}

void FormatDebugOutputARB(char outStr[], size_t outStrSize, GLenum source, GLenum type,  GLuint id, GLenum severity, const char *msg)
{
	char sourceStr[32];
	const char *sourceFmt = "UNDEFINED(0x%04X)";
	switch(source)

	{
	case GL_DEBUG_SOURCE_API_ARB:             sourceFmt = "API"; break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM_ARB:   sourceFmt = "WINDOW_SYSTEM"; break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER_ARB: sourceFmt = "SHADER_COMPILER"; break;
	case GL_DEBUG_SOURCE_THIRD_PARTY_ARB:     sourceFmt = "THIRD_PARTY"; break;
	case GL_DEBUG_SOURCE_APPLICATION_ARB:     sourceFmt = "APPLICATION"; break;
	case GL_DEBUG_SOURCE_OTHER_ARB:           sourceFmt = "OTHER"; break;
	}

	snprintf(sourceStr, 32, sourceFmt, source);

	char typeStr[32];
	const char *typeFmt = "UNDEFINED(0x%04X)";
	switch(type)
	{

	case GL_DEBUG_TYPE_ERROR_ARB:               typeFmt = "ERROR"; break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_ARB: typeFmt = "DEPRECATED_BEHAVIOR"; break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_ARB:  typeFmt = "UNDEFINED_BEHAVIOR"; break;
	case GL_DEBUG_TYPE_PORTABILITY_ARB:         typeFmt = "PORTABILITY"; break;
	case GL_DEBUG_TYPE_PERFORMANCE_ARB:         typeFmt = "PERFORMANCE"; break;
	case GL_DEBUG_TYPE_OTHER_ARB:               typeFmt = "OTHER"; break;
	}
	snprintf(typeStr, 32, typeFmt, type);


	char severityStr[32];
	const char *severityFmt = "UNDEFINED";
	switch(severity)
	{
	case GL_DEBUG_SEVERITY_HIGH_ARB:   severityFmt = "HIGH";   break;
	case GL_DEBUG_SEVERITY_MEDIUM_ARB: severityFmt = "MEDIUM"; break;
	case GL_DEBUG_SEVERITY_LOW_ARB:    severityFmt = "LOW"; break;
	}

	snprintf(severityStr, 32, severityFmt, severity);

	snprintf(outStr, outStrSize, "OpenGL: %s [source=%s type=%s severity=%s id=%d]",
			msg, sourceStr, typeStr, severityStr, id);
}


void DebugCallbackAMD(GLuint id, GLenum category, GLenum severity, GLsizei length,const GLchar *message, GLvoid *userParam)
{
	(void)length;
	FILE *outFile = (FILE*)userParam;
	char finalMsg[256];
	FormatDebugOutputAMD(finalMsg, 256, category, id, severity, message);
	fprintf(outFile, "%s\n", finalMsg);
}


void FormatDebugOutputAMD(char outStr[], size_t outStrSize, GLenum category, GLuint id,GLenum severity, const char *msg)
{
	char categoryStr[32];
	const char *categoryFmt = "UNDEFINED(0x%04X)";
	switch(category)
	{
	case GL_DEBUG_CATEGORY_API_ERROR_AMD:          categoryFmt = "API_ERROR"; break;
	case GL_DEBUG_CATEGORY_WINDOW_SYSTEM_AMD:      categoryFmt = "WINDOW_SYSTEM"; break;
	case GL_DEBUG_CATEGORY_DEPRECATION_AMD:        categoryFmt = "DEPRECATION"; break;
	case GL_DEBUG_CATEGORY_UNDEFINED_BEHAVIOR_AMD: categoryFmt = "UNDEFINED_BEHAVIOR"; break;
	case GL_DEBUG_CATEGORY_PERFORMANCE_AMD:        categoryFmt = "PERFORMANCE"; break;
	case GL_DEBUG_CATEGORY_SHADER_COMPILER_AMD:    categoryFmt = "SHADER_COMPILER"; break;
	case GL_DEBUG_CATEGORY_APPLICATION_AMD:        categoryFmt = "APPLICATION"; break;
	case GL_DEBUG_CATEGORY_OTHER_AMD:              categoryFmt = "OTHER"; break;
	}
	snprintf(categoryStr, 32, categoryFmt, category);

	char severityStr[32];
	const char *severityFmt = "UNDEFINED";
	switch(severity)
	{
	case GL_DEBUG_SEVERITY_HIGH_AMD:   severityFmt = "HIGH";   break;
	case GL_DEBUG_SEVERITY_MEDIUM_AMD: severityFmt = "MEDIUM"; break;
	case GL_DEBUG_SEVERITY_LOW_AMD:    severityFmt = "LOW";    break;
	}
	snprintf(severityStr, 32, severityFmt, severity);

	snprintf(outStr, outStrSize, "OpenGL: %s [category=%s severity=%s id=%d]",
			msg, categoryStr, severityStr, id);
}


