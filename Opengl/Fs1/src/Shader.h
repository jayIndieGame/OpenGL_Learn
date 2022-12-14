#pragma once
#include <GL/glew.h>
#include <string>
#include <unordered_map>
#include <glm/glm.hpp>
#include <unordered_map>


struct ShaderProgramSource
{
	std::string vertexShader;
	std::string fragmentShader;
	std::string geometryShader;
};


class Shader
{
public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void UnBind() const;

	void SetUniform4f(const std::string& name,float v0,float v1,float v2,float v3);
	void SetUniform3f(const std::string& name, float v0, float v1, float v2);
	void SetUniform3f(const std::string& name, glm::vec3 vec3);

	void SetUniform1i(const std::string& name, int value);
	void SetUniform1f(const std::string& name, float value);
	void SetUniform4fMat(const std::string& name,const glm::mat4& matrix);

	void SetUniform1b(const std::string& name, bool condition);

	void SetUniformBlock(const std::string& name, unsigned int bindpoint);


private:
	unsigned int m_RendererID;
	std::string m_Filepath;
	//caching
	mutable std::unordered_map<std::string, int> m_UniformLocationCache;
	GLint GetUniformLocation(const std::string& name) const;

	unsigned int CompileShader(unsigned int type, const std::string& source);

	unsigned int CreateShader(const std::string VertextShader, const std::string FragmentShader,const std::string GeometryShader);

	ShaderProgramSource ParseShader(const std::string filepath);

};

