#ifndef RESOURCECACHE_H
#define RESOURCECACHE_H

#include <string>
#include <map>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <functional>

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
    ResourceCache(std::function<R*(const I&)> loader) : mLoader(loader) {}

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
            R* res = mLoader(id); //Load res using given function
            if(res) { //Add only if not nullptr
                mResources[id] = {1,res};
            }
            return res;
        }
    }

    void put(const I& id, R* val){
        mResources[id] = {1,val};
    }

    R* loadOnly(const I& id)
    {
        return mLoader(id);
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
    }

private:
    Resources mResources;
    std::function<R*(const I&)> mLoader;
};

//Useful caches :
typedef ResourceCache<sf::Texture, std::string> TextureCache;
typedef ResourceCache<sf::Font, std::string> FontCache;
typedef ResourceCache<sf::SoundBuffer, std::string> SoundBufferCache;


#endif // RESOURCECACHE_H

