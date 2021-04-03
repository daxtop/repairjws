#ifndef Eprom_H_
#define Eprom_H_
#include <Wire.h>
#include <Arduino.h>
#define rumus
#if defined(rumus)
#include <EEPROM.h>

#endif // rumus

class Eprom
{
private:
    /* data */
public:
    Eprom(/* args */);
    ~Eprom();
    void writeByte(int deviceaddress, unsigned int eeaddress, uint8_t data);
    void write_page(int deviceaddress, unsigned int eeaddresspage, uint8_t *data, uint8_t length);
    char readByte(int deviceaddress, unsigned int eeaddress);
    void readBuffer(int deviceaddress, unsigned int eeaddress, uint8_t *buffer, int length);
};
#endif