//
//  kClientSocket.cpp
//  cctest01
//
//  Created by kael on 12/4/12.
//
//

#include "kClientSocket.h"
#include "kJsonProtocolBase.h"
#include "cocos2d.h"
#define CMD2STR(cmd) #cmd
kClientSocket::kClientSocket()
{
    recvBuffSize = 0;
}
bool kClientSocket::stop = false;

void kClientSocket::doRecv()
{
    FD_ZERO(&fds);
    FD_SET(_socket.getSocket(), &fds);
    struct timeval tv={10,0};
    int ret = select(_socket.getSocket()+1, &fds, NULL, NULL, &tv);
    if (ret == 0) {
       
    }
    if(FD_ISSET(_socket.getSocket(), &fds))
    {
        int recvbytes = _socket.recv_from(recv_buf + recvBuffSize, sizeof(recv_buf) - recvBuffSize,MSG_DONTWAIT);// MSG_DONWAIT MEANS NO BLOCK
        if (recvbytes <= 0) {
            printf("receive error\n");
            //_socket.close_me();
        }
        else{
            package_info pi;
            pi.beg = recvBuffSize;
            pi.size = recvbytes;
            package_infos.push_back(pi);
            
            recvBuffSize += recvbytes;
            // do data parse other place
            if(recvBuffSize >= MAXBUFFERED_PACKAGE * MAXDATASIZE)
            {
                recvBuffSize = 0;// from start
            }
        }
    }
}

bool kClientSocket::IsValid()
{
    return _socket.getSocket()!=-1;
}

void* kClientSocket::thread_func(void *pVoid)
{
    // this function should be static
    // thread local is this pointer
    kClientSocket* pThis = (kClientSocket*)pVoid;
    while (!stop) {
        if (!pThis->IsValid()) {
            break;
        }
        else
            pThis->doRecv();
    }
    // stoped loop over
    pthread_cancel(NULL);
    return ((void*)0);
}

void kClientSocket::onUpdate()
{
    for(std::list<package_info>::iterator it = package_infos.begin();it!=package_infos.end();)
    {
        if(do_data_parse(recv_buf + it->beg, it->size))
        {
            package_infos.erase(it++);
        }
        else
            ++it;
    }
}

bool kClientSocket::do_data_parse(const char* data,unsigned short len)
{
    // java server is big endian
    // c++ server is small endian
    kJsonProtocolBase jpb;
    jpb.fromBufferDecryptJavaServer((const unsigned char*)data, len);
    // parse command and tell ui
    int cmd = jpb.getValue("cmd").asInt();
    sprintf(cmd_in_char,"%d",cmd);
    cocos2d::CCNotificationCenter::sharedNotificationCenter()->postNotification(cmd_in_char,(cocos2d::CCObject*)(&jpb));
    return true;
}

int kClientSocket::start(const char* ip,unsigned short port)
{
    int errorcode = 0;
    // start the socket
    bool ok = true;
    ok = _socket.create(AF_INET, SOCK_STREAM, 0);
    if(ok)
    {
        ok = _socket.connect_to(ip, port);
        if (ok) {
            // start the thread
            do {
                pthread_attr_t pAttr;
                errorcode = pthread_attr_init(&pAttr);
                if (errorcode!=0) {
                    break;
                }
                errorcode = pthread_attr_setdetachstate(&pAttr,PTHREAD_CREATE_DETACHED);
                if (errorcode!=0) {
                    pthread_attr_destroy(&pAttr);
                    break;
                }
                errorcode = pthread_create(&thread, &pAttr, thread_func, this);
                stop = false;
            } while (0);
        }else
        {
            errorcode = SOCKET_ERROR;
        }
    }else
    {
        errorcode = SOCKET_ERROR;
    }
    return errorcode;
}

void kClientSocket::stop_()
{
    _socket.close_me();
    stop = true;
}