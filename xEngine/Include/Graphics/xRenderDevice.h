#pragma once

struct xPrimitiveType
{
	enum Enum
	{
		PointList,
		LineList,
		LineStrip,
		TriangleList,
		TriangleStrip
	};
};

class xEXPORT xRenderDevice
{
	xHIDE_IMPLEMENTATION
public:
	xRenderDevice(xRenderWindow* window);
	~xRenderDevice();
	
	void Clear(const xColor& color);
	//void SetIndexBuffer(xIndexBuffer* buffer);
	void SetMaterial(xMaterial* material);
	void SetVertexBuffer(xVertexBuffer* buffer);
	void DrawPrimitive(xPrimitiveType::Enum type, xUInt32 start_vertex, xUInt32 vertex_count);
	//void DrawIndexedPrimitive(xPrimitiveType::Enum type, xUInt32 base_vertex, xUInt32 min_index, xUInt32 vertex_count, xUInt32 start_index, xUInt32 primitive_count);
	void Present();

	void SetUniform(const xString& name, const xMatrix& value);
};