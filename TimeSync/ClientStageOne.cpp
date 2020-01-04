#include "ClientStageOne.h"

ClientStageOne::ClientStageOne(Timing * time, Connection * connection, bool logging)
{
    this->time = time;
    this->connection = connection;
    this->count = 0;
    this->logging = logging;
    this->id = 1;
    this->syncStarted = false;
    this->done = false;
}

void ClientStageOne::init(){
    Buffer * starter = new Buffer(-1);
    if(this->connection->send(starter)){
        this->syncStarted = true;
    }
    delete starter;
}

void ClientStageOne::exec(){
    if(this->count < 5){
        Buffer * now = new Buffer(this->time->now());
        if(this->connection->send(now)){
            Buffer * t = this->connection->receive();
            unsigned long them = this->time->now();
            if(them != 0 && them != '\0'){
                this->time->startMils = now->toLong();
                this->time->endMils = them;
                this->time->adjusted = this->time->endMils - this->time->startMils;
                this->time->delays->add(this->time->adjusted);
                if(this->logging){
                    this->log(BufferConverter::bufferToLong(now->packetStack->get(0)->data));
                }
                delete t;
                delete now;
                this->count++;
            }else{
                Serial.print(F("Receiving Failed"));
                delete t;
                delete now;
            }
        }else{
            Serial.print(F("Sending: "));
            Serial.print(now->toLong());
            Serial.println(F(" Failed"));
            delete now;
        }
    }else if(this->count == 5){
        this->time->delay();
        this->done = true;
    }
}

void ClientStageOne::log(unsigned long now){
    Serial.print(F("now: "));
    Serial.println(now);
    Serial.print(F("startMils: "));
    Serial.println(this->time->startMils);
    Serial.print(F("endMils: "));
    Serial.println(this->time->endMils);
    Serial.print(this->count);
    Serial.print(F(") Delay: "));
    Serial.println(this->time->adjusted);
}