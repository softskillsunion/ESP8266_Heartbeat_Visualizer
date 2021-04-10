#include "Wire.h"
#include "MAX30100_PulseOximeter.h"
#include "Servo.h"
#include "Adafruit_NeoPixel.h"

int servoPin = 15;
int ledPin = D5;
int ledPixels = 1;

float bpm, spO2;

bool isBeat = 0; // 偵測到心跳

int posSystole = 55;  // 模擬心室收縮狀態角度
int posDiastole = 90; // 模擬心室舒張狀態角度

PulseOximeter pox;
Servo myservo;
Adafruit_NeoPixel pixels(ledPixels, ledPin, NEO_GRB + NEO_KHZ800);

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

  myservo.attach(servoPin);
  myservo.write(posSystole);
  Serial.println("servo done");

  pixels.begin();
  pixels.setPixelColor(0, pixels.Color(0, 255, 0));
  pixels.show();
}

void loop()
{
  pox.update();

  bpm = pox.getHeartRate();
  spO2 = pox.getSpO2();

  if (bpm > 20 && spO2 > 40)
  {
    if (isBeat == 0)
    {
      pixels.setPixelColor(0, pixels.Color(0, 0, 255));
      pixels.show();
      isBeat = 1;
    }
  }
  else
  {
    pixels.setPixelColor(0, pixels.Color(255, 0, 0));
    pixels.show();
    isBeat = 0;
    if (bpm == 0 && spO2 == 0)
    {
      pixels.setPixelColor(0, pixels.Color(0, 255, 0));
      pixels.show();
    }
  }
}

void onBeatDetected()
{
  Serial.print("Beat!");
  Serial.print(bpm);
  Serial.print("; ");
  Serial.println(spO2);

  if (isBeat)
  {
    if (myservo.read() == posDiastole)
    {
      myservo.write(posSystole);
    }
    else
    {
      myservo.write(posDiastole);
    }
  }
}
