#include "../include/Camera.h"
#include "Core.h"
#include <limits>

using namespace std;

Camera::Camera(bool trackRotation) : mAlpha(0.99), mTrackRotation(trackRotation), mZoomOffset(1.5), mBeta(0.995)
{
}

void Camera::setTarget(const sf::Transformable& t)
{
    mTargets.clear();
    mTargets.push_back(&t);
}

void Camera::addTarget(const sf::Transformable &t)
{
    mTargets.push_back(&t);
}

void Camera::removeTarget(const sf::Transformable &t)
{
    for(int i = 0; i < mTargets.size(); i++)
    {
        if(mTargets[i] == &t)
        {
            swap(mTargets[i],mTargets.back());
            mTargets.pop_back();
        }
    }
}

void Camera::setAlpha(float alpha)
{
    mAlpha = min(1.f,max(0.f,alpha));
}

Camera& Camera::operator=(const sf::View& other)
{
    sf::View::operator=(other);
}

const sf::Transformable* Camera::getTarget() const
{
    return mTargets.back();
}

void Camera::update(float delta_t)
{
    sf::Vector2f center;
    sf::FloatRect bounds{std::numeric_limits<float>::max(),
                std::numeric_limits<float>::max(),
                std::numeric_limits<float>::min(),
                std::numeric_limits<float>::min()};
    for(const sf::Transformable*& t : mTargets) {
        if(t) {
            bounds.left = min(t->getPosition().x, bounds.left);
            bounds.top = min(t->getPosition().y, bounds.top);
            bounds.width = max(t->getPosition().x, bounds.width);
            bounds.height = max(t->getPosition().y, bounds.height);

            center += t->getPosition();
        }
    }

    bounds.width = bounds.width - bounds.left;
    bounds.height = bounds.height - bounds.top;
    bounds.width *= mZoomOffset;
    bounds.height *= mZoomOffset;

    center /= float(mTargets.size());


    if(mTargets.size() > 1) {
        float vratio = Core::get().aspectRatio();
        float bratio = bounds.height / bounds.width;
        if(bratio > vratio)
        {
            //Use y as reference
            mTargetSize = {bounds.height/vratio,bounds.height};
        }
        else
        {
            //Use x as reference
            mTargetSize = {bounds.width,bounds.width*vratio};
        }

        setSize(mTargetSize*(1-mBeta) + getSize()*mBeta);
    }

    if(mTargets.size()) {
        setCenter(getCenter() * mAlpha + center * (1.f-mAlpha));

        /*if(mTrackRotation)
            setRotation(getRotation() * mAlpha + mTarget->getRotation()* (1.f-mAlpha));*/
    }
}
