#include "TextureProvider.h"

sf::Texture* TextureProvider::load(const std::string &id)
{
    sf::Texture* tex = new sf::Texture();
    if(tex->loadFromFile(id))
        return tex;
    else {
        delete tex;
        return nullptr;
    }
}
