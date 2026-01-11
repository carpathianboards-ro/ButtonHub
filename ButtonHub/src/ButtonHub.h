#ifndef BUTTON_HUB_H
#define BUTTON_HUB_H

#include <Arduino.h>
#include <Wire.h>

#define BUTTON_HUB_DEFAULT_ADDR 0x10

class ButtonHub {
public:

    ButtonHub(uint8_t addr = BUTTON_HUB_DEFAULT_ADDR);

    bool begin(TwoWire *wirePort = &Wire);


    bool update();


    int16_t getEncoderValue();      
    uint8_t getButtonRegister(); 

    bool isEncoderPressed();    
    bool isButton1Pressed();    
    bool isButton2Pressed();    

    void setLimit(uint8_t newLimit);

    void setI2CAddress(uint8_t newAddress);

    bool isConnected();

private:
    uint8_t _addr;
    TwoWire *_wire;
    
    int16_t _encoderCount;
    uint8_t _buttonReg;

    void writeCommand(uint8_t command, uint8_t value);
};

#endif