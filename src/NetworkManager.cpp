#include "NetworkManager.h"
#include "Core.h"
#include "JSONSerialiser.h"

using namespace std;

NetworkManager::NetworkManager() : mContinue(true)
{
}

void NetworkManager::startNetworking(std::function<void(bool)> callback)
{
    mHost = Core::get().globalDict()["host"].toString();
    mPort = Core::get().globalDict()["port"].toInt();
    mConnectCallback = callback;
    mThread = thread(&NetworkManager::secondThread, this);
}

bool NetworkManager::sendAction(const Action& action, Slot slot)
{

}

bool NetworkManager::sendJSON(const j::Value &v)
{
    string str = j::writeToString(v);
    mSocket.send(str.c_str(),str.size()+1);
}

void NetworkManager::secondThread()
{
    connectToServer();
    sendJSON({
                       {"Hello","World"},
                       {"Obj", {
                                 {"Bonjour", "aurevoir"},
                                 {"Number", 89},
                                 {"Tatata", true},
                                 {"List", j::VArray{"Bla", "Caca", 2,true}}
                             }
                         }
                     });

    while(keepGoing())
    {
        receivePacket();
    }

    disconnect();
}

void NetworkManager::connectToServer()
{
    Lock lock(mToCallMutex);
    if(mSocket.connect(mHost,mPort) != sf::Socket::Error){
        mToCall = bind(mConnectCallback,true);
    } else {
        mToCall = bind(mConnectCallback,false);
        mContinue = false;
    }
}

void NetworkManager::disconnect()
{
    mSocket.disconnect();
}

bool NetworkManager::keepGoing() const
{
    return mContinue;
}

void NetworkManager::receivePacket()
{
    sf::Packet p;
    mSocket.receive(p);

    Lock lock(mPacketBufferMutex);
    mPacketBuffer.push(p);
}

void NetworkManager::update(float delta_s)
{
    { //Lock scope
        Lock lock(mToCallMutex);
        if(mToCall) {
                mToCall();
                mToCall = nullptr;
        }
    }

    switch(mState)
    {
        default:
            break;
    }
}

NetworkManager::~NetworkManager()
{
    mContinue = false;
    mThread.join();
}
