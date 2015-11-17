#ifndef TEXTUREPROVIDER_H
#define TEXTUREPROVIDER_H

#include "ResourceCache.h"
#include <string>
#include <SFML/Graphics/Texture.hpp>

class TextureProvider : public ResourceProvider<sf::Texture,std::string>
{
    sf::Texture* load(const std::string &id);
};

typedef ResourceCache<sf::Texture,std::string> TextureCache;

#endif // TEXTUREPROVIDER_H

