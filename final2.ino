const int sensor_pin = 12;
#include <Wire.h>
#include "SSD1306Wire.h"
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
SSD1306Wire  display(0x3c, 21, 22);

void setup() {
  Serial.begin(115200);
  pinMode(sensor_pin, INPUT);
    Serial.begin(115200);
    
    // Initialising the UI will init the display too.
    display.init();

    display.flipScreenVertically(); //畫面上下顛倒顯示
    pinMode(34,INPUT);
    display.clear();
   // display.setTextSize(3);
    
}

void loop() {
  Serial.println(analogRead(sensor_pin));
  delay(3000);
  int input = analogRead(sensor_pin);
    Serial.println(input);     
    display.clear(); //清空畫面
    display.setFont(ArialMT_Plain_16);   //設定字型與大小
    display.drawString(0, 0, String(input));  //(x座標,y座標,"字串")
    if(analogRead(sensor_pin)>=2000){
      Serial.print("too heavy");
      display.setFont(ArialMT_Plain_24);   //設定字型與大小
      display.drawString(40,20, String("too heavy"));  //(x座標,y座標,"字串")
    }  
    

    display.display(); //顯示畫面

}
