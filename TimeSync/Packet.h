#ifndef PACKET_H
#define PACKET_H
#include <Arduino.h>

#define MAX_PACKET_SIZE 128.00

class Packet
{    
public:
    Packet(uint8_t *, int);
    ~Packet();
    uint8_t * data;
    uint8_t size;
};

#endif
