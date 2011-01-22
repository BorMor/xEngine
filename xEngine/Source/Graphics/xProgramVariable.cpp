#include "xEngine.h"
#include "xProgramVariable.h"

xProgramVariableHolder	gProgramDefaultVariable;
xProgramScalarVariable	gProgramDefaultScalarVariable;
xProgramVectorVariable	gProgramDefaultVectorVariable(xProgramVectorVariable::Float, 0, 0);
xProgramMatrixVariable	gProgramDefaultMatrixVariable(xProgramMatrixVariable::RowMajor, 0);
xProgramSamplerVariable	gProgramDefaultSamplerVariable;
xProgramTextureVariable gProgramDefaultTextureVariable;

// xProgramVariable

xProgramVariable::xProgramVariable(xProgramVariableType::Enum type)
	: mType(type)
{
	pImpl = new Impl;
}

xProgramVariable::~xProgramVariable()
{
	xSAFE_DELETE(pImpl);
}

bool xProgramVariable::IsValid() const
{
	return mType != xProgramVariableType::Undefined && pImpl->mSetters.Size() != 0;
}

xProgramVariableType::Enum xProgramVariable::Type() const
{
	return mType;
}

// xProgramScalarVariable

xProgramScalarVariable::xProgramScalarVariable()
	: xProgramVariable(xProgramVariableType::Scalar)
{
}

xProgramScalarVariable::~xProgramScalarVariable()
{
}

// xProgramVectorVariable

xProgramVectorVariable::xProgramVectorVariable(Type type, size_t columns, size_t elements)
	: xProgramVariable(xProgramVariableType::Vector), mType(type), mColumns(columns), mElements(elements)
{
}

xProgramVectorVariable::~xProgramVectorVariable()
{
}

bool xProgramVectorVariable::Set(const xVector4& value)
{
	if (mType == Float && mColumns == 4)
	{
		pImpl->WriteData((void*)&value.X, 4*sizeof(float));
		return true;
	}
	return false;
}

// xProgramMatrixVariable

xProgramMatrixVariable::xProgramMatrixVariable(Type type, size_t elements)
	: xProgramVariable(xProgramVariableType::Matrix), mType(type), mElements(elements)
{
}

xProgramMatrixVariable::~xProgramMatrixVariable()
{
}

bool xProgramMatrixVariable::Set(const xMatrix& value)
{
	if (mType == RowMajor)
		pImpl->WriteData((void*)&value.M00, 16*sizeof(float));
	else
	{
		xMatrix transposed = value.Transposed();
		pImpl->WriteData((void*)&transposed.M00, 16*sizeof(float));
	}
	return true;
}

// xProgramSamplerVariable

xProgramSamplerVariable::xProgramSamplerVariable()
	: xProgramVariable(xProgramVariableType::Sampler)
{
}

xProgramSamplerVariable::~xProgramSamplerVariable()
{
}

// xProgramTextureVariable

xProgramTextureVariable::xProgramTextureVariable()
	: xProgramVariable(xProgramVariableType::Texture), mTexture(NULL)
{
}

xProgramTextureVariable::~xProgramTextureVariable()
{
}

bool xProgramTextureVariable::Set(const xTexture* texture)
{
	mTexture = texture;
	return true;
}

// xProgramVariableHolder

xProgramVariableHolder::xProgramVariableHolder(xProgramVariable* variable)
	: mVariable(variable)
{
}

xProgramVariableHolder::~xProgramVariableHolder()
{
}

bool xProgramVariableHolder::IsValid() const
{
	return mVariable.UseCount() > 0;
}

xProgramVariableType::Enum xProgramVariableHolder::Type() const
{
	if (mVariable)
		return mVariable->Type();
	return xProgramVariableType::Undefined;
}

xProgramScalarVariable* xProgramVariableHolder::AsScalar() const
{
	if (mVariable && mVariable->Type() == xProgramVariableType::Scalar)
		return (xProgramScalarVariable*)(xProgramVariable*)mVariable;
	return &gProgramDefaultScalarVariable;
}

xProgramVectorVariable* xProgramVariableHolder::AsVector() const
{
	if (mVariable && mVariable->Type() == xProgramVariableType::Vector)
		return (xProgramVectorVariable*)(xProgramVariable*)mVariable; 
	return &gProgramDefaultVectorVariable;
}

xProgramMatrixVariable* xProgramVariableHolder::AsMatrix() const
{
	if (mVariable && mVariable->Type() == xProgramVariableType::Matrix)
		return (xProgramMatrixVariable*)(xProgramVariable*)mVariable;
	return &gProgramDefaultMatrixVariable;
}

xProgramSamplerVariable* xProgramVariableHolder::AsSampler() const
{
	if (mVariable && mVariable->Type() == xProgramVariableType::Sampler)
		return (xProgramSamplerVariable*)(xProgramVariable*)mVariable;
	return &gProgramDefaultSamplerVariable;
}

xProgramTextureVariable* xProgramVariableHolder::AsTexture() const
{
	if (mVariable && mVariable->Type() == xProgramVariableType::Texture)
		return (xProgramTextureVariable*)(xProgramVariable*)mVariable;
	return &gProgramDefaultTextureVariable;
}

// xProgramVariableBufferSetter
xProgramVariableBufferSetter::xProgramVariableBufferSetter(xBuffer* buffer, size_t offset)
	: mBuffer(buffer), mOffset(offset)
{
}

xProgramVariableBufferSetter::~xProgramVariableBufferSetter()
{
}

void xProgramVariableBufferSetter::WriteData(void* data, size_t size)
{
	mBuffer->WriteData(mOffset, data, size);
}