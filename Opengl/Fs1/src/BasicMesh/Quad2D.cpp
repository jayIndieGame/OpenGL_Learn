#include "Quad2D.h"
#include <VertexBufferLayout.h>

Quad2D::Quad2D()
{
	m_vb = new VertexBuffer(GetVertices(), 8 * 4 * sizeof(float));
	m_ib = new IndexBuffer(GetIndices(), 6);
}

Quad2D::~Quad2D()
{
	delete(m_vb);
	delete(m_ib);
}

float* Quad2D::GetVertices()
{
	return vertices;
}

unsigned* Quad2D::GetIndices()
{
	return indices;
}

void Quad2D::SetRenderState(Shader& shader, Texture& diffuseTexture, Texture& specularTexture,
	VertexBufferLayout& layout, VertexArray& vao, int TextureSlot) const
{
	m_vb->Bind();
	m_ib->Bind();

	shader.Bind();
	diffuseTexture.Bind(TextureSlot);
	specularTexture.Bind(TextureSlot + 1);
	shader.SetUniform1i("u_Texture", TextureSlot);
	shader.SetUniform1i("u_Texture", TextureSlot + 1);
	layout.Push<float>(2);
	layout.Push<float>(2);
	vao.AddBuffer(*m_vb, layout);
}

void Quad2D::SetRenderState(Shader& shader, Texture& diffuseTexture, VertexBufferLayout& layout, VertexArray& vao,
	int TextureSlot) const
{
	m_vb->Bind();
	m_ib->Bind();

	shader.Bind();
	diffuseTexture.Bind(TextureSlot);
	shader.SetUniform1i("u_Texture", TextureSlot);
	layout.Push<float>(2);
	layout.Push<float>(2);
	vao.AddBuffer(*m_vb, layout);
}

void Quad2D::SetRenderState(Shader& shader, RuntimeTexture& rt, VertexBufferLayout& layout, VertexArray& vao,
	GLenum attachment) const
{
	m_vb->Bind();
	m_ib->Bind();

	shader.Bind();
	rt.BindFramebuffer(attachment);
	//shader.SetUniform1i("u_Texture", TextureSlot);
	layout.Push<float>(2);
	layout.Push<float>(2);
	vao.AddBuffer(*m_vb, layout);
}

VertexBuffer Quad2D::GetVertexBuffer()
{
	return *m_vb;
}

IndexBuffer Quad2D::GetIndexBuffer()
{
	return *m_ib;
}

IndexBuffer* Quad2D::GetIndexBufferPointer()
{
	return m_ib;
}

void Quad2D::SetLocation(glm::vec3 worldLocation)
{
	BasicMesh::SetLocation(glm::vec3(worldLocation.x,worldLocation.y,0));
}

void Quad2D::SetRotation(glm::vec3 worldRotation)
{
	BasicMesh::SetRotation(glm::vec3(0,0,0));
}

void Quad2D::SetScale(glm::vec3 worldSize)
{
	BasicMesh::SetScale(glm::vec3(worldSize.x, worldSize.y, 0));
}
