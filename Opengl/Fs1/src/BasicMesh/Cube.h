#pragma once
#include "BasicMesh.h"

class Cube:public BasicMesh
{

private:
    //int m_id;
	float vertices[24*8]
	= {
        //position                //coordinates       //normal
        -50.0f,50.0f,50.0f,       0.0f,1.0f,          0.0f,0.0f,-1.0f,//左上前
        50.0f,50.0f,50.0f,        1.0f,1.0f,          0.0f,0.0f,-1.0f,//右上前
        -50.0f,-50.0f,50.0f,      0.0f,0.0f,          0.0f,0.0f,-1.0f,//左下前
        50.0f,-50.0f,50.0f,       1.0f,0.0f,          0.0f,0.0f,-1.0f,//右下前

        50.0f,50.0f,50.0f,        0.0f,1.0f,          1.0f,0.0f,0.0f,//右上前
        50.0f,50.0f,-50.0f,       1.0f,1.0f,          1.0f,0.0f,0.0f,//右上后
        50.0f,-50.0f,50.0f,       0.0f,0.0f,          1.0f,0.0f,0.0f,//右下前
        50.0f,-50.0f,-50.0f,      1.0f,0.0f,          1.0f,0.0f,0.0f,//右下后

        50.0f,50.0f,-50.0f,       0.0f,1.0f,          0.0f,0.0f,1.0f,//右上后
        -50.0f,50.0f,-50.0f,      1.0f,1.0f,          0.0f,0.0f,1.0f,//左上后
        50.0f,-50.0f,-50.0f,      0.0f,0.0f,          0.0f,0.0f,1.0f,//右下后
        -50.0f,-50.0f,-50.0f,     1.0f,0.0f,          0.0f,0.0f,1.0f,//左下后

        -50.0f,50.0f,-50.0f,      0.0f,1.0f,          -1.0f,0.0f,0.0f,//左上后
        -50.0f,50.0f,50.0f,       1.0f,1.0f,          -1.0f,0.0f,0.0f,//左上前
        -50.0f,-50.0f,-50.0f,     0.0f,0.0f,          -1.0f,0.0f,0.0f,//左下后
        -50.0f,-50.0f,50.0f,      1.0f,0.0f,          -1.0f,0.0f,0.0f,//左下前

        -50.0f,50.0f,-50.0f,      0.0f,1.0f,          0.0f,1.0f,0.0f,//左上后 
        50.0f,50.0f,-50.0f,       1.0f,1.0f,          0.0f,1.0f,0.0f,//右上后 
        -50.0f,50.0f,50.0f,       0.0f,0.0f,          0.0f,1.0f,0.0f,//左上前
         50.0f,50.0f,50.0f,       1.0f,0.0f,          0.0f,1.0f,0.0f,//右上前 

         -50.0f,-50.0f,-50.0f,     0.0f,1.0f,         0.0f,-1.0f,0.0f,//左下后
         50.0f,-50.0f,-50.0f,      1.0f,1.0f,         0.0f,-1.0f,0.0f,//右下后
         -50.0f,-50.0f,50.0f,       0.0f,0.0f,         0.0f,-1.0f,0.0f,//左下前 
         50.0f,-50.0f,50.0f,       1.0f,0.0f,         0.0f,-1.0f,0.0f,//右下前

    };
    unsigned int indices[36]
        =
    { 2, 1, 0,
    3, 1, 2,
    6, 5, 4,
    6, 7, 5,
    10, 9, 8,
    11, 9, 10,
    14, 13, 12,
    15, 13, 14,
    18, 17, 16,
    19, 17, 18,
    20, 21, 22,
    22, 21, 23 };

    VertexBuffer* m_vb;
    IndexBuffer* m_ib;


public:

	Cube();
	~Cube() override;

    float* GetVertices() override;

    unsigned int* GetIndices() override;

    void SetRenderState(Shader& shader,Texture& diffuseTexture,Texture& specularTexture, VertexBufferLayout& layout,VertexArray& vao,int TextureSlot) const override;
    void SetRenderState(Shader& shader,Texture& diffuseTexture,VertexBufferLayout& layout,VertexArray& vao,int TextureSlot) const override;
    void SetRenderState(Shader& shader, RuntimeTexture& rt, VertexBufferLayout& layout, VertexArray& vao,GLenum attachment) const override;

    VertexBuffer GetVertexBuffer() override;
    IndexBuffer GetIndexBuffer() override;
    IndexBuffer* GetIndexBufferPointer() override;



private:

};