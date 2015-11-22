#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include <SFML/Graphics.hpp>

/**
 * @brief The StaticParticles class
 */
class StaticParticles : public sf::Drawable
{
public:
    StaticParticles();
    void uniformDistribution(sf::FloatRect rect, unsigned count);
    void setTexture(const sf::Texture* tex, int frames);
    void updateTexCoords() const;
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    virtual ~StaticParticles();
private:
    struct Particle
    {
        float phase;
        sf::Vertex* vertices;
    };

    sf::VertexArray mVertexArray;
    mutable std::vector<Particle> mParticles;
    const sf::Texture* mTexture;
    int mFrames;
};

#endif // PARTICLESYSTEM_H
