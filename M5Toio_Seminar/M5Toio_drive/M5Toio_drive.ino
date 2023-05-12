//#include <M5StickC.h>
#include <M5StickCPlus.h>
#include <Wire.h>
#include <Toio.h>

Toio toio;
ToioCore* toiocore = nullptr;

void setup()
{
  M5.begin();

  M5.Lcd.setRotation(1);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextSize(1);

  M5.Lcd.print("M5Toio_drive.ino");

  M5.IMU.Init();

  //Serial.println("scan toio");
  std::vector<ToioCore*> toiocore_list = toio.scan(3);
  size_t n = toiocore_list.size();

  toiocore = toiocore_list.at(0);
  //Serial.println("connect to cubes with BLE");
  ToioCore* toiocore = toiocore_list.at(0);
  bool connected = toiocore->connect();

  toiocore->turnOnLed(255, 255, 255);
}

float accX, accY, accZ;

void loop()
{
  M5.update();

  M5.IMU.getAccelData(&accX, &accY, &accZ);
  M5.Lcd.setCursor(0, 15);
  M5.Lcd.printf("Acc:   %.2f   %.2f   %.2f   ", accX * 10, accY * 10, accZ * 10);

  toio.loop();

  if (!toiocore) {
    return;
  }

  if (M5.BtnB.wasPressed()) {
    if (toiocore->isConnected()) {
      toiocore->disconnect();
      //M5.Lcd.print("disconnect");
    }
    else {
      toiocore->connect();
      //M5.Lcd.print("connect");
    }
    return;
  }

  if (!toiocore->isConnected()) {
    return;
  }

  toiocore->drive(accX * -100, accY * 100);

  delay(3);
}
