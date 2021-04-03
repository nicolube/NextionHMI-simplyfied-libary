#include <Arduino.h>
#include <NextionHMI.h>
#include <SoftwareSerial.h>


NextionObject text("page0", "tHallo");
NextionHMI hmi1(&Serial);

void setup() {
  hmi1.init();
}
int c = 0;
void loop() {
  hmi1.setText(&text, "Zaehler: "+String(c++));
  delay(100);
}