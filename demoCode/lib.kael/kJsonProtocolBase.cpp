//
//  kJsonProtocolBase.cpp
//
//  Created by kael on 12/19/12.
//
//

#include "kJsonProtocolBase.h"
#include "kByteBuffer.h"
#include "kCipher.h"
#include "kSocket.h"
Json::Reader kJsonProtocolBase::_reader;

std::string kJsonProtocolBase::toJson()const
{
    Json::FastWriter writer;
    Json::Value item;
    for (std::map<std::string, Json::Value>::const_iterator it = _data.begin(); it!=_data.end(); ++it) {
        item[it->first] = it->second;
    }
    return writer.write(item);
}

void kJsonProtocolBase::fromJson(const std::string& json)
{
    Json::Value root;
    if(_reader.parse(json, root))
    {
        Json::Value::Members members(root.getMemberNames());
        for (Json::Value::Members::iterator it = members.begin(); it != members.end(); ++it)
        {
            _data[*it] = root[*it];
        }
    }
 //   int testover=1;
}

// note:java is big endian,c++ is small endian,so c++ send to java,need to convert to bigendian
// java message back,need convert to small endian and do operate

void kJsonProtocolBase::toEncryptBufferJavaServer(kByteBuffer& kb)
{
    std::string buff = toJson();
    unsigned short _data_len = buff.size();// for json string length
    unsigned short swaped = _data_len;
    kByteBuffer::endian_swap_s(&swaped);
    kb.resize(_data_len);
//    kByteBuffer kb(_data_len);
    kb.putShort(swaped);
    kb.putBytes(kCipher::encryptBuffer((unsigned char*)buff.c_str(), buff.size()),buff.size());
//    return kb.getContent();
}

void kJsonProtocolBase::sendToJavaServer(kSocket& sock)
{
    if(!sock)return;
    std::string buff = toJson();
    unsigned short _data_len = buff.size();// for json string length
    unsigned short swaped = _data_len;
    kByteBuffer::endian_swap_s(&swaped);
    kByteBuffer kb(_data_len + sizeof(unsigned short));// 2 for length
    //    kByteBuffer kb(_data_len);
    kb.putShort(swaped);
    kb.putBytes(kCipher::encryptBuffer((unsigned char*)buff.c_str(), buff.size()),buff.size());
    sock.send_to((char*)kb.getContent(), _data_len + 2);
}

void kJsonProtocolBase::fromBuffer(const unsigned char* pbuffer,unsigned int bufflen)
{
    // alloc size here first,if not alloc,it will alloc each time when not enough
    kByteBuffer kb(bufflen);
    kb.putBytes(pbuffer, bufflen);
    kb.getShort();
    unsigned char buf[bufflen - sizeof(short)];
    kb.getBytes(buf, bufflen - sizeof(short));
    fromJson(std::string((char*)buf));
}

void kJsonProtocolBase::fromBufferDecrypt(const unsigned char* pbuffer,unsigned int bufflen)
{
    // alloc size here first,if not alloc,it will alloc each time when not enough
    kByteBuffer kb(bufflen);
    kb.putBytes(pbuffer, bufflen);
    kb.getShort();
    int datalen = bufflen - sizeof(short);
    unsigned char buf[datalen];
    kb.getBytes(buf, datalen);
    kCipher::decryptBuffer(buf, datalen);
    fromJson(std::string((char*)buf));
}

void kJsonProtocolBase::fromBufferDecryptJavaServer(const unsigned char* pbuffer,unsigned int bufflen)
{
    // alloc size here first,if not alloc,it will alloc each time when not enough
    kByteBuffer kb(bufflen);
    kb.putBytes(pbuffer, bufflen);
    kb.toSmallEndian();
    kb.getShort();
    int datalen = bufflen - sizeof(short);
    unsigned char buf[datalen];
    kb.getBytes(buf, datalen);
    kCipher::decryptBuffer(buf, datalen);
    fromJson(std::string((char*)buf));
}