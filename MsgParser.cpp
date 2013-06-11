#include "MsgParser.h"

MsgParser::MsgParser(string msg) {
    this->sender="";
    /*
        MESSAGE
    */
    this->sender = "";
    size_t dd=0;
    size_t ex=0;
    size_t at=0;
    dd = msg.find_first_of(':');
    ex = msg.find_first_of('!');
    at = msg.find_first_of('@');

    if(dd<ex && ex<at)
        this->sender = msg.substr( (int)dd+1 , (int)ex-(int)dd-1 );

    /*
        MESSAGE
    */
    string space(" ");
    size_t pos=0;

    // Suche nach Leerzeichen
    if( ( pos = msg.find(space) ) != string::npos )
        msg = msg.substr( pos+1 , msg.length()-(int)pos-1 );

    while( msg.length() > 0 ) {
        // Suche nach dem nächsten Leerzeichen oder dem Ende
        if( ( pos = msg.find(space) ) != string::npos) {
            this->message.push_back( msg.substr( 0 , (int)pos ) );
            msg = msg.substr( (int)pos+1 , (int)msg.length()-(int)pos-1 );
        }
        else {
            this->message.push_back( msg = msg.substr( 0 , (int)msg.length() ) );
            break;
        }
    }
}
int MsgParser::atPosition(string msgVar) {
    for(int i=0;i<this->message.size();i++)
        if(this->message[i]==msgVar) return i;
    return -1;
}
