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

void VertexArray::AddInstance(const VertexBuffer& vb, const VertexBufferLayout& Layout, int specificShaderIndex)//懒得用template写了反正也是只用float
{

	if(specificShaderIndex != -1)
	{
		m_RecordNumber = specificShaderIndex;
	}

	int tempNum = m_RecordNumber;
	this->Bind();
	GLCALL(glEnableVertexAttribArray(tempNum));
	vb.Bind();
	const auto& instanceElements = Layout.GetInstanceElemments();
	unsigned int offset = 0;

	for (unsigned int i = 0; i < instanceElements.size(); i++)
	{
		const auto& instance = instanceElements[i];

		GLCALL(glEnableVertexAttribArray(tempNum));
		GLCALL(glVertexAttribPointer(tempNum, instance.count, instance.type, instance.normalized, Layout.GetInstanceStride()[i], (const void*)offset));
		offset += instance.count * VertextBufferElement::GetSizeOfType(instance.type);

		GLCALL(glVertexAttribDivisor(instance.index, instance.divisor));
		tempNum++;
		m_RecordNumber++;
	}

}

