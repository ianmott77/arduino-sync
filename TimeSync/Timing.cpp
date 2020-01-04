#include "Timing.h"

Timing::Timing(bool logging)
{
  
    this->first = 0;
    this->dif = 0;
    this->factor = 0.00;
    this->logging = logging;
    this->startMils = 0;
    this->endMils = 0;
    this->delays = new Stack<int>(10);
    this->avgDelay = 0.00;
    this->mils = 0;
}

unsigned long Timing::now(){
    this->mils = millis();
    if(this->factor > 0.00 || this->factor < 0.00){
        /*
        adf = adjusted drift factor
        s = seconds
        now = adjusted
        ftm = first
        f = factor
        s = (now - ftm)/1000.00 (this gives how man seconds have passed since we first synced)
        adf = s*f (here we multiply the ms/s drift by the number of seconds that have gone by to get the number of milliseconds to add to the time)
        */
        //adjust the time for the diffrence between the clocks
        if(this->logging){
            Serial.print(F("first: "));
            Serial.println(this->first);
            Serial.print(F("now: "));
            Serial.println(this->mils);
            Serial.print(F("dif: "));
            Serial.println(this->dif);
            Serial.print(F("factor: "));
            Serial.println(this->factor);
        }

        unsigned long a = this->mils + this->avgDelay + this->dif;
        if(this->logging){
            Serial.print(F("a: "));
            Serial.println(a);
        }

        //calculate the elapsed seconds between when we first synced and now
        float s = (a - this->first)/1000.00;
        if(this->logging){
            Serial.print(F("s: "));
            Serial.println(s);
        }

        //multiply the seconds by the ms/s that the clocks drift apart to obtain the adjusted drift factor
        float adf =  s * this->factor;
        if(this->logging){
            Serial.print(F("adf: "));
            Serial.println(adf);
        }

        unsigned long final = round(a - adf);

        if(this->logging){
            Serial.print(F("a - adf:"));
            Serial.println(a - adf);
            Serial.print(F("final: "));
            Serial.println(final);
            Serial.flush();
        }
        return final;
    }else{
        return this->mils;
    }
}

float Timing::delay(){
    int highestTime = this->delays->get(0);
    int lowestTime = this->delays->get(0);
    float sum = 0.00;
    for(int i = 0; i < this->delays->size(); i++){
        int delay = this->delays->get(i);
        if(delay >= highestTime){
            highestTime = delay;
        }
        if(delay <= lowestTime){
            lowestTime = delay;
        }
        sum += delay;
    }
    sum -= lowestTime;
    sum -= highestTime;
    this->avgDelay = (sum/(this->delays->size() - 2.00))/2.00;
    return this->avgDelay;
}

float Timing::elapsed(){
    this->mils = millis();
    return ((this->mils + this->avgDelay + this->dif) - this->first)/1000.00;
}