#ifndef BUFFER_H
#define BUFFER_H

#include "BufferConverter.h"
#include "Packet.h"
#ifndef STACK_H
    #include "Stack.h"
#endif
#define INT 1
#define LONG 2
#define STRING 3
#define BUFFER 4

class Buffer
{
    private:
    void makePacketStack(uint8_t *);
    void init(uint8_t *);
    int length;

public:
    Buffer(int);
    Buffer(unsigned long);
    Buffer(char *);
    Buffer(uint8_t *, int);
    Buffer(Packet*);
    Buffer(Buffer*);
    ~Buffer();
    char * toString();
    int toInt();
    unsigned long toLong();
    int size();
    int type;
    Stack<Packet*> * packetStack;

};

#endif

