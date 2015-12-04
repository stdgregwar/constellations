#ifndef TRAIL_H
#define TRAIL_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <vector>

class Trail : public sf::Drawable
{
public:
    Trail(float width,float threshold, size_t size);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void addPoint(const sf::Vector2f& p);
private:
    size_t mStart,mEnd;
    float mWidth;
    float mThreshold;
    sf::Vector2f mLastPoint, mA, mB;
    bool mLoop;
    bool mStarted;
    std::vector<sf::Vertex> mVertexArray;
};

#endif // TRAIL_H
