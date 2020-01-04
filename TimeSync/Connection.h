#ifndef CONNECTION_H
#define CONNECTION_H

#include "Packet.h"
#include "Buffer.h"
#include "BufferConverter.h"

class Connection
{

private:
    long start;
    bool logging;
public:
    Connection(uint8_t, bool logging = false);
    virtual bool init() = 0;
    virtual bool write(Packet *) = 0;
    virtual Packet * read(uint8_t) = 0;
    virtual bool available() = 0;
    virtual bool send(Buffer *);
    virtual Buffer * receive();
    uint8_t connected;
    float bps;
    float receiveTime;
};

#endif
