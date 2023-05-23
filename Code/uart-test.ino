#include "Particle.h"

SYSTEM_THREAD(ENABLED);
String message = "";

const char *eventName = "pump_system";

void setup() {
    Serial1.begin(115200);
    //Serial.begin(115200);
   
    Time.zone(-6);
}
char a[150];
void loop() {
    if(Serial1.available()>0){
        message=Serial1.readStringUntil('\n');
        Particle.publish(eventName, message, PRIVATE);
    }
 }