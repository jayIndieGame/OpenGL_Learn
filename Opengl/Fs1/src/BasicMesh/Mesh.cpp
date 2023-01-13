#include "Mesh.h"

#include "VertexBufferLayout.h"

Mesh::Mesh(vector<Vertex> vertices, vector<unsigned> indices, vector<Texture> textures):
vertices(vertices),indices(indices),textures(textures)
{
	m_vertexBuffer = std::make_unique<VertexBuffer>(&vertices[0], vertices.size() * sizeof(Vertex));
	m_IndexBuffer = std::make_unique <IndexBuffer>(&indices[0], indices.size() );
	m_vao = std::make_unique <VertexArray>();

	SetRenderState();//初始化时就设置好vao
}

void Mesh::SetRenderState() const
{
	VertexBufferLayout layout;
	layout.Push<float>(3);//0
	layout.Push<float>(3);//1
	layout.Push<float>(2);//2
	layout.Push<float>(3);//3
	layout.Push<float>(3);//4
	layout.Push<int>(4);//5
	layout.Push<float>(4);//6

	m_vao->AddBuffer(*m_vertexBuffer, layout);
}

void Mesh::Draw(Shader& shader) const
{
	shader.Bind();
    // bind appropriate textures
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr = 1;
    unsigned int heightNr = 1;
    for (unsigned int i = 0; i < textures.size(); i++)
    {
		textures[i].Bind(i); // active proper texture unit before binding
        // retrieve texture number (the N in diffuse_textureN)
        string number;
        string name = textures[i].name;
        if (name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if (name == "texture_specular")
            number = std::to_string(specularNr++); // transfer unsigned int to string
        else if (name == "texture_normal")
            number = std::to_string(normalNr++); // transfer unsigned int to string
        else if (name == "texture_height")
            number = std::to_string(heightNr++); // transfer unsigned int to string

		shader.SetUniform1i((name + number).c_str(), i);
    }

	Renderer renderer;
	renderer.Draw(*m_vao, *m_IndexBuffer, shader);

}

IndexBuffer Mesh::GetIndexBuffer() const
{
	return *m_IndexBuffer;
}

VertexArray Mesh::GetVertexArray() const
{
	return *m_vao;
}
