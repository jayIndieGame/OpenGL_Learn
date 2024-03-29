#pragma once
#include <GL/glew.h>
#include <iostream>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCALL(x) GLClearError();\
x;\
ASSERT(GLLogCall(#x,__FILE__,__LINE__))

void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);


class Renderer
{
public:
	void Clear() const;
	void Draw(const VertexArray& va,const IndexBuffer& ib,const Shader& shader) const;
	void DrawPoints(const VertexArray& va,const IndexBuffer& ib,const Shader& shader) const;
	void DrawInstance(const VertexArray& va,const IndexBuffer& ib,const Shader& shader,unsigned int count) const;

};