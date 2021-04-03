#ifndef Bluetooth_H_
#define Bluetooth_H_

#include <Arduino.h>
#include "Rtc.h"
#include "Eprom.h"
#include "Alamat.h"

#include <EEPROM.h>
const PROGMEM  char bloothtCommand []={
'J','S','I','T','B','F','X','K','A','W',
};

class Bluetooth
{
private:
    /* data */
    Rtc waktu = Rtc();
    Eprom eprom = Eprom();
    Alamat addr = Alamat();
    volatile  uint8_t command;
    // const uint8_t command_start = 1;
    // const uint8_t play_mp3 = 2;  
    // const uint8_t set_jam = 3;  
    // const uint8_t set_text = 4;  
    // const uint8_t set_iqomah = 5;  
    // const uint8_t set_tarhim = 6;  
    // const uint8_t set_brightnes = 7;  
    // const uint8_t set_offsite = 8;  
    // const uint8_t set_fix = 9;  
    // const uint8_t set_bt_kota = 10;
    // const uint8_t set_adzan = 11;
    // const uint8_t command_end = 12;

    #define command_start 1
    #define set_jam 2
    #define set_text 3
    #define set_iqomah 4
    #define set_tarhim 5
    #define set_brightnes 6
    #define set_offsite 7
    #define set_fix 8
    #define set_bt_kota 9
    #define set_adzan 10
    #define play_mp3 11
    #define command_end 12
    // volatile static uint8_t command;
    

public:
    Bluetooth(/* args */);
    ~Bluetooth();
    void loop();
};

#endif