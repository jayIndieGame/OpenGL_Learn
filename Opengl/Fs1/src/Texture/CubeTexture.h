#pragma once

#include "..\\Renderer.h"


class CubeTexture
{
private:
	unsigned int m_RendererID;
	std::vector<std::string> m_FilePaths;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;

public:
	std::string name;
	CubeTexture(const std::vector<std::string> faces);
	~CubeTexture();

	void Bind(unsigned int slot = 0)const;
	void UnBind() const;
	void TextureRelease()const;

	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }
	inline std::vector<std::string> GetPath() const { return m_FilePaths; }


};
