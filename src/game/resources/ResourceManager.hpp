#pragma once

#include <cassert>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>

namespace rma
{
template <typename Resource, typename Identifier>
class ResourceManager
{
  public:
    ResourceManager() = default;
    ResourceManager(const ResourceManager &) = delete;
    ~ResourceManager() = default;

    ResourceManager &operator=(const ResourceManager &) = delete;

    void load(Identifier id, const std::string &filename);

    template <typename Parameter>
    void load(Identifier id, const std::string &filename,
	      const Parameter &parameter);
    void unload(Identifier id);

    Resource &get(Identifier id);
    const Resource &get(Identifier id) const;

  private:
    void insertResource(Identifier id, std::unique_ptr<Resource> resource);

    std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;
};

#include "ResourceManager.inl"
} // namespace rma
