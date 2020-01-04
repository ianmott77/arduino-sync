#include <LoRa.h>
#include <TimeSyncServer.h>
#include <MemoryFree.h>


TimeSyncServer * server;
void setup()
{
  // put your setup code here, to run once:
  Serial.begin(2000000);
  while (!Serial);
  Timing * time = new Timing(true);
  LoRa * radio = new LoRa(2, 1);
  if (!radio->init())
  {
    Serial.println(F("Radio initialization failed!"));
    return;
  }
  server = new TimeSyncServer(time, radio);
  Serial.println(F("Setup Successful"));
}

void loop()
{
    server->exec();
}