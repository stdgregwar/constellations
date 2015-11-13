#ifndef ACTION_H
#define ACTION_H

#include <SFML/System/Vector2.hpp>
#include <array>

/**
 * @brief The Action class
 *
 * Used like event but for Character Controller
 */
class Action
{

public:
    enum ACTION_TYPE
    {
        NONE,
        MOVE_X,
        MOVE_Y,
        JUMP,
        AIM,
        CANCEL,
        THROW,
        PUT
    };

    struct Move{
        float distance;
    };

    struct Jump{
        float strength;
    };

    struct Aim{
        sf::Vector2f direction;
    };

    struct Throw{
        sf::Vector2f direction;
    };

    struct Put{
        sf::Vector2f position;
        int planetID;
    };

    Action(ACTION_TYPE t = PUT) : type(t) {}
    ACTION_TYPE type;

    union{
        Move move;
        Jump jump;
        Aim aim;
        Throw throw_;
        Put put;
    };
};

class ActionQueue
{
public:
    static constexpr size_t BUFFERSIZE = 12;

    ActionQueue()
     : mHead(0), mTail(0)
    {
    }

    void queue(const Action& a)
    {
        mBuffer[mTail] = a;
        mTail = (mTail+1)%BUFFERSIZE;
    }

    bool pollAction(Action& a)
    {
        bool nempty = !empty();
        if(nempty) {
            a = mBuffer[mHead];
            mHead = (mHead+1)%BUFFERSIZE;
        }
        return nempty;
    }

    bool empty()
    {
        return mHead == mTail;
    }
private:
    std::array<Action, BUFFERSIZE> mBuffer;
    size_t mHead;
    size_t mTail;
};

#endif // ACTION_H
