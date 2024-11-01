/**
* @author Ayberk Karaköse
* @since 02.05.2024
*/
#include <stdbool.h>
#include "Sinek.h"

void sinek_olustur(struct SINEK* sinek, int deger) {
    bocek_olustur(&(sinek->bocek), deger, 'S');
    sinek->bocek.canli.gorunum = &sinek_gorunum; // canli üyesine erişim
}

char* sinek_gorunum(struct SINEK* sinek) {
    return sinek->bocek.canli.gorunum(&(sinek->bocek.canli)); // BOCEK yapısındaki görünüm fonksiyonunu kullan
}

bool sinek_yiyebilir(struct CANLI* canli) {
    return canli->tur == 'P' || canli->tur == 'C'; // Sinek pireyi ve böceği yiyebilir
}