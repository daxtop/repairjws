#include "Segment2.h"

uint8_t Segment::getRegAtas(uint8_t reg){
    if (reg == 1) return registerAtas1;
    if (reg == 2) return registerAtas2;    
}
uint8_t Segment::getRegBawah(uint8_t reg){
    if (reg == 2) return registerBawah1;
    if (reg == 1) return registerBawah2;    
}

void Segment::convert(){

    //abcd efgp
    //0123 4567
    if (satuan->getSegment(0)==true) registerAtas2 |= 0x04;
    else registerAtas2 &= 0xfB;
    if (satuan->getSegment(1)==true) registerAtas2 |= 0x02;
    else registerAtas2 &= 0xfD;
    if (satuan->getSegment(2)==true) registerBawah2 |= 0x80;
    else registerBawah2 &= 0x7f;
    if (satuan->getSegment(3)==true) registerBawah2 |= 0x40;
    else registerBawah2 &= 0xbf;
    if (satuan->getSegment(4)==true) registerBawah2 |= 0x20;
    else registerBawah2 &= 0xdf;
    if (satuan->getSegment(5)==true) registerAtas2 |= 0x08;
    else registerAtas2 &= 0xf7;
    if (satuan->getSegment(6)==true) registerAtas2 |= 0x10;
    else registerAtas2 &= 0xef;


    //abcd efgp
    //0123 4567
    if (puluhan->getSegment(0)==true) registerAtas2 |= 0x40;//a
    else registerAtas2 &= 0xbf;
    if (puluhan->getSegment(1)==true) registerAtas2 |= 0x20;//b
    else registerAtas2 &= 0xdf;
    if (puluhan->getSegment(2)==true) registerBawah1 |= 0x40;//c
    else registerBawah1 &= 0xbf;
    if (puluhan->getSegment(3)==true) registerBawah1 |= 0x20;//d
    else registerBawah1 &= 0xdf;
    if (puluhan->getSegment(4)==true) registerBawah1 |= 0x10;//e
    else registerBawah1 &= 0xef;
    if (puluhan->getSegment(5)==true) registerAtas2 |= 0x80;//f
    else registerAtas2 &= 0x7f;
    if (puluhan->getSegment(6)==true) registerAtas1 |= 0x02;//g
    else registerAtas1 &= 0xfd;

    //abcd efgp
    //0123 4567
    if (ratusan->getSegment(0)==true) registerAtas1 |= 0x08;
    else registerAtas1 &= 0xf7;
    if (ratusan->getSegment(1)==true) registerAtas1 |= 0x04;
    else registerAtas1 &= 0xfb;
    if (ratusan->getSegment(2)==true) registerBawah1 |= 0x08;
    else registerBawah1 &= 0xf7;
    if (ratusan->getSegment(3)==true) registerBawah1 |= 0x04;
    else registerBawah1 &= 0xfb;
    if (ratusan->getSegment(4)==true) registerBawah1 |= 0x02;
    else registerBawah1 &= 0xfd;
    if (ratusan->getSegment(5)==true) registerAtas1 |= 0x10;
    else registerAtas1 &= 0xef;
    if (ratusan->getSegment(6)==true) registerAtas1 |= 0x20;
    else registerAtas1 &= 0xdf;
}

void Segment::setNumber(int angka){
    ratusan->setNumber( angka/100);
    puluhan->setNumber( (angka%100)/10);
    satuan->setNumber( (angka%100)%10);
    this->convert();   
}
Segment::Segment(){
    satuan = new Angka();
    puluhan = new Angka();
    ratusan = new Angka();
}

Segment::~Segment()
{
}
