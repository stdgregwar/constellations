#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include "Action.h"
#include <SFML/Network.hpp>
#include <thread>
#include <functional>

typedef int UID;

class NetworkManager
{
public:
    enum State{
        IDLE,
        TCP_CONNECTING,
        TCP_CONNECTED,
        WAITING_FOR_CONNECTION,
        CONNECTED,
        WAITING_FOR_MATCH,
        IN_MATCH_MAKING,
        MATCH_START_HANDSHAKE,
        MATCH
    };

    NetworkManager();

    /**
     * @brief tries to connect to server and call the given function(if any) when done
     * @return
     */
    bool startNetworking(std::function<void()> callback);

    /**
     * @brief send action to server, if not connected : return false and do nothing
     * @param action
     * @param uid
     * @return
     */
    bool sendAction(const Action& action, UID uid);

    /**
     * @brief used to call functions from main thread in a cooperative multitask way
     * @param delta_s
     */
    void update(float delta_s);

    State state() const;
private:
    std::function<void()> mCallback;
    sf::TcpSocket mSocket;
    State mState;

};

#endif // NETWORKMANAGER_H
