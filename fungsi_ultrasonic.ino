#include "deklarasi.h"


void baca_sensor() {
  long duration;
  int distance;
  digitalWrite(pinTrig, LOW);
  delayMicroseconds(2);
  digitalWrite(pinTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrig, LOW);
  duration = pulseIn(pinEcho, HIGH);
  distance = (duration/2) / 29.1;
  Firebase.setInt("Ketinggian", distance);
  
  if(distance <= 7) {
    //digitalWrite(buzz, HIGH); 
    myservo2.write(90);
    Firebase.setString("Status Air", "Air Sedang Di Buang");
  }
  
  if (distance >= 9 ){
    //digitalWrite(buzz, LOW);
      myservo2.write(0);
      Firebase.setString("Status Air", "Air Normal");
  }
   Serial.println("Ketinggian: ");
   Serial.print(distance);
   Serial.println("cm");
   delay (1000);
}
