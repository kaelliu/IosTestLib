//
//  kClientSocket.h
//
//  Created by kael on 12/4/12.
//
//

#ifndef __cctest01__kClientSocket__
#define __cctest01__kClientSocket__

#include "kSocket.h"
//#include <curses.h>
#include <list>
// 一次最大包数据长度
#define MAXDATASIZE 8192
// 当前缓存包最大数量
#define MAXBUFFERED_PACKAGE 3
struct package_info
{
    unsigned short beg;// begin pointer in buffer
    unsigned short size;// size of this package
};
class kClientSocket
{
private:
    char cmd_in_char[8];
    fd_set fds;
    pthread_t thread;
    static bool stop;
    kSocket _socket;
    bool do_data_parse(const char* data,unsigned short len);
    unsigned short recvBuffSize;// cursor where recv buff now
    // use as ring buffer
    char recv_buf[MAXDATASIZE * MAXBUFFERED_PACKAGE];
    std::list<package_info> package_infos;
    void doRecv();
    bool IsValid();
public:
    void onUpdate();
    static void* thread_func(void*);
    kClientSocket();
    int start(const char* ip,unsigned short port);
    void stop_();
    const kSocket& getSockConst()const{return _socket;}
    kSocket& getSock(){return _socket;}
    inline bool isStop()const{return stop;}
};
#endif /* defined(__kClientSocket__) */
