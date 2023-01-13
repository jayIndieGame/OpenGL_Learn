#pragma once
#include <vector>
#include <unordered_map>
#include <GL/glew.h>
#include "Renderer.h"

struct VertextBufferElement
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
			case GL_FLOAT:				return 4;
			case GL_UNSIGNED_INT:		return 4;
			case GL_UNSIGNED_BYTE:		return 1;
			case GL_INT:				return 4;
		}
		ASSERT(false);
		return 0;
	}

};

struct VertextBufferInstanceElement
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;
	unsigned int index;
	unsigned int divisor;
	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT:				return 4;
		case GL_UNSIGNED_INT:		return 4;
		case GL_UNSIGNED_BYTE:		return 1;
		case GL_INT:				return 4;
		}
		ASSERT(false);
		return 0;
	}

	bool operator ==(const VertextBufferInstanceElement& other) const
	{
		return this->type == other.type && this->count == other.count && this->normalized == other.normalized && this->index == other.index && this->divisor == other.divisor;
	}

	static size_t myHash(const VertextBufferInstanceElement& self) noexcept
	{
		static 	std::hash<std::string> hash_str;
		return hash_str(std::to_string(self.index));
	}
};


class VertexBufferLayout
{
private:
	std::vector<VertextBufferElement> m_Elements;
	unsigned int m_Stride;

	std::vector<VertextBufferInstanceElement> m_InstanceElements;
	std::unordered_map<VertextBufferInstanceElement,unsigned int> m_InstanceStrideDic;
public:
	VertexBufferLayout() :m_Stride(0) {};
	~VertexBufferLayout();

	template<typename T>
	void Push(unsigned int count)
	{
		static_assert(false);
	}

	template<typename T>
	void PushInstance(unsigned int count,unsigned int index,unsigned int divisor)
	{
		static_assert(false);
	}

	template<>
	void Push<float>(unsigned int count)
	{
		m_Elements.push_back({GL_FLOAT,count,GL_FALSE});
		m_Stride += count * VertextBufferElement::GetSizeOfType(GL_FLOAT);
		glLoadIdentity();
	}

	template<>
	void PushInstance<float>(unsigned int count, unsigned int index, unsigned int divisor)
	{
		VertextBufferInstanceElement v = { GL_FLOAT,count,GL_FALSE,index,divisor };
		m_InstanceElements.push_back(v);
		m_InstanceStrideDic[v] = count * VertextBufferElement::GetSizeOfType(GL_FLOAT);
	}

	template<>
	void Push<unsigned int>(unsigned int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_INT,count,GL_FALSE });
		m_Stride += count * VertextBufferElement::GetSizeOfType(GL_UNSIGNED_INT) ;
	}

	template<>
	void Push<int>(unsigned int count)
	{
		m_Elements.push_back({ GL_INT,count,GL_FALSE });
		m_Stride += count * VertextBufferElement::GetSizeOfType(GL_INT);
	}

	template<>
	void Push<unsigned char>(unsigned int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_BYTE,count,GL_TRUE });
		m_Stride += count * VertextBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE) ;
	}

	/**
	 * \brief 
	 * \param count 不需要这个count，1就行 其他的数说不定还会有问题没验证
	 */
	template<>
	void PushInstance<glm::mat4>(unsigned int count, unsigned int index, unsigned int divisor)
	{
		VertextBufferInstanceElement v = { GL_FLOAT,count *4,GL_FALSE,index,divisor };
		m_InstanceElements.push_back(v);
		m_InstanceStrideDic[v] = count * sizeof(glm::mat4);
	}

	inline const std::vector<VertextBufferElement> GetElemments() const { return m_Elements; };
	inline const std::vector<VertextBufferInstanceElement> GetInstanceElemments() const { return m_InstanceElements; };
	inline unsigned int GetStride() const { return m_Stride; }
	inline unsigned int GetInstanceStride(VertextBufferInstanceElement element) const { return m_InstanceStrideDic.find(element)->second; }
};