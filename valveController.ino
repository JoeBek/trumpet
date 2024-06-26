#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <unordered_map>
#include <ESP32Servo.h>


// parameters for different actuators 
#define KEY1 1
#define KEY2 2
#define KEY3 3
#define TURN_RADIUS 15
#define LOW 90
#define key1_offset 0
#define key2_offset 30
#define key3_offset 20




int key1pressed = 1;
int key2pressed = 1;
int key3pressed = 1;

// Define the GPIO pins for the servo signals
int servoPin1 = 19; // First servo
int servoPin2 = 18; // Second servo
int servoPin3 = 21; // Third servo

// Create servo objects
Servo servo1;
Servo servo2;
Servo servo3;



void setup() {

/*
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);

  // Attach the servos to the specified pins
  servo1.attach(servoPin1, 500, 2400); // Attaches the first servo on pin to the servo object
  servo2.attach(servoPin2, 500, 2400); // Attaches the second servo on pin to the servo object
  servo3.attach(servoPin3, 500, 2400); // Attaches the third servo on pin to the servo object
*/

  servo1.attach(servoPin1);
  servo2.attach(servoPin2);
  servo3.attach(servoPin3);
  servo1.write(LOW + key1_offset);
  servo2.write(LOW + key2_offset);
  servo3.write(LOW + key3_offset);

  Serial.begin(115200);

char* ssid = "Samuel iPhone";
char* password = "fortnite";

  // init wifi connection
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
}

void loop() {
  String payload;

  char* url = "https://trumpet-prosthetic-f47753833eed.herokuapp.com/music";
  if (getPayload(url, payload)) {
    DynamicJsonDocument doc(1024);
    if (parseJson(payload, doc)) {
      // The doc is now populated with the JSON payload
      //serializeJsonPretty(doc, Serial); // Print the JSON to the serial monitor

      // work with json payload now

      // Iterate over the JSON array
     
      for (JsonPair kv : doc.as<JsonObject>()) {

        const char* key = kv.key().c_str();

        JsonObject elem = kv.value().as<JsonObject>();

        int time = elem["time"]; // Assuming "time" is the key for the time entry
        int var1 = elem["val1"]; // Assuming "var1" is the key for the first flag
        int var2 = elem["val2"]; // Assuming "var2" is the key for the second flag
        int var3 = elem["val3"]; // Assuming "var3" is the key for the third flag

        // Now you can work with the variables 'time', 'var1', 'var2', and 'var3'
        // For example, print them to the serial monitor
        Serial.print("Time: ");
        Serial.println(time);
        Serial.print("Var1: ");
        Serial.println(var1);
        Serial.print("Var2: ");
        Serial.println(var2);
        Serial.print("Var3: ");
        Serial.println(var3);


      // set note with helper function. Uncomment when the wifi connection works

       
       //if (key1pressed != var1){
        change(1, var1);
         // key1pressed = !key1pressed;
       //}
       //if (key2pressed != var2){
        change(2, !var2);
         // key2pressed = !key2pressed;
       //}
      // if (key3pressed != var3){
        change(3, var3);
        //  key3pressed = !key3pressed;
       //}
       delay(time);
       delay(1500);
       



      
      }



    } else {
      Serial.println("Failed to parse JSON payload");
    }
  } else {
    Serial.println("Failed to get payload");
  }
  


  
  delay(10000); // Wait for 10 seconds before the next request
}


bool getPayload(const char* address, String & payload) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(address); // Specify the URL
    int httpCode = http.GET();

    if (httpCode == HTTP_CODE_OK) { // Check for the returning code
      payload = http.getString();
      http.end(); // Free the resources
      return true; // Indicate success
    } else {
      Serial.print("Error on HTTP request: ");
      Serial.println(httpCode);
      http.end(); // Free the resources
      return false; // Indicate failure
    }
  }
  return false; // Not connected to WiFi or other failure
}

bool parseJson(const String& payload, JsonDocument& doc) {
  DeserializationError error = deserializeJson(doc, payload);
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return false;
  }
  return true;
}

void change(int key, int pressed){

  //int angle = pressed * TURN_RADIUS;
  int angle = pressed ? TURN_RADIUS : LOW;
  switch(key){

    case KEY1:
        servo1.write(angle + key1_offset);
        break;
    case KEY2:
        servo2.write(angle + key2_offset);
        break;
    case KEY3:
        servo3.write(angle + key3_offset);
        break;

  }

}
