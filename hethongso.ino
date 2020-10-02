#include <ESP8266WiFi.h>                                                // thư viện esp8266
#include <FirebaseArduino.h>                                             // thư viện firebase
#include "DHT.h"                                      // Gọi thư viện DHT11

#define FIREBASE_HOST "hethongso.firebaseio.com"                         // khai báo host và auth để kết nối với firebase
#define FIREBASE_AUTH "IWdHe4CMZuI8qqPwDxciXHw67R0Qz35VqJct6rGs"                   

#define WIFI_SSID "test"                                          // input your home or public wifi name 
#define WIFI_PASSWORD "12345678"                                    //password of wifi ssid                      
                                  
String Firedevice1 = "";                                                     // khai báo để nhận dữ liệu từ firebase ép kiểu dạng string
String Firedevice2 = "";


int led = D3;  
int led2 = D4; 
int led3 = D2;      
 
const int DHTPIN = D1;       //Đọc dữ liệu từ DHT11 ở chân D1 trên mạch Arduino
const int DHTTYPE = DHT11;  //Khai báo loại cảm biến, có 2 loại là DHT11 và DHT22
 
DHT dht(DHTPIN, DHTTYPE);
 
void setup() {
    Serial.begin(9600);
  dht.begin();         // Khởi động cảm biến
  pinMode(led, OUTPUT);   
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);                  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                      //try to connect with wifi
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
  delay(1000);
  }
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP Address is : ");
  Serial.println(WiFi.localIP());                                                      //print local IP address
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);                                       // connect to firebase

  Firebase.setInt("device_1", 0); 
                                         
  Firebase.setInt("device_2", 0);                                          //send initial string of led status
}
 
void loop() {
  int h = dht.readHumidity();    //Đọc độ ẩm
  int t = dht.readTemperature(); //Đọc nhiệt độ
  
  Serial.print("Humidity: ");  Serial.print(h);
  Serial.print("%  Temperature: ");  Serial.print(t); 
  delay(100);
  if(t>=30){
    Serial.print("    nhiet do cao !!!");
    digitalWrite(led3, 1);
    delay(500);
    digitalWrite(led3, 0);
    delay(100);
    }
  
  Firebase.setInt("humidity", h);
  Firebase.setInt("temperature", t); 
  Serial.println();

  Firedevice1 = Firebase.getInt("device_1");
  String z = String(Firedevice1);
  if (Firedevice1 == "1") {                                                          // compare the input of led status received from firebase
    Serial.println("Device 1: 1");                                                                      // make bultin led ON
    digitalWrite(led, 1);                                                         // make external led ON
//    delay(500);
  } 
  else if (Firedevice1  == "0") {                                                  // compare the input of led status received from firebase
    Serial.println("Device 1: 0");                                            // make bultin led OFF
    digitalWrite(led, 0);                                                         // make external led OFF
//    delay(500);
  }

  Firedevice2 = Firebase.getInt("device_2");
  String y = String(Firedevice2);
//  Serial.println(Firedevice2);
  if (Firedevice2 == "1") {                                                          // compare the input of led status received from firebase
    Serial.println("Device 2: 1");                                                                      // make bultin led ON
    digitalWrite(led2, 1);                                                         // make external led ON
//    delay(500);
  } 
  else if (Firedevice2  == "0") {                                                  // compare the input of led status received from firebase
    Serial.println("Device 2: 0");                                            // make bultin led OFF
    digitalWrite(led2, 0);                                                         // make external led OFF
//    delay(500);
  }

}
