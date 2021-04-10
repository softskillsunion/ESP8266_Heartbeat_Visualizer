#include "Wire.h"
#include "MAX30100_PulseOximeter.h"

float bpm, spO2;

PulseOximeter pox;

void setup()
{
  Serial.begin(115200);
  Serial.print("Initializing pulse oximeter..");
  if (!pox.begin())
  {
    Serial.println("FAILED");
    for (;;)
      ;
  }
  else
  {
    Serial.println("SUCCESS");
  }

  pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
  pox.setOnBeatDetectedCallback(onBeatDetected);
}

void loop()
{
  pox.update();

  bpm = pox.getHeartRate();
  spO2 = pox.getSpO2();
}

void onBeatDetected()
{
  Serial.print("Beat!");
  Serial.print(bpm);
  Serial.print("; ");
  Serial.println(spO2);
}