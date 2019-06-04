#include "ResourceManager.hpp"

template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string& filename) {
  // Create a new pointer to the resource
  std::unique_ptr<Resource> resource(new Resource());

  // Error checking and loading
  if (!resource->loadFromFile(filename)) {
    throw std::runtime_error("ResourceHolder::load - failed to load " + filename);
  }

  // Adds to the map with the ID
  auto inserted = mResourceMap.insert(std::make_pair(id, std::move(resource)));

  // Error Checking
  assert(inserted.second);
}

template <typename Resource, typename Identifier>
Resource& ResourceHolder<Resource, Identifier>::get(Identifier id) {
  auto found = mResourceMap.find(id);
  assert(found != mResourceMap.end());
  return *found->second;
}

template <typename Resource, typename Identifier>
const Resource& ResourceHolder<Resource, Identifier>::get(Identifier id) const {
  auto found = mResourceMap.find(id);
  assert(found != mResourceMap.end());
  return *found->second;
}

template <typename Resource, typename Identifier>
template <typename Parameter>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string& filename, const Parameter& secondParam)
{
	// Create and load resource
	std::unique_ptr<Resource> resource(new Resource());
	if (!resource->loadFromFile(filename, secondParam))
		throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);

	// If loading successful, insert resource to map
	insertResource(id, std::move(resource));
}
