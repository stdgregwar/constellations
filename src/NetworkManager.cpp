#include "NetworkManager.h"
#include "Core.h"
#include "JSONSerialiser.h"
#include <iostream>

using namespace std;

NetworkManager::NetworkManager() : mContinue(true), mReceiver(nullptr)
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
    /*sendJSON({
                       {"Hello","World"},
                       {"Obj", {
                                 {"Bonjour", "aurevoir"},
                                 {"Number", 89},
                                 {"Tatata", true},
                                 {"List", j::VArray{"Bla", "Caca", 2,true}}
                             }
                         }
                     });*/

    while(keepGoing())
    {
        receiveJSON();
    }

    disconnect();
}

void NetworkManager::connectToServer()
{
    Lock lock(mToCallMutex);
    if(mSocket.connect(mHost,mPort) != sf::Socket::Error){
        mToCall = bind(mConnectCallback,true);

        sendJSON(j::Value{
                     {"kind","ConnectionRequest"},
                     {"obj",{
                          {"nick",Core::get().globalDict()["nick"].toString()}
                      }
                     }
                 });
    } else {
        mToCall = bind(mConnectCallback,false);
        mContinue = false;
    }

}

void NetworkManager::disconnect()
{
    mSocket.disconnect();
}

bool NetworkManager::connected() const
{
    return keepGoing();
}

bool NetworkManager::keepGoing() const
{
    return mContinue;
}

void NetworkManager::receivePacket()
{
    /*sf::Packet p;
    mSocket.receive(p);

    Lock lock(mPacketBufferMutex);
    mPacketBuffer.push(p);*/
}

void NetworkManager::receiveJSON()
{
    constexpr size_t BUFFERSIZE = 512;
    char buf[BUFFERSIZE+1];
    buf[BUFFERSIZE] = 0; //Null terminate buffer
    size_t received;
    mSocket.receive(buf,BUFFERSIZE,received);

    mCurrentString += string(buf);
    for(size_t i = 0; i < received; i++)
    {
        if(buf[i] == 0 || buf[i] == '\n') //Null char meaning end of string
        {
            Lock lock(mPacketBufferMutex);
            cout << mCurrentString << endl;
            mPacketBuffer.push(j::readFromString(mCurrentString));
            break;
        }
    }
}

void NetworkManager::update(float delta_s)
{
    { //Lock scope
        Lock lock(mToCallMutex);
        std::function<void()> temp = mToCall;
        mToCall = nullptr;
        if(temp) {
            temp();
        }
    }

    { //Lock scope
        Lock lock(mPacketBufferMutex);
        while(!mPacketBuffer.empty())
        {
            if(mReceiver) {
                mReceiver->onReceive(mPacketBuffer.back());
                mPacketBuffer.pop();
            }
        }
    }
}

void NetworkManager::setReceiver(Receiver *r)
{
    mReceiver = r;
}

NetworkManager::Receiver* NetworkManager::receiver() const
{
    return mReceiver;
}


NetworkManager::~NetworkManager()
{
    mContinue = false;
    mThread.join();
}
