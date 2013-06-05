
// MORE INFO:
// http://www.altdevblogaday.com/2011/06/23/improving-opengl-error-messages/

#ifndef CGLERROR_H_
#define CGLERROR_H_


#include "GLLoad/GLFuncs.h"

//
bool InitGLDebugFunctions();

// ARB FUNCTIONS
void FormatDebugOutputARB(char outStr[], size_t outStrSize, GLenum source, GLenum type,  GLuint id, GLenum severity, const char *msg);
void DebugCallbackARB(GLenum source, GLenum type, GLuint id, GLenum severity,GLsizei length, const GLchar *message, GLvoid *userParam);


// AMD Specific Functions
void FormatDebugOutputAMD(char outStr[], size_t outStrSize, GLenum category, GLuint id,GLenum severity, const char *msg);
void DebugCallbackAMD(GLuint id, GLenum category, GLenum severity, GLsizei length,const GLchar *message, GLvoid *userParam);

#endif /* CGLERROR_H_ */
