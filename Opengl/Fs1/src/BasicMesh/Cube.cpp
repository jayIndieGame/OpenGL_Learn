#include "Cube.h"


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

void Cube::SetRenderState(Shader& shader, Texture& texture, VertexBufferLayout& layout, VertexArray& vao,
	int TextureSlot) const
{
	m_vb->Bind();
	m_ib->Bind();

	shader.Bind();
	texture.Bind(TextureSlot);
	shader.SetUniform1i("u_Texture", TextureSlot);
	layout.Push<float>(3);
	layout.Push<float>(2);
	layout.Push<float>(3);
	vao.AddBuffer(*m_vb, layout);
	glEnable(GL_DEPTH_TEST);
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

void Cube::SetLocation(glm::vec3 worldLocation)
{
	world_transform.location = worldLocation;
}

void Cube::SetRotation(glm::vec3 worldRotation)
{
	world_transform.Rotation = worldRotation;
}

void Cube::SetScale(glm::vec3 worldSize)
{
	world_transform.Scale = worldSize;
}


glm::mat4 Cube::GetModelMatrix()
{
	glm::mat4 temp_mat = glm::mat4(1.0f);
	temp_mat = glm::translate(temp_mat, world_transform.location);
	temp_mat = glm::rotate(temp_mat, world_transform.Rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	temp_mat = glm::rotate(temp_mat, world_transform.Rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	temp_mat = glm::rotate(temp_mat, world_transform.Rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	temp_mat = glm::scale(temp_mat, world_transform.Scale);
	modelMat = temp_mat;

	return modelMat;
}




