#include "xEngine.h"
#include "xProgramVariable.h"

xProgramVariableHolder	gProgramDefaultVariable;
xProgramScalarVariable	gProgramDefaultScalarVariable;
xProgramVectorVariable	gProgramDefaultVectorVariable(xProgramVectorVariable::Float, 0, 0);
xProgramMatrixVariable	gProgramDefaultMatrixVariable;
xProgramSamplerVariable	gProgramDefaultSamplerVariable;


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

xProgramMatrixVariable::xProgramMatrixVariable()
	: xProgramVariable(xProgramVariableType::Matrix)
{
}

xProgramMatrixVariable::~xProgramMatrixVariable()
{
}

// xProgramSamplerVariable

xProgramSamplerVariable::xProgramSamplerVariable()
	: xProgramVariable(xProgramVariableType::Sampler)
{
}

xProgramSamplerVariable::~xProgramSamplerVariable()
{
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