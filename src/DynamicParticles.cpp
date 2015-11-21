#include "DynamicParticles.h"
#include <random>
#include "Core.h"

using namespace std;

DynamicParticles::DynamicParticles()
{
    mVertexArray.setPrimitiveType(sf::Triangles);
}

void DynamicParticles::uniformDistribution(sf::FloatRect rect, unsigned count, sf::FloatRect speedRect)
{
    default_random_engine gen;
    uniform_real_distribution<float> vertical(rect.top,rect.top+rect.height);
    uniform_real_distribution<float> horizontal(rect.left,rect.left+rect.width);
    uniform_real_distribution<float> verticalSpeed(speedRect.top,speedRect.top+speedRect.height);
    uniform_real_distribution<float> horizontalSpeed(speedRect.left,speedRect.left+speedRect.width);

    uniform_real_distribution<float> phase(0,4);
    mParticles.reserve(count);
    mVertexArray.resize(count*6);
    for(int i = 0; i < count; i++)
    {   
        sf::Vector2f pos = {horizontal(gen),vertical(gen)};
        sf::Vector2f speed = {verticalSpeed(gen),verticalSpeed(gen)};

        /*int j=i*6;

        mVertexArray[j].position = {r.left,r.top}; //First triangle
        mVertexArray[j+1].position = {r.left,r.top+r.height};
        mVertexArray[j+2].position = {r.left+r.width,r.top};
        mVertexArray[j+3].position = {r.left+r.width,r.top}; //Second triangle
        mVertexArray[j+4].position = {r.left,r.top+r.height};
        mVertexArray[j+5].position = {r.left+r.width,r.top+r.height};*/

        mParticles.push_back({phase(gen),Core::get().time(),pos,speed,&mVertexArray[i*6]});
    }
}


void DynamicParticles::setFunctions(const EvolutionFuncs& funcs)
{
    mFuncs = funcs;
}

void DynamicParticles::updateParticles() const
{
    int nonDecayed = 0;
    float time = Core::get().time();
    float dt = 1/60.f;
    int frameWidth = mTexture->getSize().x/mFrames;
    float hemiWidth = mTexture->getSize().y*0.5f;
    float hemiHeight = mTexture->getSize().y*0.5f;
    sf::Vector2f sa,sb,sc,sd;
    sa = {-hemiWidth,-hemiHeight};
    sb = {-hemiWidth,hemiHeight};
    sc = {hemiWidth,hemiHeight};
    sd = {hemiWidth,-hemiHeight};
    for(Particle& p : mParticles)
    {
        float partTime = time-p.birthtime;//+p.phase;
        //TexCoords :
        int frame = mFuncs.frame ? mFuncs.frame(p,time) : 1;
        sf::FloatRect uv(frame*frameWidth,0,frameWidth,mTexture->getSize().y);
        p.vertices[0].texCoords = {uv.left,uv.top}; //First triangle
        p.vertices[1].texCoords = {uv.left,uv.top+uv.height};
        p.vertices[2].texCoords = {uv.left+uv.width,uv.top};
        p.vertices[3].texCoords = {uv.left+uv.width,uv.top}; //Second triangle
        p.vertices[4].texCoords = {uv.left,uv.top+uv.height};
        p.vertices[5].texCoords = {uv.left+uv.width,uv.top+uv.height};

        //Position :
        if(mFuncs.move) mFuncs.move(p,partTime,dt);
        //scale
        float scale = mFuncs.scale ? mFuncs.scale(p,partTime) : 1;
        //rot
        float rotation = mFuncs.rotation ? mFuncs.rotation(p,partTime) : 0;
        sf::Transform t;
        t.translate(p.pos);
        t.rotate(rotation);
        t.scale(scale,scale);
         //Particle transform
        sf::Vector2f a,b,c,d;
        a = t.transformPoint(sa);
        b = t.transformPoint(sb);
        c = t.transformPoint(sc);
        d = t.transformPoint(sd);
        p.vertices[0].position = a; //First triangle
        p.vertices[1].position = b;
        p.vertices[2].position = d;
        p.vertices[3].position = d; //Second triangle
        p.vertices[4].position = b;
        p.vertices[5].position = c;

        if(mFuncs.color)
        {
            sf::Color col = mFuncs.color(p,time);
            for(int i = 0; i < 6; i++)
            {
                p.vertices[i].color = col;
            }
        }
        if(mFuncs.decay && !mFuncs.decay)
            nonDecayed++;
    }
    /*if(nonDecayed == 0) //Opti : destruct particle and vertex array if simulation ended
    {
        mParticles.clear();
        mVertexArray.clear();
    }*/
}

void DynamicParticles::setTexture(const sf::Texture* tex, int frames)
{
    mTexture = tex;
    mFrames = frames;
}

void DynamicParticles::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    updateParticles();
    target.draw(mVertexArray,sf::RenderStates(mTexture));
}

DynamicParticles::~DynamicParticles()
{
    Core::get().textureCache().free(mTexture);
}
