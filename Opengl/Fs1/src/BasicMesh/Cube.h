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
    { 0, 1, 2,
    2, 1, 3,
    4, 5, 6,
    6, 7, 5,
    8, 9, 10,
    10, 9, 11,
    12, 13, 14,
    14, 13, 15,
    16, 17, 18,
    18, 17, 19,
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

    VertexBuffer GetVertexBuffer() override;
    IndexBuffer GetIndexBuffer() override;
    IndexBuffer* GetIndexBufferPointer() override;


private:

};