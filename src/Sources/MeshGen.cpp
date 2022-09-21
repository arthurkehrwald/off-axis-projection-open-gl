#include "MeshGen.h"

void MeshGen::addQuadToMesh(
	const glm::vec3& a,
	const glm::vec3& b,
	const glm::vec3& c,
	const glm::vec3& d,
	bool invertVertexOrder,
	const glm::vec3& normal,
	const glm::vec4& UVs,
	std::vector<float>& meshCoords,
	std::vector<int>& meshIndices)
{
	// A---B
	// |   |
	// C---D
	float quadCoords[]
	{
		a.x, a.y, a.z, normal.x, normal.y, normal.z, UVs.x, UVs.w,
		b.x, b.y, b.z, normal.x, normal.y, normal.z, UVs.z, UVs.w,
		c.x, c.y, c.z, normal.x, normal.y, normal.z, UVs.x, UVs.y,
		d.x, d.y, d.z, normal.x, normal.y, normal.z, UVs.z, UVs.y
	};

	for (const float quadCoord : quadCoords)
	{
		meshCoords.push_back(quadCoord);
	}

	const int valuesPerVertex = 8;
	const int vertexCount = meshCoords.size() / valuesPerVertex;

	// A, C, B
	// B, C, D
	int quadIndices[]
	{
		vertexCount - 4, vertexCount - 2, vertexCount - 3,
		vertexCount - 3, vertexCount - 2, vertexCount - 1
	};

	if (invertVertexOrder)
	{
		for (int i = 5; i >= 0; i--)
		{
			meshIndices.push_back(quadIndices[i]);
		}
	}
	else
	{
		for (int i = 0; i <= 5; i++)
		{
			meshIndices.push_back(quadIndices[i]);
		}
	}
}

Mesh MeshGen::createCubeMesh()
{
	std::vector<float> meshCoords;
	std::vector<int> meshIndices;

	// Vertex positions
	glm::vec3 topA(0.5f, 0.5f, 0.5f);
	glm::vec3 topB(-0.5f, 0.5f, 0.5f);
	glm::vec3 topC(0.5f, 0.5f, -0.5f);
	glm::vec3 topD(-0.5f, 0.5f, -0.5f);
	glm::vec3 botA(0.5f, -0.5f, 0.5f);
	glm::vec3 botB(-0.5f, -0.5f, 0.5f);
	glm::vec3 botC(0.5f, -0.5f, -0.5f);
	glm::vec3 botD(-0.5f, -0.5f, -0.5f);

	const auto texCoords = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

	// Sides
	addQuadToMesh(topA, topB, topC, topD, false, glm::vec3(0.0f, 1.0f, 0.0f), texCoords, meshCoords, meshIndices);
	addQuadToMesh(topA, topB, botA, botB, true, glm::vec3(0.0f, 0.0f, 1.0f), texCoords, meshCoords, meshIndices);
	addQuadToMesh(topC, topD, botC, botD, false, glm::vec3(0.0f, 0.0f, -1.0f), texCoords, meshCoords, meshIndices);
	addQuadToMesh(topA, topC, botA, botC, false, glm::vec3(1.0f, 0.0f, 0.0f), texCoords, meshCoords, meshIndices);
	addQuadToMesh(topB, topD, botB, botD, true, glm::vec3(-1.0f, 0.0f, 0.0f), texCoords, meshCoords, meshIndices);
	addQuadToMesh(botA, botB, botC, botD, true, glm::vec3(0.0f, -1.0f, 0.0f), texCoords, meshCoords, meshIndices);

	return Mesh(meshCoords, Mesh::VertexArrayFormat::posNormalUV, meshIndices);
}

Mesh MeshGen::createTriangleMesh()
{
	std::vector<float> vertices =
	{
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.25f,
		0.5f, -0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 0.25f, 0.25f,
		-0.5f, 0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f
	};

	std::vector<int> indices = { 0, 1, 2 };

	return Mesh(vertices, Mesh::VertexArrayFormat::posNormalUV, indices);
}

Mesh MeshGen::createQuadMesh()
{
	glm::vec3 tlPos = glm::vec3(0.5f, 0.5f, 0.0f);
	glm::vec3 trPos = glm::vec3(-0.5f, 0.5f, 0.0f);
	glm::vec3 blPos = glm::vec3(0.5f, -0.5f, 0.0f);
	glm::vec3 brPos = glm::vec3(-0.5f, -0.5f, 0.0f);
	bool invertVertexOrder = false;
	glm::vec3 normal = glm::vec3(0.0f, 0.0f, -1.0f);
	const auto texCoords = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
	std::vector<float> meshCoords;
	std::vector<int> meshIndices;
	addQuadToMesh(tlPos, trPos, blPos, brPos, invertVertexOrder, normal, texCoords, meshCoords, meshIndices);
	return Mesh(meshCoords, Mesh::VertexArrayFormat::posNormalUV, meshIndices);
}