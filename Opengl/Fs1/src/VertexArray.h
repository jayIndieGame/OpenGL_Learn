#pragma once
#include "VertexBuffer.h"

class VertexBufferLayout;

class VertexArray
{
private:
	unsigned int m_RendererID;
public:
	void Bind() const;
	void UnBind() const;
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& vb,const VertexBufferLayout& Layout);
};