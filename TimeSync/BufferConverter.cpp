#include "BufferConverter.h"

uint8_t *BufferConverter::intToBuffer(int data)
{
    uint8_t * buf = (uint8_t*) malloc(2);
    buf[0] = (data >> 8) & 0xFF;
    buf[1] = data & 0xFF;
    return buf;
}

int BufferConverter::bufferToInt(uint8_t * data)
{
    int val;
    val = data[0] << 8;
    val |= data[1] & 0xFF;
    return val;
}

uint8_t * BufferConverter::longToBuffer(unsigned long data){
    uint8_t * buf = (uint8_t*) malloc(4);
    for(int i = 0; i < 4; i++){
        buf[i] = (data >> (i*8)) & 0xFF;
    }
    return buf;
}

unsigned long BufferConverter::bufferToLong(uint8_t * data){
    union{
        uint8_t buf[4];
        long val;
    } long_union;

    for(int i = 0; i < 4; i++){
        long_union.buf[i] = data[i];
    }

    return long_union.val;
}