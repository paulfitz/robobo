// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <map>
#include <string>

extern "C" {
#include "yarpmin.h"
}

using namespace std;

void append_int(char *&buf,int x) {
    if (sizeof(x)!=4) {
        printf("integer unexpected size\n");
        exit(1);
    }
    yarp_write_int(buf,4,x);
    buf += 4;
}

void append_string(char *&buf,const string& str) {
    memcpy(buf,str.c_str(),str.length());
    buf += str.length();
}


string show_message(string s) {
    string result = "";
    for (int i=0; i<s.length(); i++) {
        char buf[256];
        char ch = s[i];
        sprintf(buf, "%c (%d) ", (ch>=' ')?ch:'.', ch);
        result += buf;
    }
    return result;
}

class Header {
public:
    map<string,string> data;

    string writeHeader();
    bool readHeader();
};

string Header::writeHeader() {
    size_t len = 0;
    for (map<string,string>::iterator it = data.begin();
         it!=data.end(); it++) {
        string key = it->first;
        string val = it->second;
        len += 4 + key.length() + 1 + val.length();
    }
    string result(len,'\0');
    char *buf = (char *)result.c_str();
    for (map<string,string>::iterator it = data.begin();
         it!=data.end(); it++) {
        string key = it->first;
        string val = it->second;
        append_int(buf,key.length()+1+val.length());
        append_string(buf,key);
        append_string(buf,string("="));
        append_string(buf,val);
    }
    return result;
}

bool Header::readHeader() {
    return false;
}

int ping(int port) {
    yarpAddress addr;
    strcpy(addr.host,"localhost");
    addr.port_number = port;

    yarpConnection connection = yarp_connect(&addr);
    if (!yarp_is_valid(connection)) {
        return 1;
    }
    printf("Connected\n");

    Header header;
    header.data["test"] = "hello";
    header.data["type"] = "std_msgs/String";
    header.data["md5sum"] = "*";
    header.data["message_definition"] = "mu";
    header.data["callerid"] = "/not/valid/at/all";
    string header_serial = header.writeHeader();
    string header_len(4,'\0');
    char *at = (char*)header_len.c_str();
    append_int(at,header_serial.length()+4);
    
    printf("Writing %s -- %d bytes\n", 
           show_message(header_len).c_str(),
           header_len.length());
    yarp_send_binary(connection,header_len.c_str(),header_len.length());
    printf("Writing %s -- %d bytes\n", 
           show_message(header_serial).c_str(),
           header_serial.length());
    yarp_send_binary(connection,header_serial.c_str(),header_serial.length());

    char len_buf[4] = {0,0,0,0};
    yarp_receive_binary(connection,len_buf,4);
    int len = yarp_read_int(len_buf,4);
    printf("got len %d\n", len);

    yarp_disconnect(connection);
}

int main(int argc, char *argv[]) {
    if (argc!=2) return 1;
    int port = atoi(argv[1]);
    printf("Trying port %d\n", port);
    return ping(port);
}

