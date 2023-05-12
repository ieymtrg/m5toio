//#include <M5StickC.h>
#include <M5StickCPlus.h>
#include <Wire.h>
#include <Toio.h>

// object of toio
Toio toio;
ToioCore* toiocore = nullptr;

void setup()
{
  M5.begin();

  M5.Lcd.setRotation(1);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextSize(1);

  M5.IMU.Init();

  Serial.println("scan toio");
  std::vector<ToioCore*> toiocore_list = toio.scan(3); // search for cubes 3s
  size_t n = toiocore_list.size();

  if (n == 0) {
    Serial.println("not found cube");
    return;
  }
  else {
    Serial.printf("found %d cubes\n", n);
  }

  toiocore = toiocore_list.at(0);
  Serial.println("connect to cubes with BLE");
  ToioCore* toiocore = toiocore_list.at(0);
  bool connected = toiocore->connect();

  toiocore->turnOnLed(255, 255, 255); // turn on toio's led (RGB)

  std::string mac = toiocore->getAddress();
  Serial.println(mac.c_str());

  std::string name = toiocore->getName();
  Serial.println(name.c_str());

  if (!connected) {
    Serial.println("failed to connect cubes");
    return;
  }
  else {
    Serial.println("success to connect cubes");
    return;
  }
}

float accX, accY, accZ; // acceleration of m5
const float th = 3; // threshhold of acceleration

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

  M5.Lcd.setCursor(0, 30);

  if (M5.BtnB.wasPressed()) {
    if (toiocore->isConnected()) {
      toiocore->disconnect();
      M5.Lcd.print("disconnect");
    }
    else {
      toiocore->connect();
      M5.Lcd.print("connect");
    }
    return;
  }

  if (!toiocore->isConnected()) {
    return;
  }

  /*
    void controlMotor(bool ldir, uint8_t lspeed, bool rdir, uint8_t rspeed, uint16_t duration = 0);
    spd 0~115
  */

  // control toio mode 0
  if (accX * 10 > th) {
    toiocore->controlMotor(false, accX * 30, false, accX * 30); // back
  }
  else if (accX * 10 <= -1 * th) {
    toiocore->controlMotor(true, accX * -30, true, -accX * 30); // front
  }
  else if (accY * 10 > th) {
    toiocore->controlMotor(true, accY * 30, false, accY * 30); // right
  }
  else if (accY * 10 <= -1 * th) {
    toiocore->controlMotor(false, accY * -30, true, accY * -30); // left
  }
  else {
    toiocore->drive(0, 0);
  }

  delay(3);
  //delay(5);
}
