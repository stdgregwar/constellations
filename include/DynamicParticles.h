#ifndef DPARTICLESYSTEM_H
#define DPARTICLESYSTEM_H

#include <SFML/Graphics.hpp>
#include <functional>

class DynamicParticles : public sf::Drawable
{
public:
    struct Particle
    {
        float phase;
        float birthtime;
        sf::Vector2f pos;
        sf::Vector2f speed;
        sf::Vertex* vertices;
    };

    struct EvolutionFuncs
    {
        std::function<void(Particle&p, float time, float dt)> move;
        std::function<bool(const Particle&p, float time)> decay;
        std::function<float(const Particle&p, float time)> rotation;
        std::function<float(const Particle&p, float time)> scale;
        std::function<sf::Color(const Particle&p, float time)> color;
        std::function<int(const Particle&p, float time)> frame;
    };

    DynamicParticles();
    void setFunctions(const EvolutionFuncs& funcs);
    void uniformDistribution(sf::FloatRect rect, unsigned count, sf::FloatRect speedRect);
    void setTexture(const sf::Texture* tex, int frames);
    void updateParticles() const;
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    virtual ~DynamicParticles();
private:


    mutable sf::VertexArray mVertexArray;
    mutable std::vector<Particle> mParticles;
    const sf::Texture* mTexture;
    int mFrames;
    EvolutionFuncs mFuncs;
};

#endif // PARTICLESYSTEM_H
