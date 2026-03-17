#pragma once
#include "graphics/types.hpp"

BF_BEGIN_NAMESPACE

template<typename HandleType, typename ResourceType>
class ResourceArray
{
public:
	ResourceArray()
	{
		//indices.reserve(128);
		resources.reserve(128);
	}

	HandleType PutResource(ResourceType resource)
	{
		if (free_list.empty())
		{
			resources.push_back({ resource, 0 });
			return { { uint32_t(resources.size() - 1) } };
		}
		else
		{
			uint32_t index = free_list.back();
			free_list.pop_back();

			resources[index].resource = resource;

			return { { index, resources[index].gen } };
		}
	}

	void RemoveResource(HandleType handle) // TODO: add deleter?
	{
		if (resources.at(handle.index).gen != handle.gen)
			throw "Resource generation mismatch";

		free_list.push_back(handle.index);
		resources.at(handle.index).gen += 1;
	}

	ResourceType &operator[](HandleType handle)
	{
		if (resources.at(handle.index).gen != handle.gen)
			throw "Resource generation mismatch";

		return resources[handle.index].resource;
	}

	ResourceType &GetResouce(HandleType handle, uint16_t offset)
	{
		if (resources.at(handle.index).gen != handle.gen)
			throw "Resource generation mismatch";

		if (resources.at(handle.index + offset).gen != handle.gen)
			throw "Resource generation mismatch";

		return resources[handle.index + offset].resource;
	}

	/*ResourceType &operator[](HandleType handle, uint16_t offset)
	{
		if (resources.at(handle.index).gen != handle.gen)
			throw "Resource generation mismatch";

		if (resources.at(handle.index + offset).gen != handle.gen)
			throw "Resource generation mismatch";

		return resources[handle.index + offset].resource;
	}*/

private:
	struct ResourceWithGen
	{
		ResourceType resource;
		uint16_t gen = 0;
	};

	std::vector<ResourceWithGen> resources;
	std::vector<uint32_t> free_list;
};

BF_END_NAMESPACE
