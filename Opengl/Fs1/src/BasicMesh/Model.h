#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"
#include "Texture.h"

using namespace std;

class Model
{
public:
	vector<Texture> texture_loaded;
	vector<Mesh> meshes;
	//string filepath;
	
	Model(string const &path);
	~Model();

	void Draw(Shader& shader);

private:
	string m_directory;

	void LoadModel(string const& path);

	void processNode(aiNode* node, const aiScene* scene);

	Mesh processMesh(aiMesh* mesh, const aiScene* scene);


	vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);

	

};
