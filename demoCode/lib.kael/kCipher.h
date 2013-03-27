//
//  kCipher.h
//  cctest01
//
//  Created by kael on 12/4/12.
//
//

#ifndef __kCipher__
#define __kCipher__

class kCipher
{
public:
    kCipher();
    static const short ver = 0x66;
    static unsigned char* decryptBuffer(unsigned char* pBuffer,int length);
    static unsigned char* encryptBuffer(unsigned char* pBuffer,int length);
protected:
    static const short sendMap[];
    static const short recvMap[];
    int m_cbSendRound ;
    int m_cbRecvRound ;
    
    int m_dwSendXorKey ;
    int m_dwRecvXorKey ;
    
    int m_dwSendPacketCount ;
    
    static const int g_dwPacketKey = 0xA55AA55A;
    static int seedRandMap(int wSeed);
    static unsigned char mapRecvByte(int cbData);
    static unsigned char mapSendByte(int cbData);
};

#endif /* defined(__cctest01__kCipher__) */
