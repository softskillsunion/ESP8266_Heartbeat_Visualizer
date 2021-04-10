#include "Wire.h"
#include "MAX30100_PulseOximeter.h"
#include "Servo.h"
#include "Adafruit_NeoPixel.h"
#include "BlynkSimpleEsp8266.h"

/***************↓↓↓↓↓ 更改設定值 ↓↓↓↓↓***************/
// WIFI
char ssid[] = "SSID 名稱";
char wifipwd[] = "SSID 密碼";

// Blynk App 建立 Project 後，mail 的 auth key
char auth[] = "Blynk 金鑰";
/***************↑↑↑↑↑ 更改設定值 ↑↑↑↑↑***************/

#define BLYNK_PRINT Serial

int servoPin = 15;
int ledPin = D5;
int ledPixels = 1;

float bpm, spO2;

bool isBeat = 0;       // 偵測到心跳
bool swVisualizer = 1; // 心跳模擬器開關
bool swLed = 1;        // 燈號顯示開關

int lastColor; // 紀錄最後燈號顏色

unsigned long startBeatTime = 0; // 心跳開始時間
int uploadInterval = 5;          // 上傳數據間隔時間(更新頻率)

int posSystole = 55;  // 模擬心室收縮狀態角度
int posDiastole = 90; // 模擬心室舒張狀態角度

PulseOximeter pox;
Servo myservo;
Adafruit_NeoPixel pixels(ledPixels, ledPin, NEO_GRB + NEO_KHZ800);

void setup()
{
  Serial.begin(115200);

  pixels.begin();

  setLedColor(0, pixels.Color(0, 255, 255));

  Blynk.begin(auth, ssid, wifipwd);

  delay(500);

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

  Blynk.virtualWrite(V2, swVisualizer);
  Blynk.virtualWrite(V3, swLed);
  Blynk.virtualWrite(V4, uploadInterval);

  setLedColor(0, pixels.Color(0, 255, 0));
}

void loop()
{
  pox.update();
  Blynk.run();

  bpm = pox.getHeartRate();
  spO2 = pox.getSpO2();

  if (bpm > 20 && spO2 > 40)
  {
    if (isBeat == 0)
    {
      startBeatTime = millis();
      setLedColor(0, pixels.Color(0, 0, 255));
      isBeat = 1;
    }
    if (millis() - startBeatTime > uploadInterval * 1000)
    {
      sendSensor();
      startBeatTime = millis();
      Serial.print("Send Data! ");
      Serial.print(bpm);
      Serial.print("; ");
      Serial.println(spO2);
    }
  }
  else
  {
    setLedColor(0, pixels.Color(255, 0, 0));
    isBeat = 0;
    if (bpm == 0 && spO2 == 0)
    {
      setLedColor(0, pixels.Color(0, 255, 0));
    }
  }
}

void onBeatDetected()
{
  Serial.print("Beat!");
  Serial.print(bpm);
  Serial.print("; ");
  Serial.println(spO2);

  if (swVisualizer == 1 && isBeat == 1)
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

void setLedColor(int pixelIndex, int color)
{
  lastColor = color;
  if (swLed)
  {
    pixels.setPixelColor(pixelIndex, color);
    pixels.show();
  }
}

void sendSensor()
{
  Blynk.virtualWrite(V0, bpm);
  Blynk.virtualWrite(V1, spO2);
}

BLYNK_WRITE(V2)
{
  int x = param.asInt();
  Serial.println(x);
  swVisualizer = x;
}

BLYNK_WRITE(V3)
{
  int x = param.asInt();
  Serial.println(x);
  swLed = x;
  if (x)
  {
    pixels.setPixelColor(0, lastColor);
  }
  else
  {
    pixels.setPixelColor(0, pixels.Color(0, 0, 0));
  }
  pixels.show();
}

BLYNK_WRITE(V4)
{
  int x = param.asInt();
  Serial.println(x);
  uploadInterval = x;
}