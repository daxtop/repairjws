#include <Arduino.h>
// ATMEL ATMEGA8 & 168 / ARDUINO
//
//                  +-\/-+
//            PC6  1|    |28  PC5 (AI 5)
//      (D 0) PD0  2|    |27  PC4 (AI 4)
//      (D 1) PD1  3|    |26  PC3 (AI 3)
//      (D 2) PD2  4|    |25  PC2 (AI 2)
// PWM+ (D 3) PD3  5|    |24  PC1 (AI 1)
//      (D 4) PD4  6|    |23  PC0 (AI 0)
//            VCC  7|    |22  GND
//            GND  8|    |21  AREF
//            PB6  9|    |20  AVCC
//            PB7 10|    |19  PB5 (D 13)
// PWM+ (D 5) PD5 11|    |18  PB4 (D 12)
// PWM+ (D 6) PD6 12|    |17  PB3 (D 11) PWM
//      (D 7) PD7 13|    |16  PB2 (D 10) PWM
//      (D 8) PB0 14|    |15  PB1 (D 9) PWM
//                  +----+
//
#include "Rtc.h"
#include "Segmen.h"
#include "Jadwal.h"
#include "Bluetooth.h"
#include "Eprom.h"
#include "Event.h"

#define bluetooth 9600              //jika hc 06 atau hc05 ganti dengan 38400
#define namaBluetooth "Jws DacxtroniC"
#define jumat 5

#define led_iqomah  2 //iqomah
#define buzer  A3 //buzer
#define strobePin  A2 //Pin connected to Strobe (pin 1) of 4094
#define dataPin  A1 //Pin connected to Data (pin 2) of 4094
#define clockPin  A0  //Pin connected to Clock (pin 3) of 4094

Rtc waktu = Rtc();
Jadwal MyJadwal = Jadwal();
Bluetooth HC05 = Bluetooth();
Alamat alamat = Alamat();
Eprom eprom = Eprom();
Event second = Event(1000);
Segmen segmen = Segmen(dataPin,clockPin,strobePin );

void setup() {
  Serial.begin(bluetooth);
  Serial.setTimeout(200);
  // waktu.setTime(10,58,53);
  // waktu.setTanggal(31,6,2020);
  // segmen.setTime(17,39);
  pinMode(buzer,OUTPUT);
  pinMode(led_iqomah,OUTPUT);
  digitalWrite(buzer,HIGH);
  digitalWrite(led_iqomah,LOW);
  delay(100);
  digitalWrite(buzer,LOW);
}

