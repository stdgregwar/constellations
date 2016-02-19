#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include "Action.h"
#include <SFML/Network.hpp>
#include <thread>
#include <mutex>
#include <functional>
#include <queue>
#include "JSON.h"

typedef int UID;
typedef int Slot;
typedef std::lock_guard<std::mutex> Lock;

class NetworkManager
{
public:
    /**
     * @brief Interface for receiving JSON messages
     */
    class Receiver
    {
        public:
            virtual void onReceive(const j::Value& message) = 0;
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
     * @return true on succes
     */
    bool sendAction(const Action& action, Slot slot);

    /**
     * @brief send JSON value trough tcp socket
     * @param v value
     * @return true on success
     */
    bool sendJSON(const j::Value& v);

    /**
     * @brief used to call functions from main thread in a cooperative multitask way
     * @param delta_s
     */
    void update(float delta_s);

    /**
     * @brief receive a packet and put it in the buffer
     */
    void receivePacket();

    /**
     * @brief receive JSON message (null terminated string)
     */
    void receiveJSON();

    Receiver* receiver() const;
    void setReceiver(Receiver* r);

    bool connected() const;

    ~NetworkManager();
private:
    //Static function executed in secondary thread
    void secondThread();
    void connectToServer();
    void disconnect();
    bool keepGoing() const;

    std::string mHost;
    int mPort;
    std::function<void(bool)> mConnectCallback;
    std::mutex mToCallMutex;
    std::function<void()> mToCall;
    std::thread mThread;
    bool mContinue;

    std::string mCurrentString;

    std::mutex mPacketBufferMutex;
    std::queue<j::Value> mPacketBuffer;

    sf::TcpSocket mSocket;
    Receiver* mReceiver;

};

#endif // NETWORKMANAGER_H
