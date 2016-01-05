#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Transformable.hpp>

class Camera : public sf::View
{
public:
    Camera(bool trackRotation = true);
    void setTarget(const sf::Transformable& t);
    void addTarget(const sf::Transformable& t);
    void removeTarget(const sf::Transformable& t);
    void setAlpha(float alpha);
    void setTargetHeight(float height);
    Camera& operator=(const sf::View& other);
    const sf::Transformable* getTarget() const;
    void update(float delta_t);
    void setSize(float width, float height);
    void setSize(const sf::Vector2f& size);
private:
    std::vector<const sf::Transformable*> mTargets;
    sf::Vector2f mTargetSize;
    bool mTrackRotation;
    float mAlpha;
    float mBeta;
    float mZoomOffset;
};

#endif // CAMERA_H
