#pragma once

#include "../xConstantBuffer.h"
#include "xPrerequisites.h"
#include "../xProgramVariable.h"

class xShaderResource
{
	enum Enum
	{
		Texture,
		Sampler
	};

	friend class xRenderDevice;
public:
	xShaderResource(UINT slot, xProgramVariable* variable)		
		: mSlot(slot)
	{
		if (variable->Type() == xProgramVariableType::Texture)
		{
			mType = Texture;
			mTextureVariable = (xProgramTextureVariable*)variable;
		}
		else if (variable->Type() == xProgramVariableType::Sampler)
		{
			mType = Texture;
			mTextureVariable = (xProgramTextureVariable*)variable;
		}
	}

protected:
	Enum	mType;
	UINT	mSlot;

	union
	{
		xProgramTextureVariable*	mTextureVariable;
		xProgramSamplerVariable*	mSamplerVariable;
	};
};

struct xProgram::Impl
{
	typedef xList<xConstantBuffer*>	BufferList;
	typedef xList<xShaderResource> ResourceList;
	typedef xMap<xString, xProgramVariableHolder*>	VariableList;

	xSharedPtr<xVertexShader>	mVertexShader;
	xSharedPtr<xPixelShader>	mPixelShader;
	VariableList				mVariables;
	BufferList					mVSBuffers;	
	BufferList					mPSBuffers;		
	BufferList					mGSBuffers;
	
	ResourceList				mVSResources;
	ResourceList				mPSResources;
	ResourceList				mGSResources;

	void Reflect(ID3DBlob* compiled_shader, BufferList& buffers, ResourceList& resources);
};