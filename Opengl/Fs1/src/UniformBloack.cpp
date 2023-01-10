#include "Renderer.h"
#include "UniformBlock.h"


UniformBlock::UniformBlock(const void* data, unsigned int size)
{
	GLCALL(glGenBuffers(1, &m_RendererID));
	GLCALL(glBindBuffer(GL_UNIFORM_BUFFER, m_RendererID));
	GLCALL(glBufferData(GL_UNIFORM_BUFFER, size, data, GL_STATIC_DRAW));

}

UniformBlock::UniformBlock(unsigned size)
{
	GLCALL(glGenBuffers(1, &m_RendererID));
	GLCALL(glBindBuffer(GL_UNIFORM_BUFFER, m_RendererID));
	GLCALL(glBufferData(GL_UNIFORM_BUFFER, size, NULL, GL_STATIC_DRAW));
}

UniformBlock::~UniformBlock()
{
	GLCALL(glDeleteBuffers(1, &m_RendererID));
}

void UniformBlock::Bind(unsigned int bindPoint) 
{
	m_bindpoint = bindPoint;
	GLCALL(glBindBufferBase(GL_UNIFORM_BUFFER,bindPoint, m_RendererID));
}

void UniformBlock::Bind(unsigned bindPoint, unsigned offset, unsigned size)
{
	m_bindpoint = bindPoint;
	GLCALL(glBindBufferRange(GL_UNIFORM_BUFFER, bindPoint, m_RendererID,offset,size));
}

void UniformBlock::ChangeSubBlock(unsigned int offset,unsigned size, float const* ptr)
{
	if(m_bindpoint == -1)
	{
		std::cout << "bind uniform block object first" << std::endl;
		return;
	}

	Bind(m_bindpoint);
	GLCALL(glBufferSubData(GL_UNIFORM_BUFFER, offset , sizeof(glm::mat4), ptr));
}

void UniformBlock::UnBind()
{
	m_bindpoint = -1;
	GLCALL(glBindBuffer(GL_UNIFORM_BUFFER, 0));
}
