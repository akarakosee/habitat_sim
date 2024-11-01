/**
* @author Ayberk Karaköse
* @since 02.05.2024
*/
#ifndef BOCEK_H
#define BOCEK_H

#include "Canli.h"

struct BOCEK {
    struct CANLI canli;
    char* (*gorunum)();  
};
char* bocek_gorunum(struct BOCEK* bocek);
void bocek_olustur(struct BOCEK* bocek, int deger, char tur);
bool bocek_yiyebilir(struct CANLI* canli); 

#endif