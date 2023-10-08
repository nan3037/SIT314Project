#include <ArduinoJson.h>
#include <Wire.h>

const long interval = 5000;  // Interval for sending data to MongoDB
unsigned long previousMillis = 0;

void setup() {
  Serial.begin(9600);
  Oled.begin();
  Oled.setFlipMode(true);
}

void loop() {
  // Generate random motion detected values (either HIGH or LOW)
  bool motionDetected = random(0, 2);  // Randomly generates 0 or 1

  const room = "ROOM 1";
  const timestamp = millis();

  // Create JSON data
  DynamicJsonDocument jsonDoc(256);
  jsonDoc["area"] = "ROOM 1";
  jsonDoc["timestamp"] = millis();
  jsonDoc["motion_detected"] = motionDetected;

  // Send JSON data to the Serial port (USB)
  serializeJson(jsonDoc, Serial);
  Serial.println();

  // Delay before sending data again
  delay(interval);

  if (motionDetected == 1)
  {
    Oled.setFont(u8x8_font_chroma48medium8_r); 
    Oled.setCursor(0, 20);   
    Oled.print("area = ");
    Oled.print(room);
    
    Oled.setCursor(0, 42); 
    Oled.print("timestamp: "); 
    Oled.print(timestamp);
    
    Oled.setCursor(0, 54); 
    Oled.print("motion: yes");  
    
    Oled.refreshDisplay();   
    delay(3000);
  }
  else
  {
    Oled.setFont(u8x8_font_chroma48medium8_r); 
    Oled.setCursor(0, 20);  
    Oled.print("area = ");
    Oled.print(room);
    
    Oled.setCursor(0, 42); 
    Oled.print("timestamp: "); 
    Oled.print(timestamp);
    
    Oled.setCursor(0, 54); 
    Oled.print("motion: no ");  
    
    Oled.refreshDisplay();   
    delay(3000);
  }

}




