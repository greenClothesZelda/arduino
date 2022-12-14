#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <iostream>
#include <algorithm>

#define FIREBASE_HOST "goodhouse-a0d2b-default-rtdb"
#define FIREBASE_NOISE "goodhouse-a0d2b-default-rtdb.firebaseio.com/12345/108/noise"
#define FIREBASE_week "goodhouse-a0d2b-default-rtdb.firebaseio.com/12345/108/week_noise"
#define FIREBASE_month "goodhouse-a0d2b-default-rtdb.firebaseio.com/12345/108/month_noise"
#define FIREBASE_AUTH "5y7d9hWtqHMGjHr2tiDIq2LkXKPU7MpdgPmFzfok"
#define WIFI_SSID "potatoIsDelicious_5G"
#define WIFI_PASSWORD "0172243445"


const int SOUND_SENSOR_PIN = A0;
int sensorValue;
int count = 0;
const int DELAY_TIME = 20;
int max_vol = 0;
const int HOUR = 3600000;
int day_noise[24] ={0};
int week_noise[7] = {0};
int month_noise[30] = {0};
int day_mark = 0;
int week_mark = 0;
int month_mark = 0; 


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_NOISE,FIREBASE_AUTH);
  Firebase.begin(FIREBASE_week,FIREBASE_AUTH);
  Firebase.begin(FIREBASE_month,FIREBASE_AUTH);
}

void loop() {
  // put your main code here, to run repeatedly:
  sensorValue = analogRead(SOUND_SENSOR_PIN);

  if(sensorValue >max_vol) max_vol = sensorValue;

  delay(DELAY_TIME);
  count+=DELAY_TIME;
  if(count>HOUR){
    day_noise[day_mark] = max_vol;
    day_mark++;
    if(day_mark >= 24){
      
      daymark = 0;
    }
    max_vol = 0;

    int size = sizeof(day_noise) / sizeof(*day_noise);

    if(day_mark == 0){
      week_noise[week_mark] = *std::max_element(day_noise, day_noise + size); 
      month_noise[month_mark] = week_noise[week_mark];
      week_mark++;
      if(week_mark >= 7){
        week_mark =0;
      }
      if(month_mark >= 30) {
        month_mark = 0
      }
    }
  }


}
