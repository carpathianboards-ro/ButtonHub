/*
  ButtonHub Usage Example
  This code reads the encoder and buttons via I2C.
*/

#include <ButtonHub.h>

// Default address is 0x10. If you changed it, update it here.
ButtonHub hub(0x10);

void setup() {
  Serial.begin(115200);
  
  // Initialize communication
  if (!hub.begin()) {
    Serial.println("Error: ButtonHub not responding!");
    while(1); // Halt if not connected
  }
  
  Serial.println("ButtonHub Connected!");

  // OPTIONAL: Configure encoder limits
  // 100 = Volume control (0-100)
  // 255 = PWM duty cycle (0-255)
  hub.setLimit(100); 
}

void loop() {
  // 1. Update data (perform I2C read)
  hub.update();

  // 2. Display values
  Serial.print("Encoder: ");
  Serial.print(hub.getEncoderValue());

  if (hub.isEncoderPressed()) Serial.print(" [CLICK]");
  if (hub.isButton1Pressed()) Serial.print(" [BTN 1]");
  if (hub.isButton2Pressed()) Serial.print(" [BTN 2]");
  
  Serial.println();
  
  delay(50); // Small delay for readability
}