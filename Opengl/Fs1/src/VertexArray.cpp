#include "VertexArray.h"
#include "Renderer.h"
#include "VertexBufferLayout.h"

void VertexArray::Bind() const
{
	GLCALL(glBindVertexArray(m_RendererID));
}

void VertexArray::UnBind() const
{
	GLCALL(glBindVertexArray(0));
}

VertexArray::VertexArray()
{
	GLCALL(glGenVertexArrays(1, &m_RendererID));
	Bind();
}

VertexArray::~VertexArray()
{
	GLCALL(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& Layout)
{
	this->Bind();
	vb.Bind();
	const auto& elements = Layout.GetElemments();
	unsigned int offset = 0;
	for(unsigned int i =0; i< elements.size();i++)
	{
		const auto& element = elements[i];

		GLCALL(glEnableVertexAttribArray(i));
		GLCALL(glVertexAttribPointer(i, element.count, element.type, element.normalized , Layout.GetStride() ,(const void*) offset));
		offset += element.count * VertextBufferElement::GetSizeOfType(element.type);
	}

}

