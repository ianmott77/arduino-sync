#include "TimeSyncServer.h"

TimeSyncServer::TimeSyncServer(Timing * time, Connection * connection, bool logging){
    this->time = time;
    this->connection = connection;
    this->logging = logging;
}

void TimeSyncServer::init(){

}

void TimeSyncServer::exec(){
    if(this->connection->available()){
        Buffer * buf = this->connection->receive();
        if(buf != NULL){
            Buffer * now = new Buffer(time->now());
            if(this->logging){
                Serial.print(F("Client Time: "));
                Serial.println(buf->size());
                Serial.print(F("Server Time: "));
                Serial.println(now->toLong());
            }
            delete buf;
            if(this->connection->send(now)){
                if(this->logging){
                    Serial.print(F("Sending: "));
                    Serial.println(now->toLong());
                }
            }else{
                Serial.print(F("Sending: "));
                Serial.print(now->toLong());
                Serial.println(F(" Failed"));
            }
            delete now;
        }else{
            delete buf; 
            Serial.println(F("Reveived Empty Buffer!"));
        }
    }
}