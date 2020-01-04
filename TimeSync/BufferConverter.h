#ifndef BUFFERCONVERTER_H
#define BUFFERCONVERTER_H

#include <Arduino.h>

class BufferConverter
{
public:
   static uint8_t * intToBuffer(int);
   static int bufferToInt(uint8_t *);
   static unsigned long bufferToLong(uint8_t *);
   static uint8_t * longToBuffer(unsigned long);
};

#endif