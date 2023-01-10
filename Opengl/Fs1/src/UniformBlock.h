#pragma once
#include "glm/gtc/type_ptr.hpp"

class UniformBlock
{
private:
	unsigned int m_RendererID;
	int m_bindpoint;
public:
	UniformBlock(const void* data, unsigned int size);
	UniformBlock(unsigned int size);
	~UniformBlock();

	void Bind(unsigned int bindPoint);
	void Bind(unsigned int bindPoint,unsigned int offset,unsigned int size);
	void ChangeSubBlock(unsigned int offset,unsigned int size, float const* ptr);
	void UnBind();





};