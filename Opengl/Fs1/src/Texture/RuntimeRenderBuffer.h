#pragma once
#include <Renderer.h>

class RuntimeRenderbuffer
{
public:
	RuntimeRenderbuffer(unsigned int width, unsigned int height, GLenum format);
	~RuntimeRenderbuffer();

private:
	unsigned int m_RendererID;
	unsigned int m_width, m_height;
	GLenum m_format;

public:
	void BindRenderbuffer(GLenum attachment)const;
	void Bind() const;
	void UnBind() const;

	inline int GetWidth() const { return m_width; }
	inline int GetHeight() const { return m_height; }
};
