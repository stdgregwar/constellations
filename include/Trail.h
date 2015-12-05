#ifndef TRAIL_H
#define TRAIL_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <vector>

class Trail : public sf::Drawable
{
public:
    Trail(float width, float dt, size_t size);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    bool addPoint(const sf::Vector2f& p);
    void empty();
private:
    size_t mStart,mEnd;
    float mDt;
    float mLastTime;
    float mWidth;
    sf::Vector2f mLastPoint, mA, mB;
    bool mLoop;
    bool mStarted;
    std::vector<sf::Vertex> mVertexArray;
};

#endif // TRAIL_H
