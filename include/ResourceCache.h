#ifndef RESOURCECACHE_H
#define RESOURCECACHE_H

#include <string>
#include <map>

template<class R, class I> //Resource and identifier
/**
 * @brief Abstract class for loading resources of type R given an identifier of type I
 */
class ResourceProvider
{
public:
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
        typename Resources::iterator it = mResources.find(id);
        if(it != mResources.end()) { //Resource already in cache !
            it->second.refcount++;
            return it->second.ptr;
        } else {
            R* res = mProvider->load(id);
            if(res) { //Add only if not nullptr
                mResources[id] = {1,res};
            }
            return res;
        }
    }

    /**
     * @brief free resource with given id
     * @param id
     */
    void free(const I& id)
    {
        typename Resources::iterator it = mResources.find(id);
        if(it != mResources.end())
        {
            if(!--it->second.refcount) //If --refcount == 0
            {
                delete it->second.ptr;
                mResources.erase(it);
            }
        }
    }

    /**
     * @brief free resource given it's ptr
     * @param r
     */
    void free(const R* r)
    {
        for(typename Resources::iterator it = mResources.begin(); it != mResources.end(); it++)
        {
            if(it->second.ptr == r)
            {
                if(!--it->second.refcount)
                {
                    delete it->second.ptr;
                    mResources.erase(it);
                    break;
                }
            }
        }
    }

    ~ResourceCache(){
        for(typename Resources::iterator it = mResources.begin(); it != mResources.end(); it++)
        {
            delete it->second.ptr;
        }
        delete mProvider;
    }

private:
    Resources mResources;
    ResourceProvider<R,I>* mProvider;
};



#endif // RESOURCECACHE_H

