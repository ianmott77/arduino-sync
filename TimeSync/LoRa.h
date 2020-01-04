#ifndef LORA_H
#define LORA_H

#include "Connection.h"
#include <SPI.h>
#include <RH_RF95.h>
#include <RHReliableDatagram.h>

class LoRa : public Connection 
{
private:
    int cs;
    int rst;
    int intt;
    int led;
    uint8_t address;
    float freq;
    bool logging;
    RHReliableDatagram * manager;

public:
    LoRa(uint8_t, uint8_t, bool logging = false, int cs = 4, int rst = 2, int intt = 3, int led = 13, float freq = 915.0);
    ~LoRa();
    int getCS();
    int getRST();
    int getINT();
    int getLED();
    uint8_t getAddress();
    float getFrequency();
    void setCS(int);
    void setRST(int);
    void setINT(int);
    void setLED(int);
    void setAddress(uint8_t);
    void setFrequency(float);
    void reset();
    virtual bool available();
    virtual bool init();
    virtual bool write(Packet *);
    virtual Packet * read(uint8_t);
    RH_RF95 * driver;
};

#endif

