#include <LoRa.h>
#include <TimeSyncClient.h>

TimeSyncClient * timeSyncClinet;
Timing * time;
LoRa * radio;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(2000000);
  while (!Serial);

  radio = new LoRa(1, 2);
  time = new Timing();

  if (!radio->init())
  {
    Serial.println(F("Radio initialization failed!"));
    return;
  }

  timeSyncClinet = new TimeSyncClient(time, radio, true);
  Serial.println(F("Setup Successful"));
}

void loop() {
  if(!timeSyncClinet->done){
    timeSyncClinet->exec();
  }
}