#pragma once
#include "VertexBuffer.h"

class VertexBufferLayout;

class VertexArray
{
private:
	unsigned int m_RendererID;
	unsigned int m_RecordNumber = 0;
public:
	void Bind() const;
	void UnBind() const;
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& vb,const VertexBufferLayout& Layout);

	void AddInstance(const VertexBuffer& vb,unsigned int count,unsigned int index,unsigned int divisor);
};