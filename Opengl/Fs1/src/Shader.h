#pragma once
#include <string>
#include <unordered_map>

struct ShaderProgramSource
{
	std::string vertexShader;
	std::string fragmentShader;
};


class Shader
{
public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void UnBind() const;

	void SetUniform4f(const std::string& name,float v0,float v1,float v2,float v3);
	void SetUniform1i(const std::string& name, int value);


private:
	unsigned int m_RendererID;
	std::string m_Filepath;
	//caching
	std::unordered_map<std::string, int> m_UniformLocationCache;
	int GetUniformLocation(const std::string& name);

	unsigned int CompileShader(unsigned int type, const std::string& source);

	unsigned int CreateShader(const std::string VertextShader, const std::string FragmentShader);

	ShaderProgramSource ParseShader(const std::string filepath);

};

