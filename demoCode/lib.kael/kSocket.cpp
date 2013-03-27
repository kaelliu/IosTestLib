//
//  kSocket.cpp
//  implement file
//
//  Created by kael on 12/3/12.
//
//

#include "kSocket.h"
#ifdef WIN32
    #include"stdafx.h"
    #pragma comment(lib,"wsock32")
#endif

kSocket::kSocket(SOCKET sock)
{
    init();
    this->sock = sock;
}

kSocket::~kSocket()
{
    
}

int kSocket::init()
{
#ifdef WIN32
    /*
     http://msdn.microsoft.com/zh-cn/vstudio/ms741563(en-us,VS.85).aspx
    typedef struct WSAData {
		WORD wVersion;								//winsock version
		WORD wHighVersion;							//The highest version of the Windows Sockets specification that the Ws2_32.dll can support
		char szDescription[WSADESCRIPTION_LEN+1];
		char szSystemStatus[WSASYSSTATUS_LEN+1];
		unsigned short iMaxSockets;
		unsigned short iMaxUdpDg;
		char FAR * lpVendorInfo;
	}WSADATA, *LPWSADATA;
	*/
	WSADATA wsaData;
	//#define MAKEWORD(a,b) ((WORD) (((BYTE) (a)) | ((WORD) ((BYTE) (b))) << 8))
	WORD version = MAKEWORD(2, 0);
	int ret = WSAStartup(version, &wsaData);//win sock start up
	if ( ret ) {
        //		cerr << "Initilize winsock error !" << endl;
		return -1;
	}
#endif
    return 0;
}

// this is only for windows
int kSocket::clean()
{
#ifdef WIN32
    return (WSACleanup());
#endif
    return 0;
}

// type:SOCK_STREAM,SOCK_DGRAM
bool kSocket::create(int af,int type,int protocol)
{
    sock = socket(af, type, protocol);
    if(sock == INVALID_SOCKET)
        return false;
    return true;
}

bool kSocket::connect_to(const char* ip, unsigned short port)
{
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip);
    addr.sin_port = htons(port);
    int ret = connect(sock, (struct sockaddr*)&addr,sizeof(addr));
    if (ret == SOCKET_ERROR) {
        return false;
    }
    return true;
}

bool kSocket::bind_to(unsigned short port)
{
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);
    
    int opt = 1;
    if(setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt))<0)
        return false;
    int ret = bind(sock,(struct sockaddr*)&addr,sizeof(addr));
    if (ret == SOCKET_ERROR) {
        return false;
    }
    return true;
}

// for server
bool kSocket::listen_to(int backlog)
{
    int ret = listen(sock, backlog);
    if(ret == SOCKET_ERROR)
        return false;
    return true;
}

bool kSocket::accept_from(kSocket& s,char* ip)
{
    struct sockaddr_in client_addr;
    socklen_t addrlen = sizeof(client_addr);
    SOCKET soc = accept(sock, (struct sockaddr*)&client_addr, &addrlen);
    if(soc == INVALID_SOCKET)
        return false;
    s = soc;
    if(ip != NULL)
        sprintf(ip, "%s",inet_ntoa(client_addr.sin_addr));
    return true;
}

int kSocket::send_to(const char* buf, int len,int flags)
{
    int bytes;
    int count = 0;
    while(count < len)
    {
        bytes = send(sock, buf + count, len - count, flags);
        if(bytes == -1 || bytes == 0)
            return -1;
        count += bytes;
    }
    return bytes;
}

int kSocket::recv_from(char* buf, int len,int flags)
{
    return recv(sock, buf, len, flags);
}

int kSocket::close_me()
{
#ifdef WIN32
    return (closesocket(sock));
#else
    return (close(sock));
#endif
}

int kSocket::getError()
{
#ifdef WIN32
    return (WSAGetLastErrno());
#else
    return h_errno;// mac use this,errno will add other header
#endif
}

bool kSocket::dnsParse(const char* domain, char * ip)
{
    struct hostent* p;
    if((p = gethostbyname(domain)) == NULL)
       return false;
    sprintf(ip,
            "%u.%u.%u.%u",
            (unsigned char)p->h_addr_list[0][0],
            (unsigned char)p->h_addr_list[0][1],
            (unsigned char)p->h_addr_list[0][2],
            (unsigned char)p->h_addr_list[0][3]);
    return true;
}

kSocket& kSocket::operator=(SOCKET s)
{
    sock = s;
    return *this;
}

kSocket::operator SOCKET()
{
    return sock;
}
