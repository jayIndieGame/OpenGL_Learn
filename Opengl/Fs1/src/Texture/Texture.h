#pragma once

#include "..\\Renderer.h"


class Texture
{
private:
	unsigned int m_RendererID;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;

public:
	std::string name;
	Texture(const std::string& path, const std::string& name = "u_Texture",bool enableMiniMap = false);
	~Texture();

	void Bind(unsigned int slot = 0)const;
	void UnBind() const;
	void TextureRelease()const;

	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }
	inline std::string GetPath() const { return m_FilePath; }


};
