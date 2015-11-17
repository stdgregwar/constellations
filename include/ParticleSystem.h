#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include <SFML/Graphics.hpp>

class ParticleSystem : public sf::Drawable
{
public:
    ParticleSystem();
    void uniformDistribution(sf::FloatRect rect, unsigned count);
    void setTexture(const sf::Texture& tex, int frames);
    void updateTexCoords() const;
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    virtual ~ParticleSystem();
private:
    struct Particle
    {
        float phase;
        sf::Vertex* vertices;
    };

    sf::VertexArray mVertexArray;
    mutable std::vector<Particle> mParticles;
    sf::Texture mTexture;
    int mFrames;
};

#endif // PARTICLESYSTEM_H
