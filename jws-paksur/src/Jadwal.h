#ifndef Jadwal_H_
#define Jadwal_H_

#define rumus

#include <Arduino.h>
#include "Alamat.h"
#include "Eprom.h"

#if defined(rumus)
#include "PrayerTimes.h"
#endif // rumus

class Jadwal
{
private:
#if defined(rumus)
    double times[sizeof(TimeName) / sizeof(char *)];
#endif // rumus

    Eprom eprom = Eprom();
    uint8_t alarm_status;
    Alamat alamat = Alamat();
    unsigned char jadwal[12];
    void lookupJadwal(unsigned char tanggal, unsigned char bulan, int tahun);

public:
    Jadwal(/* args */);
    ~Jadwal();
    uint8_t getAlarm();
    void setTanggal(unsigned char tanggal, unsigned char bulan, int tahun);
    void setJam(unsigned char jam, unsigned char menit);
    void getImsya(unsigned char &jam, unsigned char &menit);
    void getSubuh(unsigned char &jam, unsigned char &menit);
    void getSuruq(unsigned char &jam, unsigned char &menit);
    void getDzuhur(unsigned char &jam, unsigned char &menit);
    void getAshar(unsigned char &jam, unsigned char &menit);
    void getMaghrib(unsigned char &jam, unsigned char &menit);
    void getIsya(unsigned char &jam, unsigned char &menit);
};

#endif
