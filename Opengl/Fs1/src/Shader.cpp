#include "Shader.h"
#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Renderer.h"

enum class ShaderType
{
	NONE = -1, VERTEX = 0, FRAGMENT = 1

};



Shader::Shader(const std::string& filepath):m_Filepath(filepath),m_RendererID(0)
{
	ShaderProgramSource source = ParseShader(filepath);
	std::cout << "vertex shader" << std::endl;
	std::cout << source.vertexShader << std::endl;
	std::cout << "fragment shader" << std::endl;
	std::cout << source.fragmentShader << std::endl;

	m_RendererID = CreateShader(source.vertexShader, source.fragmentShader);
	
}

Shader::~Shader()
{
	GLCALL(glDeleteProgram(m_RendererID));
}

void Shader::Bind() const
{
	GLCALL(glUseProgram(m_RendererID));
}

void Shader::UnBind() const
{
	GLCALL(glUseProgram(0));
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	GLCALL(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

void Shader::SetUniform3f(const std::string& name, float v0, float v1, float v2)
{
	GLCALL(glUniform3f(GetUniformLocation(name), v0, v1, v2));
}

void Shader::SetUniform3f(const std::string& name, glm::vec3 vec3)
{
	GLCALL(glUniform3f(GetUniformLocation(name), vec3.x,vec3.y,vec3.z));
}

void Shader::SetUniform1i(const std::string& name, int value)
{
	GLCALL(glUniform1i(GetUniformLocation(name), value));
}

void Shader::SetUniform1f(const std::string& name, float value)
{
	GLCALL(glUniform1f(GetUniformLocation(name), value));
}


void Shader::SetUniform4fMat(const std::string& name, const glm::mat4& matrix)
{
	GLCALL(glUniformMatrix4fv(GetUniformLocation(name),1,GL_FALSE,&matrix[0][0]));
}

void Shader::SetUniform1b(const std::string& name, bool condition)
{
	GLCALL(glUniform1i(GetUniformLocation(name), condition));
}

void Shader::SetUniformBlock(const std::string& name, unsigned bindpoint)
{
	unsigned int uniformBlockIndex = glGetUniformBlockIndex(m_RendererID, "Matrices");
	if(uniformBlockIndex == -1)
	{
		std::cout << "Warning:uniform '" << name << "'doesn't exist." << std::endl;
	}
	GLCALL(glUniformBlockBinding(m_RendererID, uniformBlockIndex, bindpoint));
}

GLint Shader::GetUniformLocation(const std::string& name) const
{
	if(m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
	{
		return m_UniformLocationCache[name];
	}

	GLCALL(unsigned int location = glGetUniformLocation(m_RendererID,name.c_str()));
	if (location == -1)
		std::cout << "Warning:uniform '" << name << "'doesn't exist." << std::endl;
		m_UniformLocationCache[name] = location;
	return location;
}

ShaderProgramSource Shader::ParseShader(const std::string filepath)
{
	std::ifstream stream(filepath);

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;
	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
			{
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos)
			{
				type = ShaderType::FRAGMENT;
			}
		}
		else
		{
			ss[(int)type] << line << '\n';
		}
	}

	return { ss[0].str(),ss[1].str() };
}

//��ʾ���͵Ĳ���������GLenum,Ҳ��typedef unsigned int GLenum;д�޷������α��������ط����øú���ʱ��Ҫ����glew
unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);//����id����source�ļ���1��һ�ݣ�src��shader�ļ���nullptr�Ƕ�ȡ��nullptr��ֹͣ
	glCompileShader(id);

	//���
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));//��ջ������̶����ȴ��info
		glGetShaderInfoLog(id, length, &length, message);//���ȥ,��Ҫ����length��ԭ��δ֪
		std::cout << message << std::endl;
		glDeleteShader(id);

		return 0;
	}


	return id;
}

unsigned int Shader::CreateShader(const std::string VertextShader, const std::string FragmentShader)
{

	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, VertextShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, FragmentShader);

	glAttachShader(program, vs);

	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}
