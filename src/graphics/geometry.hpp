#pragma once
#include <cstdint>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float3.hpp>
#include <vector>

struct Vertex3D
{
	float x;
	float y;
	float z;
};

struct NormalMappedVertex
{
	glm::vec3 pos;
	glm::vec2 uv;
	glm::vec3 normal;
	glm::vec3 tangent;
	float sign;
};

std::vector<Vertex3D> GenerateGrid(float size, float step);
std::vector<Vertex3D> GenerateSphere(uint32_t sector_count, uint32_t stack_count);
std::array<NormalMappedVertex, 6> MakeWall(std::array<glm::vec3, 2> pos, float height = 8.0f);
