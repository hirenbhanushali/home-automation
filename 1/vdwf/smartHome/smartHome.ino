
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define FIREBASE_HOST ""
#define FIREBASE_AUTH ""
#define WIFI_SSID ""
#define WIFI_PASSWORD ""


String fan, klight, rlight;
void setup() {

  pinMode(D1,OUTPUT);
  pinMode(D2,OUTPUT);
  pinMode(D3,OUTPUT);
  digitalWrite(D1,HIGH);
  digitalWrite(D2,HIGH);
  digitalWrite(D3,HIGH);
  
  Serial.begin(9600);

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  
  Firebase.setString("Fan", "0");
  
  Firebase.setString("Klight", "0");
  
  Firebase.setString("Rlight", "0");
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(1000);
}

void loop() {
  // get value 
  Serial.print("Fan: ");
  Serial.println(Firebase.getString("Fan"));
  fan=Firebase.getString("Fan");

  Serial.print("Rlight: ");
  Serial.println(Firebase.getString("Rlight"));
  rlight=Firebase.getString("Rlight");

  Serial.print("Klight: ");
  Serial.println(Firebase.getString("Klight"));
  klight=Firebase.getString("Klight");

  if (fan=="1") {
    digitalWrite(D1,LOW);
  }
  else if (fan=="0"){
    digitalWrite(D1,HIGH);
  }

  if (klight=="1") {
    digitalWrite(D2,LOW);
  }
  else if (klight=="0"){
    digitalWrite(D2,HIGH);
  }
  
  if (rlight=="1") {
    digitalWrite(D3,LOW);
  }
  else if (rlight=="0"){
    digitalWrite(D3,HIGH);
  }
  
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /message failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(500);
}
