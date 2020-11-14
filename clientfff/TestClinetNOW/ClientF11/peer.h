#ifndef PEER_H
#define PEER_H

#include <string>
#include <vector>

using namespace std;

class Peer
{
public:
    static string myUsername;
    static string myPassword;
    static vector<Peer> onlinePeers;

    string username;
    string IPAddress;
    int port;

    Peer(string _username, string _IPAddress, int _port);

    Peer();

    static Peer* getPeerByUsername(string username);
};

#endif // PEER_H
