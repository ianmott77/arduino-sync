#include "ClientStageTwo.h"

ClientStageTwo::ClientStageTwo(Timing * time, Connection * connection, bool logging)
{
    this->time = time;
    this->connection = connection;
    this->logging = logging;
    this->count = 0;
    this->done = false;
}

void ClientStageTwo::init(){};

void ClientStageTwo::exec(){
    this->sync();
}

bool ClientStageTwo::sync(){
    Buffer * nowBuf = new Buffer(this->time->now());
    if(this->connection->send(nowBuf)){
        Buffer * themBuf = this->connection->receive();
        unsigned long now = nowBuf->toLong();
        unsigned long them = themBuf->toLong();
        delete nowBuf;
        delete themBuf;

        if(this->count == 0){
            this->time->dif = them - (now + this->time->avgDelay); 
            this->time->first = now + this->time->avgDelay + this->time->dif;
        }

        this->time->adjusted = (this->time->factor == 0.00) ? now + this->time->avgDelay + this->time->dif : now;
        this->time->drift = this->time->adjusted - them;

        if(this->logging){
            this->log(now, them);
        }

        if(this->time->drift > 5 || this->time->drift < -5 || this->done){
            unsigned long tempNow = this->time->mils + this->time->avgDelay + this->time->dif;
            this->time->factor = (tempNow - them) / ((tempNow - this->time->first)/1000.000000);
            this->done = true;
        }
        this->count++;
    }
}

void ClientStageTwo::log(unsigned long now, unsigned long them){
    if(this->count == 0){
        Serial.print(F("Me: "));
        Serial.println(now);
        Serial.print(F("Them: "));
        Serial.println(them);
        Serial.print(F("Dif: "));
        Serial.println(this->time->dif);
        Serial.print(F("First: "));
        Serial.println(this->time->first);
        Serial.print(F("Count"));
        Serial.print(F("    ,"));
        Serial.print(F("Elapsed Seconds"));
        Serial.print(F("  ,"));
        Serial.print(F("Me "));
        Serial.print(F("          ,"));
        Serial.print(F("Them "));
        Serial.print(F("        ,"));
        Serial.print(F("Adjusted  "));
        Serial.print(F("   ,"));
        Serial.print(F("Drift  "));
        Serial.print(F("      ,"));
        Serial.print(F("Drift Ms/s: "));
        Serial.print(F("   "));
        Serial.println();
    }
    Serial.print(this->count);
    Serial.print(F("        ,"));
    Serial.print(((this->time->mils + this->time->avgDelay + this->time->dif) - this->time->first)/1000.0000, 4);
    Serial.print(F("        ,"));
    Serial.print(this->time->mils);
    Serial.print(F("        ,"));
    Serial.print(them);
    Serial.print(F("        ,"));
    Serial.print(this->time->adjusted);
    Serial.print(F("        ,"));
    Serial.print(this->time->drift);
    Serial.print(F("        ,"));
    Serial.print(this->time->factor, 4);
    Serial.println();
    Serial.flush();
}