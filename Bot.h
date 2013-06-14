#ifndef BOT_H
#define BOT_H

#include <sqlite3.h>
#include <vector>
#include <algorithm>
#include <sstream>
#include "Connection.h"
#include "DBConnect.h"
#include "MsgParser.h"

class Bot
{
public:
    Bot(string nickname, string password);
    ~Bot();

    void            mainLoop();

    Connection      *con;

    string          nickname;
    string          password;
    bool            log;

    void    ConnectToServer(string host, int port, string channel);

    void    Logging(bool log);
    void    ClearLog();
    void    AddLog(string name, string msg);
    void    GetLog();
    void    GetLastSeen(string nickname);

    int     BotFunctions(string buffer);
    void    Nick(string nickname);
    void    User(string username);
    void    Join(string channel);
    void    Leave(string channel);
    void    ChangeTopic(string topic);
};

#endif
