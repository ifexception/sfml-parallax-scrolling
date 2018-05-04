template <typename Resource, typename Identifier>
void ResourceManager<Resource, Identifier>::load(Identifier id,
    const std::string &filename)
{
    auto resource = std::make_unique<Resource>();
    auto resourceLoaded = resource->loadFromFile(filename);
    if (!resourceLoaded) {
        throw std::runtime_error("Error - Unable to load resource: " +
            filename);
    }

    insertResource(id, std::move(resource));
}

template <typename Resource, typename Identifier>
template <typename Parameter>
void ResourceManager<Resource, Identifier>::load(Identifier id,
    const std::string &filename, const Parameter &parameter)
{
    auto resource = std::make_unique<Resource>();
    auto resourceLoaded = resource->loadFromFile(filename, parameter);
    if (!resourceLoaded) {
        throw std::runtime_error("Error - Unable to load resource: " +
            filename);
    }

    insertResource(id, std::move(resource));
}

template <typename Resource, typename Identifier>
void ResourceManager<Resource, Identifier>::unload(Identifier id)
{
    auto resourceToUnload = mResourceMap.find(id);
    assert(found != mResourceMap.end());

    mResourceMap.erase(resourceToUnload);
}

template <typename Resource, typename Identifier>
Resource& ResourceManager<Resource, Identifier>::get(Identifier id)
{
    auto found = mResourceMap.find(id);
    assert(found != mResourceMap.end());

    return *found->second;
}

template <typename Resource, typename Identifier>
const Resource& ResourceManager<Resource, Identifier>::get(Identifier id) const
{
    auto found = mResourceMap.find(id);
    assert(found != mResourceMap.end());

    return *found->second;
}

template <typename Resource, typename Identifier>
void ResourceManager<Resource, Identifier>::insertResource(Identifier id,
    std::unique_ptr<Resource> resource)
{
    auto inserted = mResourceMap.insert(std::make_pair(id, std::move(resource)));
    assert(inserted.second);
}
