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
	struct Element
	{
		size_t						Offset;
		xVertexElementType::Enum	Type;
		xVertexElementUsage::Enum	Usage;
	};
	typedef xArray<Element> ElementList;

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
	ElementList		mElements;
	size_t			mSize;
};