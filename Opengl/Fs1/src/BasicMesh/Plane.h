#pragma once
#include "BasicMesh.h"

class Plane:public BasicMesh
{
private:
    //int m_id;
    float vertices[6 * 8]
        = {
        //position                    //coordinates       //normal
         50.0f, -5.0f,  50.0f,        1.0f, 0.0f,         0.0f,1.0f,0.0f,
        -50.0f, -5.0f,  50.0f,        0.0f, 0.0f,         0.0f,1.0f,0.0f,
        -50.0f, -5.0f, -50.0f,        0.0f, 1.0f,         0.0f,1.0f,0.0f,
         50.0f, -5.0f, -50.0f,        1.0f, 1.0f,         0.0f,1.0f,0.0f

    };
    unsigned int indices[6]
        =
    {
        0,1,2,
        2,3,0
    };

    VertexBuffer* m_vb;
    IndexBuffer* m_ib;


public:
    Plane();
    ~Plane() override;

	float* GetVertices() override;
	unsigned* GetIndices() override;
	void SetRenderState(Shader& shader, Texture& diffuseTexture, Texture& specularTexture, VertexBufferLayout& layout,
		VertexArray& vao, int TextureSlot) const override;
    void SetRenderState(Shader& shader, Texture& diffuseTexture, VertexBufferLayout& layout,
        VertexArray& vao, int TextureSlot) const override;
	VertexBuffer GetVertexBuffer() override;
	IndexBuffer GetIndexBuffer() override;
	IndexBuffer* GetIndexBufferPointer() override;
};
