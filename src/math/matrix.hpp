#pragma once
#include "core/defines.hpp"
#include <glm/mat4x4.hpp>

BF_BEGIN_NAMESPACE

void FastInverse(glm::mat4 &matrix); // FIXME: is it fast though?

BF_END_NAMESPACE
