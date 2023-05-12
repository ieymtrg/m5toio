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

  if (!connected) {
    Serial.println("failed to connect cubes");
    return;
  }
  else {
    Serial.println("success to connect cubes");
    return;
  }
}

// data set of do
uint8_t do1_data[6] = {
  3, // kind of control (MIDI = 3)
  1, // how
  1, // num of operation
  100, 60, 100 // operation set
};
uint8_t re_data[6] = {
  3, // kind of control (MIDI = 3)
  1, // how
  1, // num of operation
  20, 62, 255 // operation set
};

uint8_t mi_data[6] = {
  3, // kind of control (MIDI = 3)
  1, // how
  1, // num of operation
  20, 64, 255 // operation set
};

uint8_t fa_data[6] = {
  3, // kind of control (MIDI = 3)
  1, // how
  1, // num of operation
  20, 65, 255 // operation set
};

uint8_t so_data[6] = {
  3, // kind of control (MIDI = 3)
  1, // how
  1, // num of operation
  20, 67, 255 // operation set
};

uint8_t ra_data[6] = {
  3, // kind of control (MIDI = 3)
  1, // how
  1, // num of operation
  20, 69, 255 // operation set
};

uint8_t si_data[6] = {
  3, // kind of control (MIDI = 3)
  1, // how
  1, // num of operation
  20, 71, 255 // operation set
};

uint8_t do2_data[6] = {
  3, // kind of control (MIDI = 3)
  1, // how
  1, // num of operation
  20, 72, 255 // operation set
};

int scalemode = 1;

void loop()
{
  M5.update();

  toio.loop();

  if (!toiocore) {
    return;
  }

  if (!toiocore->isConnected()) {
    return;
  }

  if (M5.BtnB.wasPressed()) {
    scalemode++;
    if (scalemode == 9) {
      scalemode = 1;
    }
  }

  M5.Lcd.setCursor(0, 15);
  M5.Lcd.setTextSize(2);

  switch (scalemode) {
    case 1:
      if (M5.BtnA.isPressed()) {
        toiocore->playSoundRaw(do1_data, 6);
      }
      M5.Lcd.print("do1");
      break;
    case 2:
      if (M5.BtnA.isPressed()) {
        toiocore->playSoundRaw(re_data, 6);
      }
      M5.Lcd.print("re");
      break;
    case 3:
      if (M5.BtnA.isPressed()) {
        toiocore->playSoundRaw(mi_data, 6);
      }
      M5.Lcd.print("mi");
      break;
    case 4:
      if (M5.BtnA.isPressed()) {
        toiocore->playSoundRaw(fa_data, 6);
      }
      M5.Lcd.print("fa");
      break;
    case 5:
      if (M5.BtnA.isPressed()) {
        toiocore->playSoundRaw(so_data, 6);
      }
      M5.Lcd.print("so");
      break;
    case 6:
      if (M5.BtnA.isPressed()) {
        toiocore->playSoundRaw(ra_data, 6);
      }
      M5.Lcd.print("ra");
      break;
    case 7:
      if (M5.BtnA.isPressed()) {
        toiocore->playSoundRaw(si_data, 6);
      }
      M5.Lcd.print("si");
      break;
    case 8:
      if (M5.BtnA.isPressed()) {
        toiocore->playSoundRaw(do2_data, 6);
      }
      M5.Lcd.print("do2");
      break;
    default:
      toiocore->stopSound();
  }

  //delay(3);
}
