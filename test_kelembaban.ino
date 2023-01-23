#include "deklarasi.h"

Servo myservo;
Servo myservo2;

#define FIREBASE_HOST "irigasi-sawah-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "jF9xuV9Dq4NdfBBdSz3ufjvF51trLI4KgRN8BrdU"
#define WIFI_SSID "Net"
#define WIFI_PASSWORD "07092013"

int pos = 0;
int sound = 250;

void setup() {
  Serial.begin(9600);
  //servo pembuangan
  myservo2.attach(5);
  pinMode (pinTrig, OUTPUT);
  pinMode (pinEcho, INPUT);
  
  Alarm.timerRepeat(30, terbuka); //waktu untuk putar servo
  myservo.attach(4); // servo pengisian air

  //test koneksi wifi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() !=WL_CONNECTED) {
    Serial.print(",");
    delay(500);
  }
  Serial.println();
  Serial.print("connecting: ");
  Serial.println(WiFi.localIP());
  Serial.print("Berhasil Terkoneksi...");
  
  //koenksi firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  baca_sensor ();
  Alarm.delay (1000);
  int kelembaban = analogRead(A0); 
  Serial.println(kelembaban);
  delay(1000);
  
  Firebase.setInt("Kelembaban Mencapai", kelembaban);
  //val = map(val, 0, 1023, 0, 180);
  
  if(kelembaban>700){
    Firebase.setString("Pesan", "Tanah Kering");
    Serial.print("Tanah Kering : ");
  }
  
  if(kelembaban<500){
    Firebase.setString("Pesan", "Tanah Lembab");
    Serial.print("Tanah Basah: ");
  }
  delay(20);

}

//pintu pengisian air 
void terbuka() {
  //Serial.print("pintu terbuka");
  myservo.write(90);
  Firebase.setString("Kondisi", "Pintu Air Terbuka");
  delay(5000);
  myservo.write(0);
  Firebase.setString("Kondisi", "Pintu Air Tertutup");
}
