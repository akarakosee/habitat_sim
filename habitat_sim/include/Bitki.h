/**
* @author Ayberk Karaköse
* @since 02.05.2024
*/

#ifndef BITKI_H
#define BITKI_H

#include "Canli.h"

struct BITKI {
    struct CANLI canli;
};

void bitki_olustur(struct BITKI* bitki, int deger); 
char* bitki_gorunum(struct BITKI* bitki);           
bool bitki_yiyebilir(struct CANLI* canli);           

#endif