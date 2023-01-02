#include "Plane.h"
#include <VertexBufferLayout.h>

Plane::Plane()
{
	m_vb = new VertexBuffer(GetVertices(), 8 * 4 * sizeof(float));
	m_ib = new IndexBuffer(GetIndices(), 6);
}

Plane::~Plane()
{
	delete(m_vb);
	delete(m_ib);
}

float* Plane::GetVertices()
{
	return vertices;
}

unsigned* Plane::GetIndices()
{
	return indices;
}

void Plane::SetRenderState(Shader& shader, Texture& diffuseTexture, Texture& specularTexture,
	VertexBufferLayout& layout, VertexArray& vao, int TextureSlot) const
{
	m_vb->Bind();
	m_ib->Bind();

	shader.Bind();
	diffuseTexture.Bind(TextureSlot);
	specularTexture.Bind(TextureSlot + 1);
	shader.SetUniform1i("u_Texture", TextureSlot);
	shader.SetUniform1i("u_Texture", TextureSlot + 1);
	layout.Push<float>(3);
	layout.Push<float>(2);
	layout.Push<float>(3);
	vao.AddBuffer(*m_vb, layout);
}

void Plane::SetRenderState(Shader& shader, Texture& diffuseTexture, VertexBufferLayout& layout, VertexArray& vao,
	int TextureSlot) const
{
	m_vb->Bind();
	m_ib->Bind();

	shader.Bind();
	diffuseTexture.Bind(TextureSlot);
	shader.SetUniform1i("u_Texture", TextureSlot);
	layout.Push<float>(3);
	layout.Push<float>(2);
	layout.Push<float>(3);
	vao.AddBuffer(*m_vb, layout);
}

VertexBuffer Plane::GetVertexBuffer()
{
	return *m_vb;
}

IndexBuffer Plane::GetIndexBuffer()
{
	return *m_ib;
}

IndexBuffer* Plane::GetIndexBufferPointer()
{
	return m_ib;
}
