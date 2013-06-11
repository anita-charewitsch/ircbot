#include "Bot.h"

// Konstruktor
Bot::Bot(string nickname, string password)
{
    this->nickname = nickname;
    this->password = password;
    this->log = false;
    con = NULL;
    DBConnect::init("logdb.sqlite");
}

// Destruktor
Bot::~Bot()
{
    delete con;
}

void Bot::mainLoop()
{
    string message;
    for (;;) {
        if (!con->Receive(message))
            break;
        cout << message << endl;
        con->PingPong(message);
        if (BotFunctions(message) == -1)
            break;
    }
}

void Bot::ConnectToServer(string host, int port, string channel)
{
    con = new Connection(host, port, channel);
    con->Connect();
    con->Identify(nickname, password, channel);
    mainLoop();
    con->Disconnect();
}

void Bot::Logging(bool log)
{
    this->log = log;
}


int Bot::BotFunctions(string buffer)
{

    return 0;
}

void Bot::Nick(string nickname)
{
    con->Send("NICK " + nickname + "\r\n");
}
void Bot::User(string username)
{
    con->Send("USER " + username + " 0 0  :" + username + "\r\n");
}
void Bot::Join(string channel)
{
    con->SetChannel(channel);
}
void Bot::Leave(string channel)
{
    con->Send("PART #" + channel + "\r\n");
}
void Bot::ChangeTopic(string topic)
{
    con->Send("TOPIC #" + con->GetChannel() + " " + topic + "\r\n");
}
