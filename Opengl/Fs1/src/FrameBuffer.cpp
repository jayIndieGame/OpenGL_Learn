#include "Renderer.h"
#include "FrameBuffer.h"


FrameBuffer::FrameBuffer()
{
	GLCALL(glGenFramebuffers(1, &m_RendererID));
	GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID));
}

FrameBuffer::~FrameBuffer()
{
	GLCALL(glDeleteFramebuffers(1, &m_RendererID));
}

void FrameBuffer::Bind() const
{
	GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID));
}

void FrameBuffer::UnBind() const
{
	GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}
