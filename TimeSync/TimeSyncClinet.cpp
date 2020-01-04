#include "TimeSyncClient.h"

TimeSyncClient::TimeSyncClient(Timing * time, Connection * connection, bool logging)
{
    this->time = time;
    this->connection = connection;
    this->logging = logging;
    this->stageOne = new ClientStageOne(this->time, this->connection, this->logging);
    this->stageTwo = new ClientStageTwo(this->time, this->connection, this->logging);
    this->lastSync = 0.0;
    this->syncTime = 0.0;
    this->count = 0;
    this->start = 0;
    this->done = false;
}

TimeSyncClient::~TimeSyncClient()
{
    delete this->stageOne;
    delete this->stageTwo;
}

void TimeSyncClient::init(){

}

void TimeSyncClient::exec(){
    if(!this->stageOne->done){
        if(this->count == 0){
            this->start = millis();
        }
        this->stageOne->exec();
    }else if(this->stageOne->done && !this->stageTwo->done){
        this->stageTwo->exec();
        this->lastSync = time->elapsed();
    }else if(this->stageTwo->done){
        this->syncTime = (millis() - this->start)/1000.0;
        this->done = true;
        if(this->logging){
            Serial.print(F("Time to sync: "));
            Serial.print(syncTime);
            Serial.println("s,");
            Serial.flush();
        }
    }
    this->count++;
}