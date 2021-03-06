#include "Eprom.h"

Eprom::Eprom(/* args */)
{
}

Eprom::~Eprom()
{
}

// ADDR = 0x50 (bit belakang rw tidak di pakai)
void Eprom::writeByte(int deviceaddress, unsigned int eeaddress, uint8_t data)
{
#if defined(rumus)

    EEPROM.write(eeaddress, data);

#endif // rumus
#if !defined(rumus)
#define rumus

    int rdata = data;
    Wire.beginTransmission(deviceaddress);
    Wire.write((int)(eeaddress >> 8));   // MSB
    Wire.write((int)(eeaddress & 0xFF)); // LSB
    Wire.write(rdata);
    Wire.endTransmission();
    delay(10);

#endif // rumus
}

// WARNING: address is a page address, 6-bit end will wrap around
// also, data can be maximum of about 30 bytes, because the Wire library has a buffer of 32 bytes
void Eprom::write_page(int deviceaddress, unsigned int eeaddresspage, uint8_t *data, uint8_t length)
{

#if defined(rumus)
    uint8_t c;
    for (c = 0; c < length; c++)
    {
        EEPROM.write(eeaddresspage + c, data[c]);
    }

#endif // rumus
#if !defined(rumus)
#define rumus

    Wire.beginTransmission(deviceaddress);
    Wire.write((int)(eeaddresspage >> 8));   // MSB
    Wire.write((int)(eeaddresspage & 0xFF)); // LSB
    uint8_t c;
    for (c = 0; c < length; c++)
        Wire.write(data[c]);
    Wire.endTransmission();

#endif // rumus
}

char Eprom::readByte(int deviceaddress, unsigned int eeaddress)
{
#if defined(rumus)

    return EEPROM.read(eeaddress);

#endif // rumus
#if !defined(rumus)
#define rumus

    char rdata = 0xFF;
    Wire.beginTransmission(deviceaddress);
    Wire.write((int)(eeaddress >> 8));   // MSB
    Wire.write((int)(eeaddress & 0xFF)); // LSB
    Wire.endTransmission();
    Wire.requestFrom(deviceaddress, 1);
    if (Wire.available())
        rdata = Wire.read();
    return rdata;

#endif // rumus
}

// maybe let's not read more than 30 or 32 bytes at a time!
void Eprom::readBuffer(int deviceaddress, unsigned int eeaddress, uint8_t *buffer, int length)
{
#if !defined(rumus)
#define rumus

    Wire.beginTransmission(deviceaddress);
    Wire.write((int)(eeaddress >> 8));   // MSB
    Wire.write((int)(eeaddress & 0xFF)); // LSB
    Wire.endTransmission();
    Wire.requestFrom(deviceaddress, length);
    int c = 0;
    for (c = 0; c < length; c++)
        if (Wire.available())
            buffer[c] = Wire.read();

#endif // rumus
#if defined(rumus)
    for (int c = 0; c < length; c++)
    {
        buffer[c] = EEPROM.read(eeaddress + c);
    }
#endif // rumus
}
