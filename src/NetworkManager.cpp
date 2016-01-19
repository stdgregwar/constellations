#include "NetworkManager.h"
#include "Core.h"


NetworkManager::NetworkManager()
{
    mSocket.setBlocking(false);
}

bool NetworkManager::startNetworking()
{
    mSocket.setBlocking(true);
    mSocket.connect(Core::get().globalDict()["host"].toString(),Core::get().globalDict()["port"]);
    mSocket.setBlocking(false);
    return false;
}

bool NetworkManager::sendAction(const Action& action, UID uid)
{

}

void NetworkManager::pollSocket()
{
    switch(mState)
    {
    }
}
