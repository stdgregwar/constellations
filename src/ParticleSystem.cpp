#include "ParticleSystem.h"
#include <random>
#include "Core.h"

using namespace std;

ParticleSystem::ParticleSystem()
{
    mVertexArray.setPrimitiveType(sf::Triangles);
}

void ParticleSystem::uniformDistribution(sf::FloatRect rect, unsigned count)
{
    default_random_engine gen;
    uniform_real_distribution<float> vertical(rect.top,rect.top+rect.height);
    uniform_real_distribution<float> horizontal(rect.left,rect.left+rect.width);
    uniform_real_distribution<float> size(mTexture.getSize().y*0.5,mTexture.getSize().y*2);
    uniform_real_distribution<float> phase(0,4);
    mParticles.reserve(count);
    mVertexArray.resize(count*6);
    for(int i = 0; i < count; i++)
    {
        float s = mTexture.getSize().y*2;
        sf::FloatRect r(horizontal(gen),vertical(gen),s,s);

        int j=i*6;

        mVertexArray[j].position = {r.left,r.top}; //First triangle
        mVertexArray[j+1].position = {r.left,r.top+r.height};
        mVertexArray[j+2].position = {r.left+r.width,r.top};
        mVertexArray[j+3].position = {r.left+r.width,r.top}; //Second triangle
        mVertexArray[j+4].position = {r.left,r.top+r.height};
        mVertexArray[j+5].position = {r.left+r.width,r.top+r.height};



        mParticles.push_back({phase(gen),&mVertexArray[i*6]});
    }
}

void ParticleSystem::updateTexCoords() const
{
    float time = Core::get().time();
    float frameWidth = mTexture.getSize().x/mFrames;
    for(Particle& p : mParticles)
    {
        int frame = int(time+p.phase)%mFrames;

        sf::FloatRect uv(frame*frameWidth,0,frameWidth,mTexture.getSize().y);

        p.vertices[0].texCoords = {uv.left,uv.top}; //First triangle
        p.vertices[1].texCoords = {uv.left,uv.top+uv.height};
        p.vertices[2].texCoords = {uv.left+uv.width,uv.top};
        p.vertices[3].texCoords = {uv.left+uv.width,uv.top}; //Second triangle
        p.vertices[4].texCoords = {uv.left,uv.top+uv.height};
        p.vertices[5].texCoords = {uv.left+uv.width,uv.top+uv.height};
    }
}

void ParticleSystem::setTexture(const sf::Texture& tex, int frames)
{
    mTexture = tex;
    mFrames = frames;
}

void ParticleSystem::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    updateTexCoords();
    target.draw(mVertexArray,sf::RenderStates(&mTexture));
}
