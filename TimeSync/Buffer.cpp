#include "Buffer.h"

Buffer::Buffer(int data)
{
    uint8_t * buffer = BufferConverter::intToBuffer(data);
    this->length = 2;
    this->type = INT;
    this->packetStack = new Stack<Packet *>(1);
    this->packetStack->add(new Packet(buffer, this->length));
    delete buffer;
}

Buffer::Buffer(unsigned long data)
{
    uint8_t * buffer = BufferConverter::longToBuffer(data);
    this->length = 4;
    this->type = LONG;
    this->packetStack = new Stack<Packet*>(1);
    this->packetStack->add(new Packet(buffer, this->length));
    delete buffer;
}

Buffer::Buffer(char *data)
{
    this->length = strlen(data);
    this->init((uint8_t *)data);
    this->type = STRING;
}

Buffer::Buffer(uint8_t *data, int size)
{
    this->length = size;
    this->init(data);
    this->type = BUFFER;
}

Buffer::Buffer(Buffer * input){
    this->length = input->size();
    this->packetStack = input->packetStack;
    this->type = BUFFER;
}
Buffer::Buffer(Packet * data){
    this->length = data->size;
    this->init(data->data);
    this->type = BUFFER;
}


Buffer::~Buffer()
{
     delete this->packetStack;
}

void Buffer::init(uint8_t *data)
{
    this->makePacketStack(data);
}

void Buffer::makePacketStack(uint8_t * data)
{
    int numPackets = ceil(this->length / MAX_PACKET_SIZE);
    this->packetStack = new Stack<Packet *>(numPackets);
    int byteCount = 0;
    for (int i = 0; i < numPackets; i++)
    {
        int remaining = this->length - byteCount;
        int nextPackSize = (remaining > MAX_PACKET_SIZE) ? MAX_PACKET_SIZE : remaining;
        uint8_t buf[nextPackSize];
        for (int j = 0; j < nextPackSize; j++)
        {
            buf[j] = data[byteCount];
            byteCount++;
        }
        this->packetStack->add(new Packet(buf, nextPackSize));
    }
}

char * Buffer::toString()
{
    char * str = (char*) malloc(this->length+1);
    int byteCount = 0;
    int numPackets = ceil(this->length / MAX_PACKET_SIZE);
    for (int i = 0; i < numPackets; i++)
    {
        Packet *incoming = this->packetStack->get(i);
        int remaining = this->length - byteCount;
        int nextPackSize = (remaining > MAX_PACKET_SIZE) ? MAX_PACKET_SIZE : remaining;
        for (int j = 0; j < nextPackSize; j++)
        {
            str[byteCount] = (char) incoming->data[j];
            byteCount++;
        }
    }
    str[byteCount] = '\0';
    return str;
}

int Buffer::toInt(){
    return BufferConverter::bufferToInt(this->packetStack->get(0)->data);
}

unsigned long Buffer::toLong(){
    return BufferConverter::bufferToLong(this->packetStack->get(0)->data);
}

int Buffer::size(){
    return this->length;
}