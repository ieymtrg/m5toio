/*
   Toio Seminar
   M5Toio Human Code
   Date : 2022/07/20
*/

//#include <M5StickC.h> // c or cplus
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
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.print("M5Toio_Human.ino");

  M5.IMU.Init();

  std::vector<ToioCore*> toiocore_list = toio.scan(3);
  size_t n = toiocore_list.size();

  toiocore = toiocore_list.at(0);
  ToioCore* toiocore = toiocore_list.at(0);
  bool connected = toiocore->connect();

  toiocore->turnOnLed(0, 255, 0); // human -> green

  if (!connected) {
    //Serial.println("failed to connect cubes");
    return;
  }
  else {
    //Serial.println("success to connect cubes");
    return;
  }
}

float accX, accY, accZ;
const float th = 4;
int sound_id = 0;

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

  if (M5.BtnB.wasReleased()) {
    if (toiocore->isConnected()) {
      toiocore->disconnect();
    }
    return;
  }

  if (!toiocore->isConnected()) {
    return;
  }

  // aori
  if (M5.BtnA.wasPressed()) {
    toiocore->playSoundEffect(sound_id);
    toiocore->turnOnLed(0, 0, 255); // aori human -> blue
    sound_id++;
    if (sound_id == 11) {
      sound_id = 0;
    }
  }

  /*
     Human skill -> rapid turn
  */
  if (accX * 10 > th) {
    toiocore->controlMotor(false, accX * 30, false, accX * 30); // back
  }
  else if (accX * 10 <= -1 * th) {
    toiocore->controlMotor(true, accX * -30, true, accX * -30); // front
  }
  else if (accY * 10 > th) {
    toiocore->controlMotor(true, accY * 40, false, accY * 40);  // right
  }
  else if (accY * 10 <= -1 * th) {
    toiocore->controlMotor(false, accY * -40, true, accY * -40); // left
  }
  else {
    toiocore->controlMotor(true, 0, true, 0); // stop
  }

  delay(3);
}
