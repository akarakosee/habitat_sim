/**
* @author Ayberk Karaköse
* @since 02.05.2024
*/
#ifndef SINEK_H
#define SINEK_H

#include "Bocek.h"

struct SINEK {
    struct BOCEK bocek;
};

void sinek_olustur(struct SINEK* sinek, int deger);
char* sinek_gorunum(struct SINEK* sinek);
bool sinek_yiyebilir(struct CANLI* canli);

#endif