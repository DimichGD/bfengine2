#pragma once

#define BF_BEGIN_NAMESPACE namespace bf {
#define BF_END_NAMESPACE }

#define BF_BEGIN_GL_NAMESPACE namespace gl {
#define BF_END_GL_NAMESPACE }

#define BF_BEGIN_VK_NAMESPACE namespace vk {
#define BF_END_VK_NAMESPACE }

#define BF_NON_COPYABLE(Class) \
	Class(const Class &) = delete; \
	Class &operator=(const Class &) = delete;

#define BF_NON_MOVABLE(Class) \
	Class(Class &&) = delete; \
	Class &operator=(Class &&) = delete;
