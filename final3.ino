const int sensor_pin = 12;
#include <Wire.h>
#include <WiFi.h>
#include "SSD1306Wire.h"
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
SSD1306Wire  display(0x3c, 21, 22);

const char* ssid = "Amane";
const char* password = "sophia030";
const char* host = "maker.ifttt.com"; //IFTTT server網址
const char* event = "line_notify";  //IFTTT事件名稱
const char* apiKey = "dPyYp3N4BelhDWI-qwBE-q";  //IFTTT Applet key

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
   
  
   if(analogRead(sensor_pin)>=100){
    // Connect to Wi-Fi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
     Serial.print(".");
   }
     Serial.println("");
     Serial.println("WiFi connected");  
 }
 
}

void loop() {
  Serial.println(analogRead(sensor_pin));
  delay(3000);
  int input = analogRead(sensor_pin);
    Serial.println(input);     
    display.clear(); //清空畫面
    display.setFont(ArialMT_Plain_10);   //設定字型與大小
    display.drawString(0, 0, String("Current pressure:"));  //(x座標,y座標,"字串")
    display.drawString(80, 0, String(input));  //(x座標,y座標,"字串")
    if(analogRead(sensor_pin)>=100){
      Serial.println("too heavy!");
      display.setFont(ArialMT_Plain_24);   //設定字型與大小
      display.drawString(15,20, String("too heavy!"));  //(x座標,y座標,"字串")
     //cilent資料傳送
      int value2 = analogRead(sensor_pin) ;
      ClientRequest(String(value2));  //Client傳送資料
      delay(3000);
    }  
    display.display(); //顯示畫面
    
    
}
void ClientRequest(String value2){
  
  WiFiClient client;  //建立Client物件
  const int httpPort = 80;  //預設通訊阜80
  String JsonString = "";  //此範例不會用到

  //Client連結Server
  if (client.connect(host, httpPort)) {
    
    //Webhook API
    String url = "/trigger/" + String(event) + "/with/key/" + String(apiKey);
    //Query String
    url += "?value2=" + value2 ;

    //Client傳送
    client.println(String("POST ") + url + " HTTP/1.1");
    client.println(String("Host: ") + host); 
    client.println("Content-Type: application/json");
    client.print("Content-Length: ");
    client.println(JsonString.length());
    client.println();
    client.println(JsonString);

    //等待5秒，每0.1秒偵測一次是否有接收到response資料  
    int timeout = 0;
    while(!client.available() && (timeout++ <= 50)){
      delay(100);
    }
  
    //如果無回應
    if(!client.available()) {
      Serial.println("No response...");
    }
    //用while迴圈一字一字讀取Response
    while(client.available()){
      Serial.write(client.read());
    }

    //停止Client
    client.stop(); 
  } 
}
