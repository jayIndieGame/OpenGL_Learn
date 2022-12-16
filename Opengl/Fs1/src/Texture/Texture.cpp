#include "Texture.h"
#include "..//vendor/stb_image/stb_image.h"

Texture::Texture(const std::string& path):m_RendererID(0),m_FilePath(path),m_LocalBuffer(nullptr),m_Width(0),m_Height(0),m_BPP(0)
{
	stbi_set_flip_vertically_on_load(1);
	m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);


	GLCALL(glGenTextures(1, &m_RendererID));
	GLCALL(glBindTexture(GL_TEXTURE_2D, m_RendererID));

	//���ĸ���ָ����ָ����õ�һ����ɫ������
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));//��С��ʱ�������ʽ
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));//�Ŵ��ʱ�������ʽ
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));//s�����tile��ʽ
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));//t����tile��ʽ

	GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));//���һ���������Ը�0������ֻ���ٿռ䲻�����ݡ�
	GLCALL(glBindTexture(GL_TEXTURE_2D, 0));

	if (m_LocalBuffer)
		stbi_image_free(m_LocalBuffer);//�Ѿ�����gpu�� ���ͷŵ�buffer������뱣�棬���ó����Ա��������
}

Texture::~Texture()
{
	GLCALL(glDeleteTextures(1, &m_RendererID));
	
}

void Texture::Bind(unsigned int slot /*= 0*/) const
{
	GLCALL(glActiveTexture(GL_TEXTURE0 + slot));
	GLCALL(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}

void Texture::UnBind() const
{
	GLCALL(glBindTexture(GL_TEXTURE_2D, 0));
}

