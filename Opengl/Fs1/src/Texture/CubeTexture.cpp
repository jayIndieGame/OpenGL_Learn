#include "CubeTexture.h"
#include "..//vendor/stb_image/stb_image.h"

CubeTexture::CubeTexture(const std::vector<std::string> faces) :m_RendererID(0), m_FilePaths(faces), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_BPP(0), name(name)
{
    stbi_set_flip_vertically_on_load(0);
	GLCALL(glGenTextures(1, &m_RendererID));
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_RendererID);

	int width, height, nrChannels;

    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
            );
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

}

CubeTexture::~CubeTexture()
{

	//GLCALL(glDeleteTextures(1, &m_RendererID));
	
}

void CubeTexture::Bind(unsigned int slot /*= 0*/) const
{
    GLCALL(glActiveTexture(GL_TEXTURE0+slot));
	GLCALL(glBindTexture(GL_TEXTURE_CUBE_MAP, m_RendererID));
}

void CubeTexture::UnBind() const
{
	GLCALL(glBindTexture(GL_TEXTURE_2D, 0));
}

void CubeTexture::TextureRelease() const
{
	GLCALL(glDeleteTextures(1, &m_RendererID));
}

