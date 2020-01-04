#include "Packet.h"

Packet::Packet(uint8_t * data, int size)
{
    this->size = size;
    this->data = (uint8_t*) malloc(this->size);
    memcpy(this->data, data, this->size);
}

Packet::~Packet()
{
    free(this->data);
}