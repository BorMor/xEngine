#include "xEngine.h"
#include "xProgramImpl.h"
#include "xVertexShaderImpl.h"
#include "xPixelShaderImpl.h"
#include "xConstantBufferImpl.h"
#include "../xProgramVariable.h"

xProgram::xProgram(const xString& vertex_shader, const xString& pixel_shader, const xString& geometry_shader)
{
	pImpl = new Impl;
	
	pImpl->mUniformsBuffer = 0;

	pImpl->mProgram = glCreateProgram();  
	
	pImpl->mVertexShader = xVertexShader::LoadFromFile(vertex_shader);
	glAttachShader(pImpl->mProgram, pImpl->mVertexShader->pImpl->mName);	

	pImpl->mFragmentShader = xPixelShader::LoadFromFile(pixel_shader);
	glAttachShader(pImpl->mProgram, pImpl->mFragmentShader->pImpl->mName);

	glLinkProgram(pImpl->mProgram);

	GLint active_uniform_blocks = 0;
	glGetProgramiv(pImpl->mProgram, GL_ACTIVE_UNIFORM_BLOCKS, &active_uniform_blocks);
	
	for (GLint i = 0; i < active_uniform_blocks; i++)
	{
		GLint block_size = 0;
		glGetActiveUniformBlockiv(pImpl->mProgram, i,  GL_UNIFORM_BLOCK_DATA_SIZE, &block_size);
//		GLint block_binding = -1;
//		glGetActiveUniformBlockiv(pImpl->mProgram, i,  GL_UNIFORM_BLOCK_BINDING , &block_binding);
		xConstantBuffer* buffer = new xConstantBuffer(block_size);
		glBindBufferBase(GL_UNIFORM_BUFFER, i, buffer->pImpl->mUBO);
		glUniformBlockBinding(pImpl->mProgram, i, i);
		pImpl->mBuffers.AddBack(buffer);
	}

	GLint active_uniforms = 0;
	size_t uniform_buffer_size = 0;
	
	glGetProgramiv(pImpl->mProgram, GL_ACTIVE_UNIFORMS, &active_uniforms);
	for (GLint i = 0; i < active_uniforms; i++)
	{
		GLint elements;
		GLenum type;
		char variable_name[256];	
		glGetActiveUniform(pImpl->mProgram, (GLuint)i, 256, 0, &elements, &type, variable_name);
		
		GLint block_index = -1;
		glGetActiveUniformsiv(pImpl->mProgram, 1, (const GLuint*)&i, GL_UNIFORM_BLOCK_INDEX, &block_index);


		Impl::UniformInfo info;
		info.Location = i;
		info.Type = type;
		info.Elements = elements;
		info.Offset = uniform_buffer_size;
		
		xProgramVariable* program_variable = NULL;

//#define GL_BOOL_VEC2	0x8B57
//#define GL_BOOL_VEC3	0x8B58
//#define GL_BOOL_VEC4	0x8B59

		switch (type)
		{
		case GL_FLOAT_VEC2:
		case GL_FLOAT_VEC3:
		case GL_FLOAT_VEC4:
			program_variable = new xProgramVectorVariable(xProgramVectorVariable::Float, type - GL_FLOAT_VEC2 + 2, elements);
			uniform_buffer_size += (type - GL_FLOAT_VEC2 + 2) * sizeof(float);
			break;
		case GL_INT_VEC2:
		case GL_INT_VEC3:
		case GL_INT_VEC4:
			program_variable = new xProgramVectorVariable(xProgramVectorVariable::Int, type - GL_INT_VEC2 + 2, elements);
			uniform_buffer_size += (type - GL_INT_VEC2 + 2) * sizeof(int);
			break;
		}

		if (program_variable)
		{
			if (block_index == -1)	// global uniform
			{
				info.Variable = program_variable;
				pImpl->mUniforms.AddBack(info);
			}
			else
			{
				GLint offset = 0;
				glGetActiveUniformsiv(pImpl->mProgram, 1, (const GLuint*)&i, GL_UNIFORM_OFFSET, &offset);				
				program_variable->pImpl->AddSetter(new xProgramVariableBufferSetter(pImpl->mBuffers[block_index], (size_t)offset));
			}
			pImpl->mVariables.Insert(variable_name, new xProgramVariableHolder(program_variable));
		}
	}

	if (uniform_buffer_size)
		pImpl->mUniformsBuffer = new xBuffer(uniform_buffer_size);

	for (Impl::UniformInfoList::Iterator it = pImpl->mUniforms.Begin(); it != pImpl->mUniforms.End(); ++it)
		it->Variable->pImpl->AddSetter(new xProgramVariableBufferSetter(pImpl->mUniformsBuffer, it->Offset));
}

xProgram::~xProgram()
{
	for (Impl::VariableList::Iterator it = pImpl->mVariables.Begin(); it != pImpl->mVariables.End(); ++it)
		delete it->Value();
	pImpl->mVariables.Clear();

	for (Impl::BufferList::Iterator it = pImpl->mBuffers.Begin(); it != pImpl->mBuffers.End(); ++it)
		delete *it;
	pImpl->mBuffers.Clear();

	for (Impl::UniformInfoList::Iterator it = pImpl->mUniforms.Begin(); it != pImpl->mUniforms.End(); ++it)
		delete it->Variable;
	pImpl->mUniforms.Clear();

	if (pImpl->mUniformsBuffer)
		delete pImpl->mUniformsBuffer;

	glDeleteProgram(pImpl->mProgram);
	if (pImpl->mFragmentShader)
		glDeleteShader(pImpl->mFragmentShader);
	if (pImpl->mVertexShader)
		glDeleteShader(pImpl->mVertexShader);
	xSAFE_DELETE(pImpl);
}

void xProgram::Impl::SetupUniforms()
{
		if (mUniformsBuffer)
		{
			const xByte* data = (const xByte*)mUniformsBuffer->Data();
			for (UniformInfoList::Iterator it = mUniforms.Begin(); it != mUniforms.End(); ++it)
			{
				switch (it->Type)
				{
				case GL_FLOAT_VEC2:
					glUniform2fv(it->Location, it->Elements, (const GLfloat*)(data + it->Offset));
					break;
				case GL_FLOAT_VEC3:
					glUniform3fv(it->Location, it->Elements, (const GLfloat*)(data + it->Offset));
					break;
				case GL_FLOAT_VEC4:
					glUniform4fv(it->Location, it->Elements, (const GLfloat*)(data + it->Offset));
					break;
				case GL_INT_VEC2:
					glUniform2iv(it->Location, it->Elements, (const GLint*)(data + it->Offset));
					break;
				case GL_INT_VEC3:
					glUniform3iv(it->Location, it->Elements, (const GLint*)(data + it->Offset));
					break;
				case GL_INT_VEC4:
					glUniform4iv(it->Location, it->Elements, (const GLint*)(data + it->Offset));
					break;
				}
			}
		}
	}

xProgramVariableHolder* xProgram::GetVariableByName(const xString& name)
{
	Impl::VariableList::Iterator it = pImpl->mVariables.Find(name);
	if (it != pImpl->mVariables.End())
		return it->Value();
	return &gProgramDefaultVariable;
}