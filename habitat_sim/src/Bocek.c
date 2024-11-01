/**
* @author Ayberk Karaköse
* @since 02.05.2024
*/
#include <stdbool.h>
#include <stdlib.h>
#include "Bocek.h"

void bocek_olustur(struct BOCEK* bocek, int deger, char tur) {
    canli_olustur(&(bocek->canli), deger, tur);
    bocek->canli.gorunum = (char* (*)())bocek_gorunum;  // Görünüm fonksiyonunu ata
}

bool bocek_yiyebilir(struct CANLI* canli) {
    return canli->tur == 'B' || canli->tur == 'P'; // Böcek bitkiyi ve pireyi yiyebilir
}

char* bocek_gorunum(struct BOCEK* bocek) {
    return "C"; // Böcek görünümü
}