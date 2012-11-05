#include "xEngine.h"
#include "xPixelShaderImpl.h"
#include "xVertexShaderImpl.h"
#include "../xProgramVariable.h"
#include "xProgramImpl.h"
#include "xConstantBufferImpl.h"

xProgram::xProgram(const xString& vertex_shader, const xString& pixel_shader, const xString& geometry_shader)
{
	pImpl = new Impl;	
	pImpl->mVertexShader = xVertexShader::LoadFromFile(vertex_shader);
	pImpl->mPixelShader = xPixelShader::LoadFromFile(pixel_shader);
	
	pImpl->Reflect(pImpl->mVertexShader->pImpl->mCompiledShader, pImpl->mVSBuffers, pImpl->mVSResources);
	pImpl->Reflect(pImpl->mPixelShader->pImpl->mCompiledShader, pImpl->mPSBuffers, pImpl->mPSResources);
}

xProgram::~xProgram()
{
	for (Impl::VariableList::Iterator it = pImpl->mVariables.Begin(); it != pImpl->mVariables.End(); ++it)
		delete it->Value();
	pImpl->mVariables.Clear();

	for (Impl::BufferList::Iterator it = pImpl->mGSBuffers.Begin(); it != pImpl->mGSBuffers.End(); ++it)
		delete *it;
	pImpl->mGSBuffers.Clear();
	
	for (Impl::BufferList::Iterator it = pImpl->mPSBuffers.Begin(); it != pImpl->mPSBuffers.End(); ++it)
		delete *it;
	pImpl->mPSBuffers.Clear();

	for (Impl::BufferList::Iterator it = pImpl->mVSBuffers.Begin(); it != pImpl->mVSBuffers.End(); ++it)
		delete *it;
	pImpl->mVSBuffers.Clear();
	
	xSAFE_DELETE(pImpl);
}

void xProgram::Impl::Reflect(ID3DBlob* compiled_shader, BufferList& buffers, ResourceList& resources)
{
	ID3D11ShaderReflection*	reflection = NULL;
	D3DReflect(compiled_shader->GetBufferPointer(), compiled_shader->GetBufferSize(), IID_ID3D11ShaderReflection, (void**)&reflection);
	D3D11_SHADER_DESC shader_desc;
	reflection->GetDesc(&shader_desc);

	for (size_t i = 0; i < shader_desc.BoundResources; i++)
	{
		D3D11_SHADER_INPUT_BIND_DESC input_desc;
		reflection->GetResourceBindingDesc(i, &input_desc);
		
		xProgramVariable* program_variable = NULL;
		xString variable_name = input_desc.Name;	
		
		switch (input_desc.Type)
		{
		case D3D_SIT_TEXTURE:
			program_variable = new xProgramTextureVariable();
			break;
		}
		if (program_variable)
		{
			resources.AddBack(xShaderResource(input_desc.BindPoint, program_variable));
			mVariables.Insert(variable_name, new xProgramVariableHolder(program_variable));
		}
	}
	for (size_t i = 0; i < shader_desc.ConstantBuffers; i++)
	{		
		ID3D11ShaderReflectionConstantBuffer* constant_buffer = reflection->GetConstantBufferByIndex(i);
		D3D11_SHADER_BUFFER_DESC buffer_desc;
		constant_buffer->GetDesc(&buffer_desc);

		xConstantBuffer* buffer = new xConstantBuffer(buffer_desc.Size);

		for (size_t j = 0; j < buffer_desc.Variables; j++)
		{
			ID3D11ShaderReflectionVariable* variable = constant_buffer->GetVariableByIndex(j);
			D3D11_SHADER_VARIABLE_DESC variable_desc;
			variable->GetDesc(&variable_desc);
			ID3D11ShaderReflectionType* type = variable->GetType();
			D3D11_SHADER_TYPE_DESC type_desc;
			type->GetDesc(&type_desc);

			xProgramVariable* program_variable = NULL;
			xString variable_name = variable_desc.Name;				
			VariableList::Iterator it = mVariables.Find(variable_name);
			if (it != mVariables.End())
				program_variable = it->Value()->mVariable;
			else
			{
				switch (type_desc.Class)
				{
				case D3D_SVC_SCALAR:
					program_variable = new xProgramScalarVariable();
					break;
				case D3D_SVC_VECTOR:						
					switch (type_desc.Type)
					{
					case D3D_SVT_FLOAT:
						program_variable = new xProgramVectorVariable(xProgramVectorVariable::Float, type_desc.Columns, type_desc.Elements);
						break;
					case D3D_SVT_INT:
						program_variable = new xProgramVectorVariable(xProgramVectorVariable::Int, type_desc.Columns, type_desc.Elements);
						break;
					}
					break;
				case D3D_SVC_MATRIX_ROWS:
					program_variable = new xProgramMatrixVariable(xProgramMatrixVariable::RowMajor, type_desc.Elements);
					break;
				case D3D_SVC_MATRIX_COLUMNS:
					program_variable = new xProgramMatrixVariable(xProgramMatrixVariable::ColumnMajor, type_desc.Elements);
					break;
				}
				if (program_variable)
					mVariables.Insert(variable_name, new xProgramVariableHolder(program_variable));
			}
			if (program_variable)
				program_variable->pImpl->AddSetter(new xProgramVariableBufferSetter(buffer, variable_desc.StartOffset));
		}

		buffers.AddBack(buffer);
	}
}

xProgramVariableHolder* xProgram::GetVariableByName(const xString& name)
{
	Impl::VariableList::Iterator it = pImpl->mVariables.Find(name);
	if (it != pImpl->mVariables.End())
		return it->Value();
	return &gProgramDefaultVariable;
}