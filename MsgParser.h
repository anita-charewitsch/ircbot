#ifndef MSGPARSER_H
#define MSGPARSER_H

#include <vector>
#include <ctime>
#include <sstream>
#include <stdio.h>
#include <string>

using namespace std;

class MsgParser {
public:
    MsgParser(string msg);
    ~MsgParser() {};

    string          sender;
    vector<string>  message;

    int atPosition(string msgVar);
};

#endif
