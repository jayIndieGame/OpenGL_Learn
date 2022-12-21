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
	float vertices[21*8]
	= {
        //position              //vertex color      //texture coordinates
        -50.0f,50.0f,50.0f,     1.0f,1.0f,1.0f,     0.0f,1.0f,//左上前
        50.0f,50.0f,50.0f,      1.0f,1.0f,1.0f,     1.0f,1.0f,//右上前
        -50.0f,-50.0f,50.0f,    1.0f,1.0f,1.0f,     0.0f,0.0f,//左下前
        50.0f,-50.0f,50.0f,     1.0f,1.0f,1.0f,     1.0f,0.0f,//右下前

        50.0f,50.0f,50.0f,      1.0f,1.0f,1.0f,     0.0f,1.0f,//右上前
        50.0f,50.0f,-50.0f,     1.0f,1.0f,1.0f,     1.0f,1.0f,//右上后
        50.0f,-50.0f,50.0f,     1.0f,1.0f,1.0f,     0.0f,0.0f,//右下前
        50.0f,-50.0f,-50.0f,    1.0f,1.0f,1.0f,     1.0f,0.0f,//右下后

        50.0f,50.0f,-50.0f,     1.0f,1.0f,1.0f,     0.0f,1.0f,//右上后
        -50.0f,50.0f,-50.0f,    1.0f,1.0f,1.0f,     1.0f,1.0f,//左上后
        50.0f,-50.0f,-50.0f,    1.0f,1.0f,1.0f,     0.0f,0.0f,//右下后
        -50.0f,-50.0f,-50.0f,   1.0f,1.0f,1.0f,     1.0f,0.0f,//左下后

        -50.0f,50.0f,-50.0f,    1.0f,1.0f,1.0f,     0.0f,1.0f,//左上后
        -50.0f,50.0f,50.0f,     1.0f,1.0f,1.0f,     1.0f,1.0f,//左上前
        -50.0f,-50.0f,-50.0f,   1.0f,1.0f,1.0f,     0.0f,0.0f,//左下后
        -50.0f,-50.0f,50.0f,    1.0f,1.0f,1.0f,     1.0f,0.0f,//左下前

        //-50.0f,50.0f,-50.0f,  1.0f,1.0f,1.0f,     0.0f,1.0f,//左上后 12
        //50.0f,50.0f,-50.0f,   1.0f,1.0f,1.0f,     1.0f,1.0f,//右上后 5
        -50.0f,50.0f,50.0f,     1.0f,1.0f,1.0f,     0.0f,0.0f,//左上前
         50.0f,50.0f,50.0f,     1.0f,1.0f,1.0f,     1.0f,0.0f,//右上前 4

         -50.0f,-50.0f,-50.0f,   1.0f,1.0f,1.0f,     0.0f,1.0f,//左下后
         50.0f,-50.0f,-50.0f,    1.0f,1.0f,1.0f,     1.0f,1.0f,//右下后
         //50.0f,-50.0f,50.0f,   1.0f,1.0f,1.0f,     0.0f,0.0f,//左下前 2
         50.0f,-50.0f,50.0f,     1.0f,1.0f,1.0f,     0.0f,1.0f,//右下前

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
    16, 12, 5,
    5, 16, 17,
    18, 19, 2,
    2, 19, 20 };

    VertexBuffer* m_vb;
    IndexBuffer* m_ib;
    glm::mat4 modelMat = glm::mat4(1.0f);

public:

    Transform world_transform;

	Cube();
	~Cube();

    float* GetVertices();

    unsigned int* GetIndices();

    void SetRenderState(Shader& shader,Texture& texture, VertexBufferLayout& layout,VertexArray& vao,int TextureSlot) const;

    VertexBuffer GetVertexBuffer();
    IndexBuffer GetIndexBuffer();

    void SetLocation(glm::vec3 worldLocation);
    void SetRotation(glm::vec3 worldRotation);
    void SetScale(glm::vec3 worldSize);
    glm::mat4 GetModelMatrix();

private:

};