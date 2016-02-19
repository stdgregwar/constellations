#ifndef STATEERROR_H
#define STATEERROR_H

#include "GameState.h"
#include "Exceptions.h"
#include "Camera.h"

/**
 * @brief Display given Error on screen, several behaviour available
 */
class StateError : public GameState
{
public:
    StateError(const CException& e);
    void onBegin();
    void onResume();
    void pushEvent(const sf::Event& e);
    void update(float delta_s);
    void draw(sf::RenderTarget &target);
    void onPause();
    void onEnd();
    ~StateError();
private:
    sf::Text mTitle;
    sf::Text mText;
    Camera mCam;
    EType mType;
};

#endif // STATEERROR_H
