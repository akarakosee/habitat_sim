/**
* @author Ayberk Karaköse
* @since 02.05.2024
*/
#ifndef PIRE_H
#define PIRE_H

#include "Bocek.h"

struct PIRE {
    struct BOCEK bocek;
};

void pire_olustur(struct PIRE* pire, int deger);
char* pire_gorunum(struct PIRE* pire);
bool pire_yiyebilir(struct CANLI* canli);

#endif