/**
* @author Ayberk Karaköse
* @since 02.05.2024
*/
#include <stdbool.h>
#include "Pire.h"

void pire_olustur(struct PIRE* pire, int deger) {
    bocek_olustur(&(pire->bocek), deger, 'P');
    pire->bocek.gorunum = &pire_gorunum;
}

bool pire_yiyebilir(struct CANLI* canli) {
    return false; //pire hiçbir canlıyı yiyemez
}

char* pire_gorunum(struct PIRE* pire) {
    return "P";
}