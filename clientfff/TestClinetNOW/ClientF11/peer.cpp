#include "peer.h"

string Peer::myUsername;
string Peer::myPassword;
vector<Peer> Peer::onlinePeers;

Peer::Peer(string _username, string _IPAddress, int _port)
{
username = _username;
IPAddress = _IPAddress;
port = _port;
}



Peer* Peer::getPeerByUsername(string username)
{
for(int i = 0; i < onlinePeers.size(); i++)
{
    if(onlinePeers.at(i).username == username)
    {
        return &onlinePeers.at(i);
    }
}

return NULL;
}
