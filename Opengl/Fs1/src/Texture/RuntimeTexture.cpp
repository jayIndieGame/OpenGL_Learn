#include "RuntimeTexture.h"

RuntimeTexture::RuntimeTexture(unsigned int width,unsigned int height,GLenum internalformat,GLenum format)
:m_width(width),m_height(height),m_internalformat(internalformat),m_format(format)
{
	GLCALL(glGenTextures(1, &m_RendererID));
	GLCALL(glBindTexture(GL_TEXTURE_2D, m_RendererID));
	//给纹理的data参数传递了NULL。对于这个纹理，我们仅仅分配了内存而没有填充它。填充这个纹理将会在我们渲染到帧缓冲之后来进行。
	GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, internalformat, width, height, 0, format, GL_UNSIGNED_BYTE, NULL));

	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	GLCALL(glBindTexture(GL_TEXTURE_2D, 0));

}

RuntimeTexture::~RuntimeTexture()
{
}

void RuntimeTexture::BindFramebuffer(GLenum attachment, unsigned int slot /*= 0*/) const
{
	GLCALL(glActiveTexture(GL_TEXTURE0 + slot));
	GLCALL(glBindTexture(GL_TEXTURE_2D, m_RendererID));
	GLCALL(glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, m_RendererID, 0));//0是minimapleve
}

void RuntimeTexture::Bind(GLenum attachment, unsigned slot) const
{
	GLCALL(glActiveTexture(GL_TEXTURE0 + slot));
	GLCALL(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}

void RuntimeTexture::UnBind() const
{
	GLCALL(glBindTexture(GL_TEXTURE_2D, 0));
}

void RuntimeTexture::TextureRelease() const
{
	GLCALL(glDeleteTextures(1, &m_RendererID));
}
