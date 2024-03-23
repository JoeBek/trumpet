#define ENA 15
#define IN1 2
#define IN2 4
// #define button 4



void setup() {
  // Initialize the motor control pins as outputs
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  // Setup PWM for ENA pin
  ledcSetup(0, 5000, 8); // channel 0, 5 kHz, 8-bit resolution
  ledcAttachPin(ENA, 0); // Attach ENA to channel 0

  // Start with motor stopped
  ledcWrite(0, 0); // 0% duty cycle, motor is off
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}

void loop() {
  // Turn the motor in one direction
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  ledcWrite(0, 255); // 100% duty cycle for full speed
  delay(1000); // Wait for 1 second
  
  // Stop the motor
  ledcWrite(0, 0); // 0% duty cycle, motor is off
  delay(1000); // Wait for 1 second to see the stop effect

  // Reverse the motor direction
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  ledcWrite(0, 255); // 100% duty cycle for full speed
  delay(1000); // Wait for 1 second
  
  // Stop the motor before the next loop iteration
  ledcWrite(0, 0); // Motor off
  delay(1000); // Wait for 1 second to see the stop effect
}


