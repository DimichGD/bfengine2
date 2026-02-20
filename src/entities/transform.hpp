#pragma once
#include "core/defines.hpp"
#include "core/log.hpp"
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>
#include <vector>
#include <span>
#include <cassert>

BF_BEGIN_NAMESPACE

struct Transform
{
	glm::quat rot { 1.0f, 0.0f, 0.0f, 0.0f };
	glm::vec3 pos { 0.0f, 0.0f, 0.0f };
};

class MotionState
{
public:
	void Reserve(size_t count)
	{
		prev.reserve(count);
		curr.reserve(count);
	}

	size_t Allocate()
	{
		prev.emplace_back();
		curr.emplace_back();

		return curr.size() - 1;
	}

	void NextFrame()
	{
		std::copy(curr.begin(), curr.end(), prev.begin());
	}

	void InterpolateTo(float a, std::span<glm::mat4> matrices)
	{
		assert(matrices.size() >= curr.size());

		for (size_t i = 0; i < curr.size(); i++)
		{
			Transform &x = prev[i];
			Transform &y = curr[i];

			glm::vec3 pos = glm::mix(x.pos, y.pos, a);
			glm::quat rot = glm::mix(x.rot, y.rot, a);

			matrices[i] = glm::mat4_cast(glm::normalize(rot)); // TODO: is normalization necessary
			matrices[i][3] = glm::vec4(pos, 1.0f);
		}
	}

	Transform &GetTransform(size_t index)
	{
		return curr[index];
	}

private:
	std::vector<Transform> prev;
	std::vector<Transform> curr;
};

BF_END_NAMESPACE
