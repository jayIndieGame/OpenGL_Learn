#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Texture.h>
#include <Shader.h>
#include <string>
#include <vector>
using namespace std;

#define MAX_BONE_INFLUENCE 4

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
	glm::vec3 Tangent;
	glm::vec3 Bitangent;

	int m_BoneIDs[MAX_BONE_INFLUENCE];
	float m_Weights[MAX_BONE_INFLUENCE];
};


class Mesh
{
	public:
		vector<Vertex>			vertices;
		vector<unsigned int>	indices;
		vector<Texture>			textures;

		Mesh(vector<Vertex> vertices,vector<unsigned int> indices,vector<Texture> textures);
		void SetRenderState() const;
		void Draw(Shader& shader)const;
		IndexBuffer GetIndexBuffer() const;
		VertexArray GetVertexArray() const;
		VertexArray* GetVertexArrayPointer() const;
		IndexBuffer* GetIndexBufferPointer() const;


private:
	std::unique_ptr <VertexBuffer> m_vertexBuffer;
	std::unique_ptr <IndexBuffer> m_IndexBuffer;
	std::unique_ptr <VertexArray> m_vao;

};
