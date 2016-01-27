#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include "Action.h"
#include <SFML/Network.hpp>
#include <thread>
#include <mutex>
#include <functional>
#include <queue>

typedef int UID;
typedef int Slot;
typedef std::lock_guard<std::mutex> Lock;

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
    void startNetworking(std::function<void(bool)> callback);

    /**
     * @brief send action to server, if not connected : return false and do nothing
     * @param action
     * @param uid
     * @return
     */
    bool sendAction(const Action& action, Slot slot);

    /**
     * @brief used to call functions from main thread in a cooperative multitask way
     * @param delta_s
     */
    void update(float delta_s);

    void receivePacket();

    State state() const;

    ~NetworkManager();
private:
    static void secondThread(NetworkManager& that);
    void connectToServer();
    void disconnect();
    bool keepGoing() const;

    std::string mHost;
    sf::Uint8 mPort;
    std::function<void(bool)> mConnectCallback;
    std::mutex mToCallMutex;
    std::function<void()> mToCall;
    std::thread mThread;
    bool mContinue;

    std::mutex mPacketBufferMutex;
    std::queue<sf::Packet> mPacketBuffer;

    sf::TcpSocket mSocket;
    State mState;

};

#endif // NETWORKMANAGER_H
