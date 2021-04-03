
#include "Angka.h"

bool Angka::getSegment( unsigned char bit){
    if (bit==0)return a;
    if (bit==1)return b;
    if (bit==2)return c;
    if (bit==3)return d;
    if (bit==4)return e;
    if (bit==5)return f;
    if (bit==6)return g;
    if (bit==7)return p;
}

void Angka::setNumber(unsigned char angka)
{
    a = false;
    b = false;
    c = false;
    d = false;
    e = false;
    f = false;
    g = false;
    p = false;
    if (angka == 0)
    {
       a = true;
       b = true;
       c = true;
       d = true;
       e = true;
       f = true;
       g = false;
    }
    if (angka == 1)
    {
        b = true;
        c = true;
    }
    
    if (angka == 2)
    {
        a = true;
        b = true;
        d = true;
        e = true;
        g = true;
    }
    
    if (angka == 3)
    {
        a = true;
        b = true;
        c = true;
        d = true;
        g = true;
    }
    
    if (angka == 4)
    {
        b = true;
        c = true;
        f = true;
        g = true;
    }
    
    if (angka == 5)
    {
        a = true;
        c = true;
        d = true;
        f = true;
        g = true;
    }
    
    if (angka == 6)
    {
        a = true;
        c = true;
        d = true;
        e = true;
        f = true;
        g = true;
    }
    
    if (angka == 7)
    {
        a = true;
        b = true;
        c = true;
    }
    
    if (angka == 8)
    {
        a = true;
        b = true;
        c = true;
        d = true;
        e = true;
        f = true;
        g = true;
    }
    
    if (angka == 9)
    {
        a = true;
        b = true;
        c = true;
        d = true;
        f = true;
        g = true;
    }
}
Angka::Angka(/* args */)
{
}

Angka::~Angka()
{
}
