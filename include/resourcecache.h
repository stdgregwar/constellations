#ifndef RESOURCECACHE_H
#define RESOURCECACHE_H

#include <string>
#include <map>

template<class R, class I> //Resource and identifier
class ResourceProvider
{
    /**
     * @brief abstract load for provider
     * @param identifier of resource, usually string
     * @return ptr to resource or nullptr if resource could'nt be found
     */
    virtual R* load(const I& id) = 0;
};

template<class R, class I> //Templated resource type and provider
/**
 * @brief The ResourceCache class allow to cache resources and load them trough a resource provider
 */
class ResourceCache
{
    struct Resource
    {
        unsigned refcount;
        R* ptr;
    };
    typedef std::map<I,Resource> Resources;
public:
    /**
     * @brief Init resource cache with given provider, take ptr ownership
     * @param provider
     */
    ResourceCache(ResourceProvider<R,I>* provider) : mProvider(provider) {}

    /**
     * @brief getResource with given ID
     * @param id
     * @return ptr to resource or nullptr if resource could'nt be found
     */
    R* get(const I& id)
    {
        return nullptr;
    }

    /**
     * @brief free resource with given id
     * @param id
     */
    void free(const I& id)
    {

    }

    /**
     * @brief free resource given it's ptr
     * @param r
     */
    void free(R* r)
    {

    }

private:


    Resources mResources;
    ResourceProvider<R,I> mProvider;
};



#endif // RESOURCECACHE_H

