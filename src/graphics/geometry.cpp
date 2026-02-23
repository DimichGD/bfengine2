#include "geometry.hpp"
#include "core/log.hpp"
#include <cmath>
#include <glm/ext/scalar_constants.hpp>
#include <glm/geometric.hpp>

std::vector<Vertex3D> GenerateGrid(float size, float step)
{
	float grid_half_size = size / 2.0f;
	std::vector<Vertex3D> verts;
	verts.reserve(size_t(size) / 16 * 4 + 4);

	for (int i = -grid_half_size; i <= grid_half_size; i += 2)
	{
		float fi = i;

		if (i == 0)
			continue;

		verts.push_back({ fi, 0.0f,  grid_half_size });
		verts.push_back({ fi, 0.0f, -grid_half_size });

		verts.push_back({ -grid_half_size, 0.0f, fi });
		verts.push_back({  grid_half_size, 0.0f, fi });
	}

	verts.push_back({ -grid_half_size, 0.0f, 0.0f });
	verts.push_back({  grid_half_size, 0.0f, 0.0f });

	verts.push_back({ 0.0f, 0.0f,  grid_half_size });
	verts.push_back({ 0.0f, 0.0f, -grid_half_size });

	//Mesh mesh;
	//mesh.vbo = device->CreateBuffer(GPUBuffer::Type::VERTEX, verts);

	/*uint32_t grid_vert_count = verts.size();
	mesh.surfaces = {
		{ {}, 0, grid_vert_count - 4 },
		{ {}, grid_vert_count - 4, 2 },
		{ {}, grid_vert_count - 2, 2 }
	};*/

	return verts;
}

std::vector<Vertex3D> GenerateSphere(uint32_t sector_count, uint32_t stack_count)
{
	float R = 1.0f;

	float PI = glm::pi<float>();
	float sector_step = 2 * PI / float(sector_count);
	float stack_step = PI / float(stack_count);

	float x, y, z, xy;
	float sector_angle, stack_angle;
	std::vector<Vertex3D> verts;
	std::vector<uint32_t> indices;

	for(uint32_t i = 0; i <= sector_count; i++)
	{
		stack_angle = PI / 2 - i * stack_step;
		xy = R * cosf(stack_angle);
		z = R * sinf(stack_angle);

		for(uint32_t j = 0; j <= sector_count; j++)
		{
			sector_angle = j * sector_step;
			x = xy * cosf(sector_angle);
			y = xy * sinf(sector_angle);

			verts.push_back({ x, y, z });
		}
	}

	uint32_t k1, k2;
	for(uint32_t i = 0; i < stack_count; i++)
	{
		k1 = i * (sector_count + 1);
		k2 = k1 + sector_count + 1;

		for(uint32_t j = 0; j < sector_count; j++, k1++, k2++)
		{
			if (i != 0)
			{
				indices.push_back(k1);
				indices.push_back(k2);
				indices.push_back(k1 + 1);
			}

			if (i != stack_count - 1)
			{
				indices.push_back(k1 + 1);
				indices.push_back(k2);
				indices.push_back(k2 + 1);
			}

			/*line_indices.push_back(k1);
			line_indices.push_back(k2);
			if (i != 0)
			{
				line_indices.push_back(k1);
				line_indices.push_back(k1 + 1);
			}*/
		}
	}

	std::vector<Vertex3D> verts2;
	for (uint32_t i: indices)
		verts2.push_back(verts[i]);

	return verts2;
}

std::array<NormalMappedVertex, 6> MakeWall(std::array<glm::vec3, 2> pos, float height)
{
	std::array<NormalMappedVertex, 6> result {};

	// assert pos[0].y == pos[1].y
	glm::vec3 normal = glm::cross(glm::normalize(pos[1] - pos[0]), { 0.0f, 1.0f, 0.0f });
	glm::vec3 tangent = glm::normalize(pos[1] - pos[0]);
	float scale_x = glm::length(pos[1] - pos[0]) / 8.0f;

	result[0] =
	{
		{ pos[0].x, pos[0].y + height, pos[0].z },
		{ 0.0f, 0.0f },
		normal,
		tangent,
		1.0f,
	};

	result[1] =
	{
		{ pos[0].x, pos[0].y, pos[0].z },
		{ 0.0f, 1.0f },
		normal,
		tangent,
		1.0f,
	};

	result[2] =
	{
		{ pos[1].x, pos[1].y + height, pos[1].z },
		{ scale_x, 0.0f },
		normal,
		tangent,
		1.0f,
	};

	result[3] = result[2];
	result[4] = result[1];

	result[5] =
	{
		{ pos[1].x, pos[1].y, pos[1].z },
		{ scale_x, 1.0f },
		normal,
		tangent,
		1.0f,
	};

	return result;
}
