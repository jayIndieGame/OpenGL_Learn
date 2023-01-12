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

		GLCALL(glEnableVertexAttribArray(m_RecordNumber));
		GLCALL(glVertexAttribPointer(m_RecordNumber, element.count, element.type, element.normalized , Layout.GetStride() ,(const void*) offset));
		offset += element.count * VertextBufferElement::GetSizeOfType(element.type);
		m_RecordNumber++;
	}
}

void VertexArray::AddInstance(const VertexBuffer& vb, unsigned int count, unsigned index, unsigned divisor)//懒得用template写了反正也是只用float
{

	this->Bind();
	GLCALL(glEnableVertexAttribArray(m_RecordNumber));
	vb.Bind();
	GLCALL(glVertexAttribPointer(m_RecordNumber, count, GL_FLOAT, GL_FALSE, count * VertextBufferElement::GetSizeOfType(GL_FLOAT), (void*)0));
	GLCALL(glVertexAttribDivisor(index, divisor));
	m_RecordNumber++;
}

