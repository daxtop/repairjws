#include "Bluetooth.h"

Bluetooth::Bluetooth(/* args */)
{
}

Bluetooth::~Bluetooth()
{
}

void Bluetooth::loop()
{
  String input_serial;
  if (Serial.available())
  {
    input_serial = Serial.readString();
    // Serial.println(input_serial);

    if (input_serial == "1234")
    {
      Serial.print("OK\n");
      command = command_start;
    }
    else
    {
      if (command == command_start)
      {
        if (input_serial[0] == '%')
        {
          for (uint8_t cmd = 0; cmd < 10; cmd++)
          {
            char lookupCmd = pgm_read_byte_near(bloothtCommand + cmd);
            if (lookupCmd == input_serial[1])
            {
              Serial.print("OK");
              Serial.print(lookupCmd);
              Serial.print("\n");
              command = cmd + 2;
              break;
            }
          }
        }
      }
      //===========================================================
      else if (command == play_mp3)
      {
        command = command_end;
        //   int _track =((input_serial[1]-'0')*100)+((input_serial[2]-'0')*10)+(input_serial[3]-'0');
        // 1234 %W Q001
        // 1234 %W Q001
        // 1234 %W Q001
        // 1234 %W Q004
        // sholawat
        // 1234 %W W003
        // 1234 %W W010
        // stop
        // 1234 %W STOP
        // myDFPlayer.play(1);  //Play the first mp3
        // myDFPlayer.stop();

        if (input_serial[0] == 'Q')
        {
          // myDFPlayer.play(_track);        //play alquran
        }
        if (input_serial[0] == 'W')
        { //play sholawat
          // myDFPlayer.play(_track+114);
        }
        if (input_serial[0] == 'S')
        {
          // myDFPlayer.stop(); //STOP
        }
        Serial.print("SetPlay\n");
      }
      else if (command == set_jam)
      {
        command = command_end;
        //290417040319 // DTK_MNT_JAM_TGL_BLN_TH
        //502009170920
        uint8_t jam = ((input_serial[4] - '0') * 10) + (input_serial[5] - '0');
        uint8_t menit = ((input_serial[2] - '0') * 10) + (input_serial[3] - '0');
        uint8_t detik = ((input_serial[0] - '0') * 10) + (input_serial[1] - '0');
        uint8_t tanggal = ((input_serial[6] - '0') * 10) + (input_serial[7] - '0');
        uint8_t bulan = ((input_serial[8] - '0') * 10) + (input_serial[9] - '0');
        uint16_t tahun = 2000 + ((input_serial[10] - '0') * 10) + (input_serial[11] - '0');
        // tulis_rtc();

        // Serial.print("jam = ");
        // Serial.print(jam);
        // Serial.print("-");
        // Serial.print(menit);
        // Serial.print("-");
        // Serial.print(detik);
        // Serial.print("-");
        // Serial.print(tanggal);
        // Serial.print("-");
        // Serial.print(bulan);
        // Serial.print("-");
        // Serial.println(tahun);

        waktu.setTime(jam, menit, detik);
        waktu.setTanggal(tanggal, bulan, tahun);
        Serial.print("SetTime\n");
      }
      else if (command == set_text)
      { //ok
        command = command_end;
        //1234 %S tes karakter
        //writeString(text_run,input_serial);

        // int _size = input_serial.length();
        // int i;
        // for(i=0;i<_size;i++)EEPROM.write(text_run+i,input_serial[i]);
        // EEPROM.write(text_run+_size,'\0');   //Add termination null character for String Data
        // Serial.print("SetText\n");
        // alamat_eprom=0;
        // display_eprom(text_run);
      }
      else if (command == set_iqomah)
      {
        // 1234 %I N 0 1010 Iqomah Subuh // n DAN y ADALAH ENABLE IQOMAH
        // 1234 %I N 1 1010 Iqomah Dzuhur... //IQOMAH_SHOLAT
        // 1234 %I N 2 1010 Iqomah Ashar...
        // 1234 %I N 3 1010 Iqomah Maghrib...
        // 1234 %I N 4 1010 Iqomah Isya...
        // 1234 %I N 5 0510 Iqomah jumat
        // 1234 %I Y 0 1010 Iqomah Subuh
        command = command_end;
        //   int _text_iqomah;
        if (input_serial[1] == '0')
        {
          uint8_t value = ((input_serial[2] - '0') * 10) + (input_serial[3] - '0');
          eprom.writeByte(0x50, addr.IQOMAH_SUBUH, value);
          value = ((input_serial[4] - '0') * 10) + (input_serial[5] - '0');
          eprom.writeByte(0x50, addr.SHOLAT_SUBUH, value);
          //writeString(text_iq_subuh,input_serial.substring(6));
          // _text_iqomah=text_iq_subuh;
        }
        if (input_serial[1] == '1')
        {
          uint8_t value = ((input_serial[2] - '0') * 10) + (input_serial[3] - '0');
          eprom.writeByte(0x50, addr.IQOMAH_DZUHUR, value);
          value = ((input_serial[4] - '0') * 10) + (input_serial[5] - '0');
          eprom.writeByte(0x50, addr.SHOLAT_DZUHUR, value);
          //writeString(text_iq_duhur,input_serial.substring(6));
          // _text_iqomah=text_iq_duhur;
        }
        if (input_serial[1] == '2')
        {
          uint8_t value = ((input_serial[2] - '0') * 10) + (input_serial[3] - '0');
          eprom.writeByte(0x50, addr.IQOMAH_ASHAR, value);
          value = ((input_serial[4] - '0') * 10) + (input_serial[5] - '0');
          eprom.writeByte(0x50, addr.SHOLAT_ASHAR, value);
          //writeString(text_iq_ashar,input_serial.substring(6));
          // _text_iqomah=text_iq_ashar;
        }
        if (input_serial[1] == '3')
        {
          uint8_t value = ((input_serial[2] - '0') * 10) + (input_serial[3] - '0');
          eprom.writeByte(0x50, addr.IQOMAH_MAGHRIB, value);
          value = ((input_serial[4] - '0') * 10) + (input_serial[5] - '0');
          eprom.writeByte(0x50, addr.SHOLAT_MAGHRIB, value);
          //writeString(text_iq_maghrib,input_serial.substring(6));
          // _text_iqomah=text_iq_maghrib;
        }
        if (input_serial[1] == '4')
        {
          uint8_t value = ((input_serial[2] - '0') * 10) + (input_serial[3] - '0');
          eprom.writeByte(0x50, addr.IQOMAH_ISYA, value);
          value = ((input_serial[4] - '0') * 10) + (input_serial[5] - '0');
          eprom.writeByte(0x50, addr.SHOLAT_ISYA, value);
          //writeString(text_iq_isya,input_serial.substring(6));
          // _text_iqomah=text_iq_isya;
        }
        if (input_serial[1] == '5')
        {
          uint8_t value = ((input_serial[2] - '0') * 10) + (input_serial[3] - '0');
          eprom.writeByte(0x50, addr.IQOMAH_JUMAT, value);
          value = ((input_serial[4] - '0') * 10) + (input_serial[5] - '0');
          eprom.writeByte(0x50, addr.SHOLAT_JUMAT, value);
          //writeString(text_iq_jumat,input_serial.substring(6));
          // _text_iqomah=text_iq_jumat;
        }
        //   int _size = input_serial.length();
        //   int i,u=0;
        //   for(i=6;i<_size;i++){
        //     EEPROM.write(_text_iqomah+u,input_serial[i]);
        //     u++;
        //   }
        //   EEPROM.write(_text_iqomah+u,'\0');
        //   EEPROM.put( 0, parameter );
        Serial.print("SetIqom\n");
      }
      else if (command == set_tarhim)
      { //OK
        command = command_end;
        //15 15 15 15 15 15 YNNNYY  //Subuh Dzuhur...  jumat YES/NO
        //   parameter.tartil_subuh = ((input_serial[0]-'0')*10)+(input_serial[1]-'0') ;
        //   parameter.tartil_duhur = ((input_serial[2]-'0')*10)+(input_serial[3]-'0');
        //   parameter.tartil_ashar = ((input_serial[4]-'0')*10)+(input_serial[5]-'0') ;
        //   parameter.tartil_maghrib = ((input_serial[6]-'0')*10)+(input_serial[7]-'0');
        //   parameter.tartil_isya = ((input_serial[8]-'0')*10)+(input_serial[9]-'0');
        //   parameter.tartil_jumat = ((input_serial[10]-'0')*10)+(input_serial[11]-'0');
        //   if(input_serial[12]=='N') parameter.tartil_subuh =0;
        //   if(input_serial[13]=='N') parameter.tartil_duhur =0;// ((_trtl[2]-'0')*10)+(_trtl[3]-'0');
        //   if(input_serial[14]=='N') parameter.tartil_ashar = 0;// ((_trtl[4]-'0')*10)+(_trtl[5]-'0') ;
        //   if(input_serial[15]=='N') parameter.tartil_maghrib = 0;//((_trtl[6]-'0')*10)+(_trtl[7]-'0');
        //   if(input_serial[16]=='N') parameter.tartil_isya = 0;//((_trtl[8]-'0')*10)+(_trtl[9]-'0');
        //   if(input_serial[17]=='N') parameter.tartil_jumat = 0;//((_trtl[10]-'0')*10)+(_trtl[11]-'0');
        //   EEPROM.put( 0, parameter );
        Serial.print("SetTrkm\n");
      }
      else if (command == set_brightnes)
      { //ok
        command = command_end;
        // 1234 %B 0300 01 0600 03 1730 01 2100 00
        // 1234 %B 0300 07 0600 03 1730 01 2100 00
        //    parameter.kecerahan_1 =input_serial[5]-'0';
        //    parameter.kecerahan_2 =input_serial[11]-'0';
        //    parameter.kecerahan_3 =input_serial[17]-'0';
        //    parameter.kecerahan_4 =input_serial[23]-'0';
        //    parameter.jam_kecerahan_1 = ((((input_serial[0]-'0')*10)+(input_serial[1]-'0'))*60)+(((input_serial[2]-'0')*10)+(input_serial[3]-'0'));
        //    parameter.jam_kecerahan_2 = ((((input_serial[6]-'0')*10)+(input_serial[7]-'0'))*60)+(((input_serial[8]-'0')*10)+(input_serial[9]-'0'));
        //    parameter.jam_kecerahan_3 = ((((input_serial[12]-'0')*10)+(input_serial[13]-'0'))*60)+(((input_serial[14]-'0')*10)+(input_serial[15]-'0'));
        //    parameter.jam_kecerahan_4 = ((((input_serial[18]-'0')*10)+(input_serial[19]-'0'))*60)+(((input_serial[20]-'0')*10)+(input_serial[21]-'0'));
        //    EEPROM.put( 0, parameter );
        Serial.print("SetBrns\n");
      }
      else if (command == set_offsite)
      { //OK
        command = command_end;
        //1234 %F 19 02 01 03 05 //1= TAMBAH & 0=KURANG
        // if(input_serial[0]=='0') parameter.tambah_kurang_subuh =0-(input_serial[1]-'0');
        // else  parameter.tambah_kurang_subuh =input_serial[1]-'0';
        // if(input_serial[2]=='0')parameter.tambah_kurang_duhur =0-(input_serial[3]-'0');
        // else parameter.tambah_kurang_duhur =input_serial[3] -'0';
        // if(input_serial[4]=='0')parameter.tambah_kurang_ashar =0-(input_serial[5]-'0');
        // else parameter.tambah_kurang_ashar =input_serial[5] -'0';
        // if(input_serial[6]=='0')parameter.tambah_kurang_maghrib =0-(input_serial[7]-'0');
        // else parameter.tambah_kurang_maghrib =input_serial[7] -'0';
        // if(input_serial[8]=='0')parameter.tambah_kurang_isya =0-(input_serial[9]-'0');
        // else parameter.tambah_kurang_isya =input_serial[9] -'0';
        // EEPROM.put( 0, parameter );

        if (input_serial[0] == '0')
          eprom.writeByte(0x50, addr.OFFSITE_SUBUH, (100 + (input_serial[1] - '0')));
        else
          eprom.writeByte(0x50, addr.OFFSITE_SUBUH, (input_serial[1] - '0'));

        if (input_serial[2] == '0')
          eprom.writeByte(0x50, addr.OFFSITE_DZUHUR, (100 + (input_serial[3] - '0')));
        else
          eprom.writeByte(0x50, addr.OFFSITE_DZUHUR, (input_serial[3] - '0'));

        if (input_serial[4] == '0')
          eprom.writeByte(0x50, addr.OFFSITE_ASHAR, (100 + (input_serial[5] - '0')));
        else
          eprom.writeByte(0x50, addr.OFFSITE_ASHAR, (input_serial[5] - '0'));

        if (input_serial[6] == '0')
          eprom.writeByte(0x50, addr.OFFSITE_MAGHRIB, (100 + (input_serial[7] - '0')));
        else
          eprom.writeByte(0x50, addr.OFFSITE_MAGHRIB, (input_serial[7] - '0'));

        if (input_serial[8] == '0')
          eprom.writeByte(0x50, addr.OFFSITE_ISYA, (100 + (input_serial[9] - '0')));
        else
          eprom.writeByte(0x50, addr.OFFSITE_ISYA, (input_serial[9] - '0'));

        Serial.print("SetOffs\n");
      }
      else if (command == set_fix)
      { //OK
        command = command_end;
        //YYNYN 2200 0000 0000 0000 0000
        //5 9 13 17 21
        // parameter.jadwal_fix_subuh = 0 ;
        // parameter.jadwal_fix_duhur =0;
        // parameter.jadwal_fix_ashar =0;
        // parameter.jadwal_fix_maghrib =0;
        // parameter.jadwal_fix_isya =0;
        // if(input_serial[0]=='Y')parameter.jadwal_fix_subuh = ((((input_serial[5]-'0')*10)+(input_serial[6]-'0'))*60)+(((input_serial[7]-'0')*10)+(input_serial[8]-'0'));
        // if(input_serial[1]=='Y')parameter.jadwal_fix_duhur = ((((input_serial[9]-'0')*10)+(input_serial[10]-'0'))*60)+(((input_serial[11]-'0')*10)+(input_serial[12]-'0'));
        // if(input_serial[2]=='Y')parameter.jadwal_fix_ashar = ((((input_serial[13]-'0')*10)+(input_serial[14]-'0'))*60)+(((input_serial[15]-'0')*10)+(input_serial[16]-'0'));
        // if(input_serial[3]=='Y')parameter.jadwal_fix_maghrib = ((((input_serial[17]-'0')*10)+(input_serial[18]-'0'))*60)+(((input_serial[19]-'0')*10)+(input_serial[20]-'0'));
        // if(input_serial[4]=='Y')parameter.jadwal_fix_isya = ((((input_serial[21]-'0')*10)+(input_serial[22]-'0'))*60)+(((input_serial[23]-'0')*10)+(input_serial[24]-'0'));
        // EEPROM.put( 0, parameter );
        Serial.print("SetFixx\n");
      }
      else if (command == set_bt_kota)
      { //ok
        // EN 110 39 007 82 01187+00 //LU
        // ES 110 39 007 82 01187+00 //ls
        // parameter.set_kota_bjr=((input_serial[2]-'0')*100)+((input_serial[3]-'0')*10)+(input_serial[4]-'0')+((input_serial[5]-'0')*0.1)+((input_serial[6]-'0')*0.01)  ;
        // if(input_serial[1] == 'N') parameter.set_kota_lnt =((input_serial[7]-'0')*100)+((input_serial[8]-'0')*10)+(input_serial[9]-'0')+((input_serial[10]-'0')*0.1)+((input_serial[11]-'0')*0.01)  ;
        // if(input_serial[1] == 'S')parameter.set_kota_lnt =0-(((input_serial[7]-'0')*100)+((input_serial[8]-'0')*10)+(input_serial[9]-'0')+((input_serial[10]-'0')*0.1)+((input_serial[11]-'0')*0.01))  ;
        // parameter.set_kota_gmt=input_serial[16]-'0' ;
        // parameter.kota = 0;
        // EEPROM.put( 0, parameter );
        for (unsigned char i = 0; i < 10; i++)
        {
          EEPROM.write((2 + i), (input_serial[2 + i] - '0'));
        }

        EEPROM.write(1, input_serial[16] - '0');

        Serial.print("SetKoor\n");
        command = command_end;
      }
      else if (command == set_adzan)
      { //OK
        command = command_end;
        uint8_t value;
        value = ((input_serial[0] - '0') * 10) + (input_serial[1] - '0');
        eprom.writeByte(0x50, addr.ADZAN_SUBUH, value);
        value = ((input_serial[2] - '0') * 10) + (input_serial[3] - '0');
        eprom.writeByte(0x50, addr.ADZAN_DZUHUR, value);
        value = ((input_serial[4] - '0') * 10) + (input_serial[5] - '0');
        eprom.writeByte(0x50, addr.ADZAN_ASHAR, value);
        value = ((input_serial[6] - '0') * 10) + (input_serial[7] - '0');
        eprom.writeByte(0x50, addr.ADZAN_MAGHRIB, value);
        value = ((input_serial[8] - '0') * 10) + (input_serial[9] - '0');
        eprom.writeByte(0x50, addr.ADZAN_ISYA, value);
        value = ((input_serial[10] - '0') * 10) + (input_serial[11] - '0');
        eprom.writeByte(0x50, addr.ADZAN_JUMAT, value);
        //   EEPROM.put( 0, parameter );
        Serial.print("SetAlrm\n");
      }
      if (command == command_end)
      {
        digitalWrite(A3, HIGH);
        delay(300);
        digitalWrite(A3, LOW);
        /* code */
      }
    }
  } // if serial availebel
}