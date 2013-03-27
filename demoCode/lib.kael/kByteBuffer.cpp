//
//  kByteBuffer.cpp
//
//  Created by kael on 12/19/12.
//
//

#include "kByteBuffer.h"
kByteBuffer::kByteBuffer(unsigned int size) {
    // resize means resize the space,but reserve means reserve some space
    buf.reserve(size);
    clear();
}

kByteBuffer::kByteBuffer(byte* arr, unsigned int size) {
    // If the provided array is NULL, allocate a blank buffer of the provided size
    if(arr == NULL) {
        buf.reserve(size);
        clear();
    } else {
        // Consume the provided array
        buf.reserve(size);
        clear();
        putBytes(arr, size);
    }
}

kByteBuffer::~kByteBuffer() {
}

unsigned int kByteBuffer::bytesRemaining() {
    return size()-rpos;
}

void kByteBuffer::clear() {
    rpos = 0;
    wpos = 0;
    buf.clear();
}

kByteBuffer* kByteBuffer::clone() {
    kByteBuffer* ret = new kByteBuffer(buf.size());
    
    // Copy data
    for(unsigned int i = 0; i < buf.size(); i++) {
        ret->put(i, (byte)get(i));
    }
    
    // Reset positions
    ret->setReadPos(0);
    ret->setWritePos(0);
    return ret;
}

bool kByteBuffer::equals(kByteBuffer *other)
{
    // is size equal
    if(buf.size() != other->size())
        return false;
    // compare byte
    unsigned int len = size();
    for (unsigned int i=0; i<len; ++i) {
        if ((byte)get(i) != (byte)other->get(i)) {
            return false;
        }
    }
    return true;
}

void kByteBuffer::resize(unsigned int newSize) {
    buf.resize(newSize);
    rpos = 0;
    wpos = 0;
}

unsigned int kByteBuffer::size() {
    return buf.size();
}

void kByteBuffer::replace(byte key, byte rep, unsigned int start, bool firstOccuranceOnly)
{
    unsigned int len = buf.size();
    for(unsigned int i = start; i < len; i++) {
        byte data = read<byte>(i);
        // not found key
        if((key != 0) && (data == 0))
            break;
        // Key was found in array, perform replacement
        if(data == key) {
            buf[i] = rep;
            // find one and return?
            if (firstOccuranceOnly) {
                break;
            }
        }
    }
}

// Read Functions
byte kByteBuffer::peek(){
    return read<byte>(rpos);
}

byte kByteBuffer::get(){
    return read<byte>();
}

byte kByteBuffer::get(unsigned int index) {
    return read<byte>(index);
}

void kByteBuffer::getBytes(byte* buf, unsigned int len){
    for(unsigned int i = 0; i < len; i++) {
        buf[i] = read<byte>();
    }
}

char kByteBuffer::getChar() {
    return read<char>();
}

char kByteBuffer::getChar(unsigned int index) {
    return read<char>(index);
}

double kByteBuffer::getDouble() {
    return read<double>();
}

double kByteBuffer::getDouble(unsigned int index) {
    return read<double>(index);
}

float kByteBuffer::getFloat() {
    return read<float>();
}

float kByteBuffer::getFloat(unsigned int index) {
    return read<float>(index);
}

int kByteBuffer::getInt() {
    return read<int>();
}

int kByteBuffer::getInt(unsigned int index) {
    return read<int>(index);
}

long kByteBuffer::getLong() {
    return read<long>();
}

long kByteBuffer::getLong(unsigned int index) {
    return read<long>(index);
}

short kByteBuffer::getShort() {
    return read<short>();
}

short kByteBuffer::getShort(unsigned int index) {
    return read<short>(index);
}

// Write Functions
void kByteBuffer::put(kByteBuffer* src) {
    int len = src->size();
    for(int i = 0; i < len; i++)
        append<byte>(src->get(i));
}

void kByteBuffer::put(byte b) {
    append<byte>(b);
}

void kByteBuffer::put(byte b, unsigned int index) {
    insert<byte>(b, index);
}

void kByteBuffer::putBytes(const byte* b, unsigned int len) {
    // Insert the data one byte at a time into the internal buffer at position i+starting index
    for(unsigned int i = 0; i < len; i++)
        append<byte>(b[i]);
}

void kByteBuffer::putBytes(const byte* b, unsigned int len, unsigned int index) {
    wpos = index;
    
    // Insert the data one byte at a time into the internal buffer at position i+starting index
    for(unsigned int i = 0; i < len; i++)
        append<byte>(b[i]);
}

void kByteBuffer::putChar(char value) {
    append<char>(value);
}

void kByteBuffer::putChar(char value, unsigned int index) {
    insert<char>(value, index);
}

void kByteBuffer::putDouble(double value) {
    append<double>(value);
}

void kByteBuffer::putDouble(double value, unsigned int index) {
    insert<double>(value, index);
}
void kByteBuffer::putFloat(float value) {
    append<float>(value);
}

void kByteBuffer::putFloat(float value, unsigned int index) {
    insert<float>(value, index);
}

void kByteBuffer::putInt(int value) {
    append<int>(value);
}

void kByteBuffer::putInt(int value, unsigned int index) {
    insert<int>(value, index);
}

void kByteBuffer::putLong(long value) {
    append<long>(value);
}

void kByteBuffer::putLong(long value, unsigned int index) {
    insert<long>(value, index);
}

void kByteBuffer::putShort(short value) {
    append<short>(value);
}

void kByteBuffer::putShort(short value, unsigned int index) {
    insert<short>(value, index);
}

void kByteBuffer::toBigEndian()
{}
void kByteBuffer::toSmallEndian()
{}