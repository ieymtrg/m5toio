#include <M5StickCPlus.h>
#include <Toio.h>

// object of toio
Toio toio;

void setup() {
  M5.begin();

  Serial.println("scan toio");
  std::vector<ToioCore*> toiocore_list = toio.scan(3);
  size_t n = toiocore_list.size();

  if (n == 0) {
    Serial.println("not found toio");
    return;
  }

  Serial.printf("found %d toio(s)\n", n);
  Serial.println("connect to toio with BLE");

  ToioCore* toiocore = toiocore_list.at(0);
  bool connected = toiocore->connect();

  if (!connected) {
    Serial.println("failed to connect toio(s)");
    return;
  }

  Serial.println("success to connect toio(s)");
  Serial.println("disconnect 3s later");

  delay(3000);

  toiocore->disconnect();
  Serial.println("-disconnected BLE");
}

void loop() {
}