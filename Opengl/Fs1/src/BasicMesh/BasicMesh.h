#pragma once
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"
#include "Texture.h"
#include "RuntimeTexture.h"

struct Transform
{
	glm::vec3 location = glm::vec3(0, 0, 0);
	glm::vec3 Rotation = glm::vec3(0, 0, 0);
	glm::vec3 Scale = glm::vec3(1, 1, 1);
};

class BasicMesh
{
protected:

	int m_id;
	glm::mat4 modelMat = glm::mat4(1.0f);

public:
	Transform world_transform;

	BasicMesh(){};

	virtual ~BasicMesh(){};

public:
	virtual float* GetVertices() = 0;
	virtual unsigned int* GetIndices()=0;

	virtual void SetRenderState(Shader& shader, Texture& diffuseTexture, Texture& specularTexture, VertexBufferLayout& layout, VertexArray& vao, int TextureSlot) const = 0;
	virtual void SetRenderState(Shader& shader, Texture& diffuseTexture, VertexBufferLayout& layout, VertexArray& vao, int TextureSlot) const = 0;
	virtual void SetRenderState(Shader& shader, RuntimeTexture& rt, VertexBufferLayout& layout, VertexArray& vao, GLenum attachment, unsigned int TextureSlot) const = 0;

	virtual VertexBuffer GetVertexBuffer() = 0;
	virtual IndexBuffer GetIndexBuffer() = 0;
	virtual IndexBuffer* GetIndexBufferPointer()=0;

	virtual void SetLocation(glm::vec3 worldLocation);
	virtual void SetRotation(glm::vec3 worldRotation);
	virtual void SetScale(glm::vec3 worldSize);
	glm::mat4 GetModelMatrix();
};
