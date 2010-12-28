#pragma once

struct xEXPORT xProgramVariableType
{
	enum Enum
	{
		Undefined,
		Scalar,
		Vector,
		Matrix,
		Sampler
	};
};

class xEXPORT xProgramVariable
{
	xHIDE_IMPLEMENTATION
	friend class xProgram;
public:
	xProgramVariable(xProgramVariableType::Enum type = xProgramVariableType::Undefined);
	virtual ~xProgramVariable();

	bool IsValid() const;
	xProgramVariableType::Enum Type() const;	
protected:	
	xProgramVariableType::Enum	mType;	
};

class xEXPORT xProgramScalarVariable : public xProgramVariable
{
public:
	xProgramScalarVariable();
	~xProgramScalarVariable();
};

class xEXPORT xProgramVectorVariable : public xProgramVariable
{
public:
	enum Type
	{
		Float,
		Int
	};

	xProgramVectorVariable(Type type, size_t columns, size_t elements);
	~xProgramVectorVariable();

	bool Set(const xVector4& value);
protected:
	Type	mType;
	size_t	mColumns;
	size_t	mElements;
};

class xEXPORT xProgramMatrixVariable : public xProgramVariable
{
public:
	enum Type
	{
		ColumnMajor,
		RowMajor
	};

	xProgramMatrixVariable(Type type, size_t elements);
	~xProgramMatrixVariable();

	bool Set(const xMatrix& value);
protected:
	Type	mType;
	size_t	mElements;
};

class xEXPORT xProgramSamplerVariable : public xProgramVariable
{
public:
	xProgramSamplerVariable();
	~xProgramSamplerVariable();
};

class xEXPORT xProgramVariableHolder
{
	friend class xProgram;
public:
	xProgramVariableHolder(xProgramVariable* variable = NULL);
	~xProgramVariableHolder();

	bool IsValid() const;
	xProgramVariableType::Enum Type() const;

	xProgramScalarVariable* AsScalar() const;
	xProgramVectorVariable* AsVector() const;
	xProgramMatrixVariable* AsMatrix() const;
	xProgramSamplerVariable* AsSampler() const;
protected:
	xSharedPtr<xProgramVariable>	mVariable;
};