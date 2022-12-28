#pragma once

#include "..\\VertexBuffer.h"
#include "..\\VertexBufferLayout.h"
#include "..\\IndexBuffer.h"
#include "..\\VertexArray.h"
#include "..\\Shader.h"
#include "..\\Texture/Texture.h"
#include "..\\vendor/glm/glm.hpp"
#include "..\\vendor/glm/gtc/matrix_transform.hpp"

struct Transform
{
    glm::vec3 location = glm::vec3(0,0,0);
    glm::vec3 Rotation = glm::vec3(0, 0, 0);
    glm::vec3 Scale =  glm::vec3(1, 1, 1);
};


class Cube
{

private:
    int m_id;
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
    glm::mat4 modelMat = glm::mat4(1.0f);

public:

    Transform world_transform;

	Cube();
	~Cube();

    float* GetVertices();

    unsigned int* GetIndices();

    void SetRenderState(Shader& shader,Texture& Diffusetexture,Texture& Speculartexture, VertexBufferLayout& layout,VertexArray& vao,int TextureSlot) const;

    VertexBuffer GetVertexBuffer();
    IndexBuffer GetIndexBuffer();
    IndexBuffer* GetIndexBufferPointer();

    void SetLocation(glm::vec3 worldLocation);
    void SetRotation(glm::vec3 worldRotation);
    void SetScale(glm::vec3 worldSize);
    glm::mat4 GetModelMatrix();

private:

};