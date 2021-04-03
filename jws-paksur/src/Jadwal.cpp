#include "Jadwal.h"
Jadwal::Jadwal(/* args */)
{
    set_calc_method(ISNA);
    set_asr_method(Shafii);
    set_high_lats_adjust_method(AngleBased);
    set_fajr_angle(20);
    set_isha_angle(18);
}

Jadwal::~Jadwal()
{
}

void Jadwal::lookupJadwal(unsigned char tanggal, unsigned char bulan, int tahun)
{
    volatile uint8_t offsite;
    volatile uint16_t calc;

#if !defined(rumus)
#define rumus

    uint8_t data;
    uint16_t index = tanggal - 1;
    bulan--;
    for (uint8_t i = 0; i < 12; i++)
    {
        // const int Jan = 0 ;
        // const int Feb = 600 ;
        // const int Mar = 1200 ;
        // const int Apr = 1800 ;
        // const int Mei = 2400 ;
        // const int Jun = 3000 ;
        // const int Jul = 3600 ;
        // const int Agu = 4200 ;
        // const int Sep = 4800 ;
        // const int Okt = 5400 ;
        // const int Nov = 6000 ;
        // const int Des = 6600 ;

        // switch (bulan)    {
        //     case 0: alamat = Jan;
        //     break;
        //     case 1: alamat = Feb;
        //     break;
        //     case 2: alamat = Mar;
        //     break;
        //     case 3: alamat = Apr;
        //     break;
        //     case 4: alamat = Mei;
        //     break;
        //     case 5: alamat = Jun;
        //     break;
        //     case 6: alamat = Jul;
        //     break;
        //     case 7: alamat = Agu;
        //     break;
        //     case 8: alamat = Sep;
        //     break;
        //     case 9: alamat = Okt;
        //     break;
        //     case 10: alamat = Nov;
        //     break;
        //     case 11: alamat = Des;
        //     break;
        // }

        uint16_t alamat = bulan * 600;
        data = eprom.readByte(0x50, (alamat + index));
        this->jadwal[i] = (data / 16 * 10) + (data % 16); //ubah ke desimal
        index += 50;

        // Serial.print ("data ke ");
        // Serial.print(i);
        // Serial.print (" = ");
        // Serial.println(data);
        // jamImsya = data ;
        // menitImsya = data ;
        // jamSubuh = data ;
        // menitSubuh = data ;
        // jamDzuhur = data ;
        // menitDzuhur = data ;
        // jamAshar = data ;
        // menitAshar = data ;
        // jamMaghrib = data ;
        // menitMaghrib = data ;
        // jamIsya = data ;
        // menitIsya = data ;
    }

#endif // rumus
#if defined(rumus)

    float bj = 110.33;      //pgm_read_float(lintang + daerah);
    float lt = -7.80;       //pgm_read_float(bujur + daerah);
    unsigned char wkt = 7; // pgm_read_byte_near(gmt + daerah);
    int hours, minutes;
    //   if (daerah == 0)
    //   {
    //     wkt = parameter.set_kota_gmt;
    //     lt = parameter.set_kota_lnt;
    //     bj = parameter.set_kota_bjr;
    //   }
    get_prayer_times(tahun, bulan, tanggal, lt, bj, wkt, times);
    get_float_time_parts(times[0], hours, minutes);
    jadwal[2] = hours;
    jadwal[3] = minutes;
    // get_float_time_parts(times[1], hours, minutes);
    calc = (jadwal[2] * 60) + jadwal[3] - 8; //imsyak = subuh - 10 menit (+2 toleransi)
    jadwal[0] = calc / 60;
    jadwal[1] = calc % 60;

    get_float_time_parts(times[2], hours, minutes);
    jadwal[4] = hours;
    jadwal[5] = minutes;
    get_float_time_parts(times[3], hours, minutes);
    jadwal[6] = hours;
    jadwal[7] = minutes;
    get_float_time_parts(times[5], hours, minutes);
    jadwal[8] = hours;
    jadwal[9] = minutes;
    get_float_time_parts(times[6], hours, minutes);
    jadwal[10] = hours;
    jadwal[11] = minutes;
    // data[waktu_isya] = (hours * 60) + minutes;
    // data[waktu_subuh] = data[waktu_subuh] + 2;
    // data[waktu_duhur] = data[waktu_duhur] + 2;
    // data[waktu_ashar] = data[waktu_ashar] + 2;
    // data[waktu_magrib] = data[waktu_magrib] + 2;
    // data[waktu_isya] = data[waktu_isya] + 2;

#endif // rumus

    calc = (jadwal[2] * 60) + jadwal[3];
#if defined(rumus)
    calc += 2;
#endif // rumus

    offsite = eprom.readByte(0x50, alamat.OFFSITE_SUBUH);
    if (offsite >= 100)
    {
        offsite -= 100;
        calc -= offsite;
    }
    else
    {
        calc += offsite;
    }
    jadwal[2] = calc / 60;
    jadwal[3] = calc % 60;

    calc = (jadwal[4] * 60) + jadwal[5];
#if defined(rumus)
    calc += 2;
#endif // rumus
    offsite = eprom.readByte(0x50, alamat.OFFSITE_DZUHUR);
    if (offsite >= 100)
    {
        offsite -= 100;
        calc -= offsite;
    }
    else
    {
        calc += offsite;
    }
    jadwal[4] = calc / 60;
    jadwal[5] = calc % 60;

    calc = (jadwal[6] * 60) + jadwal[7];
#if defined(rumus)
    calc += 2;
#endif // rumus
    offsite = eprom.readByte(0x50, alamat.OFFSITE_ASHAR);
    if (offsite >= 100)
    {
        offsite -= 100;
        calc -= offsite;
    }
    else
    {
        calc += offsite;
    }
    jadwal[6] = calc / 60;
    jadwal[7] = calc % 60;

    calc = (jadwal[8] * 60) + jadwal[9];
#if defined(rumus)
    calc += 2;
#endif // rumus
    offsite = eprom.readByte(0x50, alamat.OFFSITE_MAGHRIB);
    if (offsite >= 100)
    {
        offsite -= 100;
        calc -= offsite;
    }
    else
    {
        calc += offsite;
    }
    jadwal[8] = calc / 60;
    jadwal[9] = calc % 60;

    calc = (jadwal[10] * 60) + jadwal[11];
#if defined(rumus)
    calc += 2;
#endif // rumus
    offsite = eprom.readByte(0x50, alamat.OFFSITE_ISYA);
    if (offsite >= 100)
    {
        offsite -= 100;
        calc -= offsite;
    }
    else
    {
        calc += offsite;
    }
    jadwal[10] = calc / 60;
    jadwal[11] = calc % 60;
}
uint8_t Jadwal::getAlarm()
{
    return alarm_status;
}
void Jadwal::setJam(unsigned char jam, unsigned char menit)
{
    alarm_status = alamat.ALARM_OFF;
    if (jam == jadwal[0] && menit == jadwal[1])
    {
        alarm_status = alamat.ALARM_IMSYA;
    }
    if (jam == jadwal[2] && menit == jadwal[3])
    {
        alarm_status = alamat.ALARM_SUBUH;
    }
    if (jam == jadwal[4] && menit == jadwal[5])
    {
        alarm_status = alamat.ALARM_DZUHUR;
    }
    if (jam == jadwal[6] && menit == jadwal[7])
    {
        alarm_status = alamat.ALARM_ASHAR;
    }
    if (jam == jadwal[8] && menit == jadwal[9])
    {
        alarm_status = alamat.ALARM_MAGHRIB;
    }
    if (jam == jadwal[10] && menit == jadwal[11])
    {
        alarm_status = alamat.ALARM_ISYA;
    }
}

void Jadwal::setTanggal(unsigned char tanggal, unsigned char bulan, int tahun)
{
    this->lookupJadwal(tanggal, bulan, tahun);
}

void Jadwal::getImsya(unsigned char &jam, unsigned char &menit)
{

    jam = jadwal[0];
    menit = jadwal[1];
}
void Jadwal::getSubuh(unsigned char &jam, unsigned char &menit)
{
    jam = jadwal[2];
    menit = jadwal[3];
}
void Jadwal::getSuruq(unsigned char &jam, unsigned char &menit)
{
    jam = jadwal[2];
    menit = jadwal[3];
}
void Jadwal::getDzuhur(unsigned char &jam, unsigned char &menit)
{
    jam = jadwal[4];
    menit = jadwal[5];
}
void Jadwal::getAshar(unsigned char &jam, unsigned char &menit)
{
    jam = jadwal[6];
    menit = jadwal[7];
}
void Jadwal::getMaghrib(unsigned char &jam, unsigned char &menit)
{
    jam = jadwal[8];
    menit = jadwal[9];
}
void Jadwal::getIsya(unsigned char &jam, unsigned char &menit)
{
    jam = jadwal[10];
    menit = jadwal[11];
}