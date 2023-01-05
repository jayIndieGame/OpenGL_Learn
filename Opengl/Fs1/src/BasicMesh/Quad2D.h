#pragma once
#include "BasicMesh.h"

class Quad2D:public BasicMesh
{
private:
    //int m_id;
    float vertices[4 * 4]
        = {
        //position     //coordinates      
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f

    };
    unsigned int indices[6]
        =
    {
        2,1,0,
        0,3,2
    };

    VertexBuffer* m_vb;
    IndexBuffer* m_ib;


public:
    Quad2D();
    ~Quad2D() override;

	float* GetVertices() override;
	unsigned* GetIndices() override;
	void SetRenderState(Shader& shader, Texture& diffuseTexture, Texture& specularTexture, VertexBufferLayout& layout,
		VertexArray& vao, int TextureSlot) const override;
    void SetRenderState(Shader& shader, Texture& diffuseTexture, VertexBufferLayout& layout,
        VertexArray& vao, int TextureSlot) const override;
    void SetRenderState(Shader& shader, RuntimeTexture& rt, VertexBufferLayout& layout, VertexArray& vao,
        GLenum attachment) const override;

	VertexBuffer GetVertexBuffer() override;
	IndexBuffer GetIndexBuffer() override;
	IndexBuffer* GetIndexBufferPointer() override;

    /**
     * \brief 0-1之间。按照屏幕百分比移动
     * \param worldLocation 只考虑x，y分量
     */
    void SetLocation(glm::vec3 worldLocation) override;
    /**
     * \brief 无效方法
     * \param worldRotation 不能设置旋转
     */
    void SetRotation(glm::vec3 worldRotation) override;
    /**
     * \brief 默认scale为整个屏幕，所以最好只缩小
     * \param worldSize 只考虑x，y分量
     */
    void SetScale(glm::vec3 worldSize) override;

};
