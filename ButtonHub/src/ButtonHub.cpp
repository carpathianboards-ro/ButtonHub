#include "ButtonHub.h"

ButtonHub::ButtonHub(uint8_t addr) {
    _addr = addr;
    _encoderCount = 0;
    _buttonReg = 0;
}

bool ButtonHub::begin(TwoWire *wirePort) {
    _wire = wirePort;
    _wire->begin();
    return isConnected();
}

bool ButtonHub::isConnected() {
    _wire->beginTransmission(_addr);
    return (_wire->endTransmission() == 0);
}

bool ButtonHub::update() {

    uint8_t qty = _wire->requestFrom(_addr, (uint8_t)3);

    if (qty == 3) {
        _buttonReg = _wire->read();
        uint8_t lowByte = _wire->read();
        uint8_t highByte = _wire->read();

        _encoderCount = (int16_t)(highByte << 8 | lowByte);
        return true;
    }
    return false;
}

int16_t ButtonHub::getEncoderValue() {
    return _encoderCount;
}

uint8_t ButtonHub::getButtonRegister() {
    return _buttonReg;
}

bool ButtonHub::isEncoderPressed() {
    return (_buttonReg & 0x01);
}

bool ButtonHub::isButton1Pressed() {
    return (_buttonReg & 0x02);
}

bool ButtonHub::isButton2Pressed() {
    return (_buttonReg & 0x04);
}

void ButtonHub::setLimit(uint8_t newLimit) {

    writeCommand(0xFB, newLimit);
}

void ButtonHub::setI2CAddress(uint8_t newAddress) {

    writeCommand(0xFA, newAddress);
    _addr = newAddress; 
}

void ButtonHub::writeCommand(uint8_t command, uint8_t value) {
    _wire->beginTransmission(_addr);
    _wire->write(command);
    _wire->write(value);
    _wire->endTransmission();
}