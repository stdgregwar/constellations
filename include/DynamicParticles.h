#ifndef DPARTICLESYSTEM_H
#define DPARTICLESYSTEM_H

#include <SFML/Graphics.hpp>
#include <functional>


/**
 * @brief Represent a system of dynamic particless
 */
class DynamicParticles : public sf::Drawable
{
public:
    /**
     * @brief struct containing particle simulation data and link to the  vertex array
     */
    struct Particle
    {
        float phase; ///Time offset of the particle assigned randomly
        float birthtime; ///Timestamp of the particle creation
        sf::Vector2f pos; ///Position of the particle
        sf::Vector2f speed; ///Speed of the particle
        sf::Vertex* vertices; ///Ptr on the array element containing the 6 vertex associated with this particle
    };

    /**
     * @brief struct containing the functions defining the evolutions of particles with
     * respect to time
     */
    struct EvolutionFuncs
    {
        std::function<void(Particle&p, float time, float dt)> move;
        std::function<bool(const Particle&p, float time)> decay;
        std::function<float(const Particle&p, float time)> rotation;
        std::function<float(const Particle&p, float time)> scale;
        std::function<sf::Color(const Particle&p, float time)> color;
        std::function<int(const Particle&p, float time)> frame;
    };

    /**
     * @brief DynamicParticles
     */
    DynamicParticles();

    /**
     * @brief set evolution function for this particle system
     * @param funcs an evolution function struct
     */
    void setFunctions(const EvolutionFuncs& funcs);

    /**
     * @brief uniformDistribution
     * @param rect
     * @param count
     * @param speedRect
     */
    void uniformDistribution(sf::FloatRect rect, unsigned count, sf::FloatRect speedRect);

    /**
     * @brief set the texture for this particle system
     * @param tex a texture ptr (freed on system destruction)
     * @param frames (frame count on sprite atlas, 1 if only one frame)
     */
    void setTexture(const sf::Texture* tex, int frames);

    /**
     * @brief update particle data and vertex array
     */
    void updateParticles() const;

    /**
     * @brief draw particles efficiently using a vertex array
     * @param target
     * @param states
     */
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    /**
     * @brief free texture ptr
     */
    virtual ~DynamicParticles();
private:
    mutable sf::VertexArray mVertexArray;
    mutable std::vector<Particle> mParticles;
    const sf::Texture* mTexture;
    int mFrames;
    EvolutionFuncs mFuncs;
};

#endif // PARTICLESYSTEM_H
