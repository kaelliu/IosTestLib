//
//  kJsonProtocolBase.h
//
//  Created by kael on 12/19/12.
//
//

#ifndef __kJsonProtocolBase__
#define __kJsonProtocolBase__

#include <map>
#include <string>
#include "json/json.h"
class kByteBuffer;
class kSocket;
typedef std::map<std::string,Json::Value> ptotocol_type;
class kJsonProtocolBase
{
protected:
    // json value contains array type
    ptotocol_type _data;
public:
    void addValue(const std::string& key,const Json::Value& value){_data[key] = value;}
    Json::Value getValue(const std::string& key)const{return _data.find(key)->second;}
    std::string toJson()const;
    void fromJson(const std::string& json);
    static Json::Reader _reader;
//    void toBuffer(kByteBuffer&);
    void toEncryptBufferJavaServer(kByteBuffer&);
    void sendToJavaServer(kSocket& sock);
    void fromBuffer(const unsigned char* pbuffer,unsigned int bufflen);
    void fromBufferDecrypt(const unsigned char* pbuffer,unsigned int bufflen);
    void fromBufferDecryptJavaServer(const unsigned char* pbuffer,unsigned int bufflen);
};

#endif /* defined(__kJsonProtocolBase__) */
