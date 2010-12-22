#pragma once

#include "xConstantBuffer.h"

extern xProgramVariableHolder	gProgramDefaultVariable;
extern xProgramScalarVariable	gProgramDefaultScalarVariable;
extern xProgramVectorVariable	gProgramDefaultVectorVariable;
extern xProgramMatrixVariable	gProgramDefaultMatrixVariable;
extern xProgramSamplerVariable	gProgramDefaultSamplerVariable;

class xProgramVariableSetter
{	
public:
	xProgramVariableSetter(){}
	virtual ~xProgramVariableSetter(){}

	virtual void WriteData(void* data, size_t size) = 0;
};

struct xProgramVariable::Impl
{
	typedef xList<xProgramVariableSetter*>	SetterList;

	void AddSetter(xProgramVariableSetter* setter)
	{
		mSetters.AddBack(setter);
	}

	void RemoveSetter(xProgramVariableSetter* setter)
	{
		SetterList::Iterator it = mSetters.Find(setter);
		if (it != mSetters.End())
			mSetters.Remove(it);
	}

	void WriteData(void* data, size_t size)
	{
		for (SetterList::Iterator it = mSetters.Begin(); it != mSetters.End(); ++it)
			(*it)->WriteData(data, size);
	}

	SetterList	mSetters;
};

class xProgramVariableBufferSetter : public xProgramVariableSetter
{
public:
	xProgramVariableBufferSetter(xBuffer* buffer, size_t offset);
	~xProgramVariableBufferSetter();	
protected:
	xBuffer*	mBuffer;
	size_t				mOffset;

	void WriteData(void* data, size_t size);
};