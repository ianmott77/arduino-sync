#include "Connection.h"
Connection::Connection(uint8_t connected, bool logging){

    this->connected = connected;
    this->logging = logging;
    this->bps = 0.00;
}

bool Connection::send(Buffer * buffer){
    uint8_t * size = BufferConverter::intToBuffer(buffer->size());
    Packet * sizePack = new Packet(size, 2);
    if (this->write(sizePack))
    {
        if(this->logging){
            uint8_t * temp = sizePack->data;
            Serial.print(F("Packet Data "));
            for(int j = 0; j < sizePack->size; j++){
                Serial.print(temp[j]);
                Serial.print(F(", "));
            }
            Serial.println();
            Serial.flush();
        }
        for(int i = 0; i < buffer->packetStack->size(); i++){
            if(!this->write(buffer->packetStack->get(i))){
                return false;
            }
        }
        delete size;
        delete sizePack;
    }else{
        delete size;
        delete sizePack;
        return false;
    }
    return true;
}

Buffer * Connection::receive(){
    this->start = millis();
    Packet * sizePack = this->read(2);
    if(this->logging){
        Serial.print(F("Size Packet: "));
        for(int i = 0; i < 2; i++){
            Serial.print(sizePack->data[i]);
            Serial.print(F(", "));
        }
        Serial.println();
        Serial.flush();
    }
    if(sizePack != NULL){
        int incomingSize = BufferConverter::bufferToInt(sizePack->data);
        uint8_t data[incomingSize];
        int byteCount = 0;
        int numPackets = ceil(incomingSize / MAX_PACKET_SIZE);
        for (int i = 0; i < numPackets; i++)
        {
            int remaining = incomingSize - byteCount;
            int nextPackSize = (remaining > MAX_PACKET_SIZE) ? MAX_PACKET_SIZE : remaining;
            Packet * incoming = this->read(nextPackSize);
            if(incoming != NULL){
                for(int j = 0; j < nextPackSize; j++){
                    data[byteCount] = incoming->data[j];
                    byteCount++;    
                }
            }else{
                Serial.println(F("Data packet wasn't recieved correctly!"));
                Serial.print(F("Packet Size: "));
                Serial.println(incomingSize);
                delete incoming;
                return NULL;
            }
            delete incoming;
        }
        this->receiveTime = millis() - this->start;
        this->bps = 1000.00/(this->receiveTime/(incomingSize + 2));
        delete sizePack;
        return new Buffer(data, incomingSize);
    }else{
        Serial.println(F("Size packet wasn't recieved!"));
        delete sizePack;
        return NULL;
    }
}