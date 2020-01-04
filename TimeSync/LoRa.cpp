#include "LoRa.h"

LoRa::LoRa(uint8_t address, uint8_t connected, bool logging, int cs, int rst, int intt, int led, float freq) : Connection(connected, logging)
{
    this->address = address;
    this->cs = cs;
    this->rst = rst;
    this->intt = intt;
    this->led = led;
    this->freq = freq;
    this->driver = new RH_RF95(this->cs, this->intt);
    this->manager = new RHReliableDatagram(*this->driver, this->address);
    this->logging = logging;
}

LoRa::~LoRa() {}

int LoRa::getCS()
{
    return this->cs;
}

int LoRa::getRST()
{
    return this->rst;
}

int LoRa::getINT()
{
    return this->intt;
}

int LoRa::getLED()
{
    return this->led;
}

uint8_t LoRa::getAddress()
{
    return this->address;
}

float LoRa::getFrequency()
{
    return this->freq;
}

void LoRa::setCS(int cs)
{
    this->cs = cs;
}

void LoRa::setRST(int rst)
{
    this->rst = rst;
}

void LoRa::setINT(int intt)
{
    this->intt = intt;
}

void LoRa::setLED(int led)
{
    this->led = led;
}

void LoRa::setAddress(uint8_t address)
{
    this->address = address;
}

void LoRa::setFrequency(float freq)
{
    this->freq = freq;
}

void LoRa::reset()
{
    digitalWrite(this->getRST(), LOW);
    delay(10);
    digitalWrite(this->getRST(), HIGH);
    delay(10);
}

bool LoRa::available()
{
    return this->manager->available();
}

bool LoRa::init()
{
    
    pinMode(this->getRST(), OUTPUT);
    digitalWrite(this->getRST(), HIGH);
    
    if (!this->manager->init())
    {
        return false;
    }

    this->driver->setSpreadingFactor(9);
    this->driver->setSignalBandwidth(125000);
    this->driver->setCodingRate4(8);
    this->driver->setTxPower(23);

    if (!this->driver->setFrequency(this->getFrequency()))
    {
        return false;
    }

    return true;
}

bool LoRa::write(Packet *packet)
{
    for (int i = 0; i < 5; i++)
    {
        if(this->logging){
            Serial.print(F("Sending Size "));
            Serial.print(packet->size);
            Serial.print(F(" Packet Data: "));
            for(int j = 0; j < packet->size; j++){
                Serial.print(packet->data[j]);
                Serial.print(F(", "));
            }
            Serial.println();
        }
        if (this->manager->sendtoWait(packet->data, packet->size, this->connected))
        {
            return true;
        }
    }
    return false;
}

Packet *LoRa::read(uint8_t size)
{
        uint8_t from;
        uint8_t len = size;
        uint8_t * data = (uint8_t *) malloc(size);
        if (this->manager->recvfromAckTimeout(data, &len, 2000, &from))
        {
            if(this->logging){
                Serial.print(len);
                Serial.print(F(" Bytes Received Data: "));
                for(int i = 0; i < len; i++){
                    Serial.print(data[i]);
                    Serial.print(", ");
                }
                Serial.println();
            }

            Packet * ret = new Packet(data, size);

            delete data;

            return ret;
        }
        delete data;
        return NULL;
    
}