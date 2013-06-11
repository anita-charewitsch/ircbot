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
    MsgParser data(buffer);
    int pos=0;

    if (log) {
        stringstream msg;
        for(int i=0;i<(int)data.message.size();i++)
            msg << data.message[i] << " ";
        if (data.message.size() > 0)
            AddLog(data.sender, msg.str());
    }

    if ((pos=data.atPosition("-log")) != -1 && (int)data.message.size() > pos+1 ) {
        if (data.message[pos+1] == "on" )
        {
            log = true;
            con->Send("PRIVMSG #" + con->GetChannel() + " :Logging enabled\r\n");
        } else if( data.message[pos+1] == "off" )
        {
            log = false;
            con->Send("PRIVMSG #" + con->GetChannel() + " :Logging disabled\r\n");
        }
    }
    else if( (pos=data.atPosition("-topic")) != -1 && (int)data.message.size() > pos+1)
    {
        ChangeTopic(data.message[pos+1]);
        con->Send("PRIVMSG #" + con->GetChannel() + " :Topic changed\r\n");
    }
    else if( (pos=data.atPosition("-nick")) != -1 && (int)data.message.size() > pos+1 )
    {
        Nick(data.message[pos+1]);
        con->Send("PRIVMSG #" + con->GetChannel() + " :Nickname changed\r\n");
    }
    else if( (pos=data.atPosition("-join")) != -1 && (int)data.message.size() > pos+1 )
    {
        Join( data.message[pos+1] );
    }
    else if( (pos=data.atPosition("-leave")) != -1 && (int)data.message.size() > pos+1 )
    {
        con->Send("PRIVMSG #" + con->GetChannel() + " :Leaving channel... bye!\r\n");
        Leave( data.message[pos+1] );
    }
    else if((pos=data.atPosition("-show_log")) != -1 )
    {
        GetLog();
    }
    else if ((pos=data.atPosition("-last_seen")) != -1 && data.message.size() > pos+1)
    {
        GetLastSeen(data.message[pos+1]);
    }
    else if ((pos=data.atPosition("-exit")) != -1 )
    {
        con->Send("PRIVMSG #" + con->GetChannel() + " :BYE BYE!\r\n");
        con->Send("QUIT bye\r\n");
        return -1;
    }
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
