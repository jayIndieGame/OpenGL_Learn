#include "Cube.h"
#include <VertexBufferLayout.h>

Cube::Cube()
{
	m_vb = new VertexBuffer(GetVertices(), 8 * 24 * sizeof(float));
	m_ib = new IndexBuffer(GetIndices(), 36);
}

Cube::~Cube()
{
	delete(m_vb);
	delete(m_ib);
}

float* Cube::GetVertices()
{
	return vertices;
}

unsigned int* Cube::GetIndices()
{
	return indices;
}

void Cube::SetRenderState(Shader& shader, Texture& diffuseTexture,Texture& specularTexture, VertexBufferLayout& layout, VertexArray& vao,
	int TextureSlot) const
{
	m_vb->Bind();
	m_ib->Bind();

	shader.Bind();
	diffuseTexture.Bind(TextureSlot);
	specularTexture.Bind(TextureSlot+1);
	shader.SetUniform1i("u_Texture", TextureSlot);
	shader.SetUniform1i("u_Texture", TextureSlot+1);
	layout.Push<float>(3);
	layout.Push<float>(2);
	layout.Push<float>(3);
	vao.AddBuffer(*m_vb, layout);
}

void Cube::SetRenderState(Shader& shader, Texture& diffuseTexture, VertexBufferLayout& layout, VertexArray& vao,
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

void Cube::SetRenderState(Shader& shader, RuntimeTexture& rt, VertexBufferLayout& layout, VertexArray& vao,
	GLenum attachment) const
{
	m_vb->Bind();
	m_ib->Bind();

	shader.Bind();
	rt.BindFramebuffer(attachment);
	//shader.SetUniform1i("u_Texture", TextureSlot);
	layout.Push<float>(3);
	layout.Push<float>(2);
	layout.Push<float>(3);
	vao.AddBuffer(*m_vb, layout);
}

VertexBuffer Cube::GetVertexBuffer()
{
	return *m_vb;
}

IndexBuffer Cube::GetIndexBuffer()
{
	return *m_ib;
}

IndexBuffer* Cube::GetIndexBufferPointer()
{
	return m_ib;
}


