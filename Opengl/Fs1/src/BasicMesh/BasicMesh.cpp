#include "BasicMesh.h"

void BasicMesh::SetLocation(glm::vec3 worldLocation)
{
	world_transform.location = worldLocation;
}

void BasicMesh::SetRotation(glm::vec3 worldRotation)
{
	world_transform.Rotation = worldRotation;
}

void BasicMesh::SetScale(glm::vec3 worldSize)
{
	world_transform.Scale = worldSize;
}


glm::mat4 BasicMesh::GetModelMatrix()
{
	glm::mat4 temp_mat = glm::mat4(1.0f);
	temp_mat = glm::translate(temp_mat, world_transform.location);
	temp_mat = glm::rotate(temp_mat, world_transform.Rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	temp_mat = glm::rotate(temp_mat, world_transform.Rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	temp_mat = glm::rotate(temp_mat, world_transform.Rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	temp_mat = glm::scale(temp_mat, world_transform.Scale);
	modelMat = temp_mat;

	return modelMat;
}