void loop() {
  // ambil waktu dari rtc
  uint8_t dtk,jam,menit,tgl,bln,hri;
  uint8_t jadwaljam , jadwalmenit;
  int th;
  waktu.getTime(jam,menit,dtk);
  waktu.getTanggal(hri,tgl,bln,th);
  segmen.setTime(jam,menit);
  segmen.setTanggal(tgl,bln,2020);
  // ambil jadwal

  MyJadwal.setTanggal(tgl,bln,th);

  MyJadwal.getImsya(jadwaljam ,jadwalmenit);
  segmen.setImsya(jadwaljam ,jadwalmenit);

  MyJadwal.getSubuh(jadwaljam ,jadwalmenit);
  segmen.setSubuh(jadwaljam ,jadwalmenit);

  MyJadwal.getDzuhur(jadwaljam ,jadwalmenit);
  segmen.setDzuhur(jadwaljam ,jadwalmenit);

  MyJadwal.getAshar(jadwaljam ,jadwalmenit);
  segmen.setAshar(jadwaljam ,jadwalmenit);

  MyJadwal.getMaghrib(jadwaljam ,jadwalmenit);
  segmen.setMaghrib(jadwaljam ,jadwalmenit);

  MyJadwal.getIsya(jadwaljam ,jadwalmenit);
  segmen.setIsya(jadwaljam ,jadwalmenit);
  // cek alarm
  MyJadwal.setJam(jam,menit);

  if (MyJadwal.getAlarm() != alamat.ALARM_OFF){
    uint8_t count;//
    uint16_t adzan  ;
    uint16_t sholat  ;
    if (MyJadwal.getAlarm() == alamat.ALARM_SUBUH){
      segmen.displaySubuh();
      count = eprom.readByte(0x50,alamat.IQOMAH_SUBUH);
      adzan = 60 * eprom.readByte(0x50,alamat.ADZAN_SUBUH) ;
      sholat = 60 * eprom.readByte(0x50,alamat.SHOLAT_SUBUH) ;
    }    
    if (MyJadwal.getAlarm() == alamat.ALARM_DZUHUR){
      segmen.displayDzuhur();
      if (hri == jumat ){
        count = eprom.readByte(0x50,alamat.IQOMAH_JUMAT);
        adzan = 60 * eprom.readByte(0x50,alamat.ADZAN_JUMAT) ;
        sholat = 60 * eprom.readByte(0x50,alamat.SHOLAT_JUMAT) ;
      }
      else{
        count = eprom.readByte(0x50,alamat.IQOMAH_DZUHUR);
        adzan = 60 * eprom.readByte(0x50,alamat.ADZAN_DZUHUR) ;
        sholat = 60 * eprom.readByte(0x50,alamat.SHOLAT_DZUHUR) ;
      }
    }
    if (MyJadwal.getAlarm() == alamat.ALARM_ASHAR){
      segmen.displayAshar();
      count = eprom.readByte(0x50,alamat.IQOMAH_ASHAR);
      adzan = 60 * eprom.readByte(0x50,alamat.ADZAN_ASHAR) ;
      sholat = 60 * eprom.readByte(0x50,alamat.SHOLAT_ASHAR) ;
    }
    if (MyJadwal.getAlarm() == alamat.ALARM_MAGHRIB){
      segmen.displayMaghrib();
      count = eprom.readByte(0x50,alamat.IQOMAH_MAGHRIB);
      adzan = 60 * eprom.readByte(0x50,alamat.ADZAN_MAGHRIB) ;
      sholat = 60 * eprom.readByte(0x50,alamat.SHOLAT_MAGHRIB) ;
    }
    if (MyJadwal.getAlarm() == alamat.ALARM_ISYA){
      segmen.displayIsya();
      count = eprom.readByte(0x50,alamat.IQOMAH_ISYA);
      adzan = 60 * eprom.readByte(0x50,alamat.ADZAN_ISYA);
      sholat = 60 * eprom.readByte(0x50,alamat.SHOLAT_ISYA) ;
    }

    // beep alarm
    for (uint8_t i = 0; i < 5 ; i++){
      digitalWrite(buzer,HIGH);
      delay(500);
      digitalWrite(buzer,LOW);
      delay(500);
      HC05.loop();
    }    
    //waktu tunggu adzan
    while (adzan>0) {
      if (second.getEvent()){
        waktu.getTime(jam,menit,dtk);
        segmen.setTime(jam,menit);
        adzan--;
      }
      HC05.loop();
    }
    digitalWrite(buzer,HIGH);
    delay(500);
    digitalWrite(buzer,LOW);
    //counting down iqomah
    int countdown = count * 60;
    while (countdown >= 0){
      uint8_t i = countdown/60;
      uint8_t j = countdown%60;
      segmen.setTime(i,j);
      if (second.getEvent()){
        if ((countdown % 2) == 0){
          digitalWrite(led_iqomah,HIGH);
        }
        else{
          digitalWrite(led_iqomah,LOW);
        }
        countdown--;
      }
      HC05.loop();
    }
    // beep alarm
    for (uint8_t i = 0; i < 3 ; i++){
      digitalWrite(buzer,LOW);
      delay(500);
      digitalWrite(buzer,HIGH);
      delay(500);
    }
    digitalWrite(buzer,HIGH);
    delay(1000);
    digitalWrite(buzer,LOW);
    digitalWrite(led_iqomah,LOW);
    //waktu tunggu SHOLAT
    while (sholat>0){
      if (second.getEvent()){
        sholat--;
        waktu.getTime(jam,menit,dtk);
        segmen.setTime(jam,menit);
        segmen.displayOff();
      }
      HC05.loop();
    }
  }
  HC05.loop();
  segmen.loop();
  if (jam>=22 || jam <= 2)  {
    segmen.displayOff();
  }
  else  {
    segmen.displayNormal();
  }
}
