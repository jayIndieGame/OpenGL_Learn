#include "RuntimeRenderbuffer.h"

RuntimeRenderbuffer::RuntimeRenderbuffer(unsigned int width,unsigned int height,GLenum format)
:m_width(width),m_height(height),m_format(format)
{
	GLCALL(glGenRenderbuffers(1, &m_RendererID));
	GLCALL(glBindRenderbuffer(GL_RENDERBUFFER, m_RendererID));
	//由于渲染缓冲对象通常都是只写的，它们会经常用于深度和模板附件，因为大部分时间我们都不需要从深度和模板缓冲中读取值，只关心深度和模板测试。
	GLCALL(glRenderbufferStorage(GL_RENDERBUFFER,m_format, m_width, m_height));

}

RuntimeRenderbuffer::~RuntimeRenderbuffer()
{
	this->UnBind();
}

void RuntimeRenderbuffer::BindRenderbuffer(GLenum attachment) const
{
	GLCALL(glBindRenderbuffer(GL_RENDERBUFFER, m_RendererID));
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachment, GL_RENDERBUFFER, m_RendererID);
}

void RuntimeRenderbuffer::Bind() const
{
	GLCALL(glBindRenderbuffer(GL_RENDERBUFFER, m_RendererID));
	GLCALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));
	GLCALL(glActiveTexture(GL_TEXTURE0));
}

void RuntimeRenderbuffer::UnBind() const
{
	GLCALL(glBindRenderbuffer(GL_RENDERBUFFER, 0));
}

