#include "xEngine.h"
#include "xMaterialImpl.h"

xMaterial::xMaterial()
{
	pImpl = new Impl;

	pImpl->mVertexShader = glCreateShader(GL_VERTEX_SHADER);	
	pImpl->mFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	pImpl->mProgram = glCreateProgram();
	glAttachShader(pImpl->mProgram, pImpl->mVertexShader);	
    glAttachShader(pImpl->mProgram, pImpl->mFragmentShader);
	glLinkProgram(pImpl->mProgram);
}

xMaterial::~xMaterial()
{
	glDeleteProgram(pImpl->mProgram);
	glDeleteShader(pImpl->mFragmentShader);
	glDeleteShader(pImpl->mVertexShader);
	xSAFE_DELETE(pImpl);
}

void xMaterial::SetVertexShader(const xString& source)
{
	const char* src = source.c_str();
	glShaderSource(pImpl->mVertexShader, 1, (const char**)&src, 0);
	glCompileShader(pImpl->mVertexShader);	

	glLinkProgram(pImpl->mProgram);//fix
}

void xMaterial::SetFragmentShader(const xString& source)
{
	const char* src = source.c_str();
	glShaderSource(pImpl->mFragmentShader, 1, (const char**)&src, 0);
	glCompileShader(pImpl->mFragmentShader);

	GLint compiled;
	glGetShaderiv(pImpl->mVertexShader, GL_COMPILE_STATUS, &compiled);

	if (!compiled)
	{
		GLint logLength, charsWritten;
		char* log;
		
		glGetShaderiv(pImpl->mVertexShader, GL_INFO_LOG_LENGTH, &logLength);


		log = (char*)malloc(logLength);

		// http://www.opengl.org/sdk/docs/man/xhtml/glGetShaderInfoLog.xml
        glGetShaderInfoLog(pImpl->mVertexShader, logLength, &charsWritten, log);

		printf("Vertex shader compile error:\n");
		printf("%s\n", log);

		free(log);
	}

	/*
	GLint compiled;
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &compiled);
	if (!compiled)
	{
		GLint length, written;
		glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);

		char* log = (char*)malloc(length);
        glGetShaderInfoLog(vertex, length, &written, log);
		free(log);
	}*/

	glLinkProgram(pImpl->mProgram);//fix
}