//
//  kByteBuffer.h
//
//  Created by kael on 12/19/12.
//
//

#ifndef __kByteBuffer__
#define __kByteBuffer__
#include <vector>
#define DEFAULT_SIZE 64


typedef unsigned char byte;
typedef std::vector<byte> buffType;
class kByteBuffer
{
private:
    // read position/write position
    unsigned int rpos, wpos;
    buffType buf;
    template <typename T>
    T read()
    {
        T data = read<T>(rpos);
        rpos += sizeof(T);
        return data;
    }
    
    template <typename T>
    T read(unsigned int pos)const
    {
        if(pos + sizeof(T) <= buf.size())
            return *((T*)&buf[pos]);
        return 0;
    }
    
    template<typename T>
    void append(T data)
    {
        unsigned int s = sizeof(data);
        if (size() < (wpos + s))
            buf.resize(wpos + s);
        memcpy(&buf[wpos], (byte*)&data, s);
        wpos += s;
    }
    
    template<typename T>
    void insert(T data,unsigned int index)
    {
        unsigned int s = sizeof(data);
        if((s + index) > size())
            return;
        memcpy(&buf[index], (byte*)&data, s);
        wpos += index + sizeof(data);
    }
    
public:
    byte* getContent() {return &buf[0];}
    const byte* getConstContent()const {return &buf[0];}
    kByteBuffer(unsigned int size = DEFAULT_SIZE);
    kByteBuffer(byte* arr, unsigned int size);
    ~kByteBuffer();
    // Number of bytes from the current read position till the end of the buffer
    unsigned int bytesRemaining();
    // clear data and reset write/read position
    void clear();
    kByteBuffer* clone();
    bool equals(kByteBuffer* other);
    void resize(unsigned int newsize);
    // Size of internal vector
    unsigned int size();
    // linear search for key's index 
    template <typename T> int find(T key, unsigned int start=0)
    {
        int ret = -1;
        unsigned int len = buf.size();
        for(unsigned int i = start; i < len; i++) {
            T data = read<T>(i);
            if((key != 0) && (data == 0))
                break;
            // Key was found in array
            if(data == key) {
                ret = i;
                break;
            }
        }
        return ret;
    }
    
    // Replacement
    void replace(byte key, byte rep, unsigned int start = 0, bool firstOccuranceOnly=false);
    // Read
    // Relative peek. Reads and returns the next byte in the buffer from the current position but does not increment the read position
    byte peek();
    // Relative get method. Reads the byte at the buffers current position then increments the position
    byte get();
    // Absolute get method. Read byte at index,and not increse the read position
    byte get(unsigned int index);
    // Absolute read into and array buf of length len
    void getBytes(byte* buf, unsigned int len);
    // variable type
    char getChar();
    char getChar(unsigned int index); // Absolute
    double getDouble();
    double getDouble(unsigned int index);
    float getFloat();
    float getFloat(unsigned int index);
    int getInt();
    int getInt(unsigned int index);
    long getLong();
    long getLong(unsigned int index);
    short getShort();
    short getShort(unsigned int index);
    // Write
    // Relative write of the entire contents of another ByteBuffer (src)
    void put(kByteBuffer* src); 
    void put(byte b);
    // Absolute write at index
    void put(byte b, unsigned int index); 
    void putBytes(const byte* b, unsigned int len);
    // Absolute write starting at index
    void putBytes(const byte* b, unsigned int len, unsigned int index);
    void putChar(char value); 
    void putChar(char value, unsigned int index); 
    void putDouble(double value);
    void putDouble(double value, unsigned int index);
    void putFloat(float value);
    void putFloat(float value, unsigned int index);
    void putInt(int value);
    void putInt(int value, unsigned int index);
    void putLong(long value);
    void putLong(long value, unsigned int index);
    void putShort(short value);
    void putShort(short value, unsigned int index);
    // Buffer Position Accessors
    void setReadPos(unsigned int r) {
        rpos = r;
    }
    
    int getReadPos() {
        return rpos;
    }
    
    void setWritePos(unsigned int w) {
        wpos = w;
    }
    
    int getWritePos() {
        return wpos;
    }
public:
    static void endian_swap(unsigned int* x)
    {
        *x = (*x>>24) |
        ((*x<<8) & 0x00FF0000) |
        ((*x>>8) & 0x0000FF00) |
        (*x<<24);
    }
    static void endian_swap_s(unsigned short* x)
    {
        *x = (((*x & 0xff00) >> 8) | ((*x & 0x00ff) << 8));
    }
    // help function
public:
    void toBigEndian();
    void toSmallEndian();
};

#endif /* defined(__kByteBuffer__) */
