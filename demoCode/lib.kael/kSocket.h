//
//  kSocket.h
//  define socket class
//  description : should suit both on windows and linux for client
//  Created by kael on 12/3/12.
//
//

#ifndef __kSocket__
#define __kSocket__

#include <iostream>
#ifdef  WIN32
    #include <winsock.h>
    typedef int socklen_t;
#else
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <netdb.h>
    #include <fcntl.h>
    #include <unistd.h>
    #include <sys/stat.h>
    #include <sys/types.h>
    #include <arpa/inet.h>
    typedef int SOCKET;

    #define INVALID_SOCKET -1
    #define SOCKET_ERROR -1
#endif

typedef struct
{
    int block;
    int sendbuffersize;
    int recvbuffersize;
    int lingertimeout;
    int recvtimeout;
    int sendtimeout;
} socketoption_t;

typedef struct
{
    int nbytes;
    int nresult;
} transresult_t;

class kSocket {
public:
    kSocket(SOCKET sock = INVALID_SOCKET);
    virtual ~kSocket();
    // create socket
    // param @af address family
    // @type tcp or udp
    // @protocol
    bool create(int af,int type,int protocol);
    // connect to ipaddress
    bool connect_to(const char* ip,unsigned short port);
    // bind socket,for server
    bool bind_to(unsigned short port);
    // listen socket
    bool listen_to(int backlog = 5);
    // accept socket
    bool accept_from(kSocket& s,char* from_ip = NULL);
    // send msg
    int send_to(const char* buf,int data_len,int flags = 0);
    // receive msg
    int recv_from(char* buf,int data_len,int flags = 0);
    // close socket
    int close_me();
    // get errno
    int getError();
    // for win32 platform
    // init win32 dll
    static int init();
    // clean win32 dll
    static int clean();
    
    // domain parse
    static bool dnsParse(const char* domain,char* ip);
    // misc staff
    kSocket& operator =(SOCKET s);
    operator SOCKET();
    inline SOCKET getSocket()const {return sock;}
protected:
    SOCKET sock;
};

#endif /* defined(__cctest01__kSocket__) */
