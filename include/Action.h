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
    /**
     * @brief type of the action used to discriminate the union of struct
     */
    enum ACTION_TYPE
    {
        NONE, ///Default type of an action (empty action)
        MOVE_X, ///Moving action on the x axis
        MOVE_Y, ///Moving action on the y axis
        JUMP, ///Jump
        AIM, ///Aim at some direction
        CANCEL, ///Cancel action
        THROW, ///Throw arrow
        PUT ///Reset character on some position
    };

    struct Move{
        float distance; ///position offset
    };

    struct Jump{
        float strength; ///jump height/strenght
    };

    struct Aim{
        sf::Vector2f direction; ///direction of the aim
    };

    struct Throw{
        sf::Vector2f direction; ///direction of the throw
    };

    struct Put{
        sf::Vector2f position; ///position on which to be put
        int planetID; ///planet associated with position
    };

    Action(ACTION_TYPE t = NONE) : type(t) {}
    ACTION_TYPE type; ///Public action type

    /**
     * @brief Anonymous union containing all events structure (since they are never used simultaneously)
     */
    union{
        Move move;
        Jump jump;
        Aim aim;
        Throw throw_;
        Put put;
    };
};

/**
 * @brief Represent a queue of action (with fixed size) to be handled by the character
 *
 * TODO: Make thread safe
 */
class ActionQueue
{
public:
    static constexpr size_t BUFFERSIZE = 12; ///Fixed size of the queue

    ActionQueue()
     : mHead(0), mTail(0)
    {
    }

    /**
     * @brief queue action
     * @param a an action
     */
    void queue(const Action& a)
    {
        mBuffer[mTail] = a;
        mTail = (mTail+1)%BUFFERSIZE;
    }

    /**
     * @brief poll action
     * @param an action to fill with the new one
     * @return true if queue isn't empty
     */
    bool pollAction(Action& a)
    {
        bool nempty = !empty();
        if(nempty) {
            a = mBuffer[mHead];
            mHead = (mHead+1)%BUFFERSIZE;
        }
        return nempty;
    }

    /**
     * @brief is the queue empty
     * @return true if the queue is empty
     */
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
