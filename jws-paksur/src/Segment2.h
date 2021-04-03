#include <Arduino.h>
#include "Angka.h"
class Segment{
private:
    uint8_t registerBawah1;
    uint8_t registerBawah2;
    uint8_t registerAtas1;
    uint8_t registerAtas2;
    Angka *satuan;
    Angka *puluhan;
    Angka *ratusan;

    void convert();
public:
    Segment(/* args */);
    ~Segment();
    void setNumber(int angka);
    uint8_t getRegAtas(uint8_t reg);
    uint8_t getRegBawah(uint8_t reg);
};
