#include "xEngine.h"

struct xVertexElementType
{
	enum Enum
	{
		Float,
		Vector2,
		Vector3,
		Vector4,
		Color
	};
};

struct xVertexElementUsage
{
	enum Enum
	{
		Position = 0,
		Normal,
		Diffuse,
		TexCoord
	};
};

class xEXPORT xVertexFormat
{
	xHIDE_IMPLEMENTATION
	friend class xRenderDevice;
	friend class xVertexBuffer;
public:
	xVertexFormat();
	~xVertexFormat();

	void Clear();
	void AddElement(xVertexElementType::Enum type, xVertexElementUsage::Enum usage);
	size_t VertexSize() const;
protected:
	size_t		mSize;
};