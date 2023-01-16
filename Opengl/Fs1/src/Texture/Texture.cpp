#include "Texture.h"
#include "..//vendor/stb_image/stb_image.h"

Texture::Texture(const std::string& path,const std::string& name,bool enableMinimap,bool sRGB) :m_RendererID(0), m_FilePath(path), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_BPP(0), name(name)
{
	stbi_set_flip_vertically_on_load(1);
	GLCALL(glGenTextures(1, &m_RendererID));
	m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 0);
	if (m_LocalBuffer)
	{
		GLenum internalFormat;
		GLenum dataFormat;
		if (m_BPP == 1)
			internalFormat = dataFormat = GL_RED;
		else if (m_BPP == 3)
		{
			internalFormat = sRGB ? GL_SRGB : GL_RGB;
			dataFormat = GL_RGB;
		}
		else if (m_BPP == 4)
		{
			internalFormat = sRGB ? GL_SRGB_ALPHA : GL_RGBA;
			dataFormat = GL_RGBA;
		}

		GLCALL(glBindTexture(GL_TEXTURE_2D, m_RendererID));
		GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Width, m_Height, 0, dataFormat, GL_UNSIGNED_BYTE, m_LocalBuffer));//最后一个参数可以给0，就是只开辟空间不存数据。
		if (enableMinimap)
		{
			GLCALL(glGenerateMipmap(GL_TEXTURE_2D));
			GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
			GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
			GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
			GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		}

		else {
			GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
			GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
			GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
			GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
		}

		
		GLCALL(glBindTexture(GL_TEXTURE_2D, 0));
		stbi_image_free(m_LocalBuffer);//已经传给gpu了 就释放调buffer，如果想保存，设置成类成员变量即可
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(m_LocalBuffer);
	}
}

Texture::~Texture()
{

	//GLCALL(glDeleteTextures(1, &m_RendererID));
	
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

void Texture::TextureRelease() const
{
	GLCALL(glDeleteTextures(1, &m_RendererID));
}

