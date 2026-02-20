#include "matrix.hpp"

BF_BEGIN_NAMESPACE

void FastInverse(glm::mat4 &matrix)
{
	std::swap(matrix[0][1], matrix[1][0]);
	std::swap(matrix[0][2], matrix[2][0]);
	std::swap(matrix[1][2], matrix[2][1]);

	float x = matrix[0][0] * matrix[3][0] + matrix[1][0] * matrix[3][1] + matrix[2][0] * matrix[3][2];
	float y = matrix[0][1] * matrix[3][0] + matrix[1][1] * matrix[3][1] + matrix[2][1] * matrix[3][2];
	float z = matrix[0][2] * matrix[3][0] + matrix[1][2] * matrix[3][1] + matrix[2][2] * matrix[3][2];

	matrix[3][0] = -x;
	matrix[3][1] = -y;
	matrix[3][2] = -z;
}

BF_END_NAMESPACE
