#pragma once
#include <Renderer.h>

class RuntimeTexture
{
public:
	RuntimeTexture(unsigned int width, unsigned int height, GLenum internalformat, GLenum format);
	~RuntimeTexture();

private:
	unsigned int m_RendererID ;
	unsigned int m_width, m_height;
	GLenum m_internalformat, m_format;

public:
	void BindFramebuffer(GLenum attachment, unsigned int slot /*= 0*/)const;
	void UnBind() const;
	void TextureRelease()const;

	inline int GetWidth() const { return m_width; }
	inline int GetHeight() const { return m_height; }
};
