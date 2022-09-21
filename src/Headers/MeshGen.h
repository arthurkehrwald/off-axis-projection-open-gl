#pragma once
#include "Mesh.h"

#include <vector>
#include <glm/glm.hpp>

namespace MeshGen
{
	void addQuadToMesh(
		const glm::vec3& a,
		const glm::vec3& b,
		const glm::vec3& c,
		const glm::vec3& d,
		bool invertVertexOrder,
		const glm::vec3& normal,
		const glm::vec4& UVs,
		std::vector<float>& meshCoords,
		std::vector<int>& meshIndices);
	Mesh createCubeMesh(bool invertNormals = false);
	Mesh createTriangleMesh();
	Mesh createQuadMesh();
}