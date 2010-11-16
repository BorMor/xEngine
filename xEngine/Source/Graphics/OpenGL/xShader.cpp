#include "xEngine.h"
#include "xShaderImpl.h"
#include "../xShaderPreprocessor.h"

xShader::xShader(xShaderType::Enum type)
{
	pImpl = new Impl;	
	switch (type)
	{
	case xShaderType::Vertex:
		pImpl->mName = glCreateShader(GL_VERTEX_SHADER);
		break;
	case xShaderType::Fragment:
		pImpl->mName = glCreateShader(GL_FRAGMENT_SHADER);
		break;
	case xShaderType::Geometry:
		pImpl->mName = glCreateShader(GL_GEOMETRY_SHADER);
		break;
	}
}

xShader::~xShader()
{
	glDeleteShader(pImpl->mName);
	xSAFE_DELETE(pImpl);
}

void xShader::LoadFromFile(const xString& path)
{
	xString source = xShaderPreprocessor::LoadContents(path);
	// Load and compile
	const char* ptr = source.c_str();
	glShaderSource(pImpl->mName, 1, (const char**)&ptr, 0);
	glCompileShader(pImpl->mName);
/*
	GLint compiled;
	glGetShaderiv(pImpl->mName, GL_COMPILE_STATUS, &compiled);
	if (!compiled)
	{
		GLint logLength, charsWritten;
		char* log;
		
		glGetShaderiv(pImpl->mName, GL_INFO_LOG_LENGTH, &logLength);


		log = (char*)malloc(logLength);

        glGetShaderInfoLog(pImpl->mName, logLength, &charsWritten, log);

		printf("Shader compile error:\n");
		printf("%s\n", log);

		free(log);
	}*/
}
