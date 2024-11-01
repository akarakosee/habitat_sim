/**
* @author Ayberk Karaköse
* @since 02.05.2024
*/
#include <stdbool.h>
#include "Bitki.h"

void bitki_olustur(struct BITKI* bitki, int deger) {
    canli_olustur(&bitki->canli, deger, 'B');
    bitki->canli.gorunum = (char* (*)())bitki_gorunum;
}

bool bitki_yiyebilir(struct CANLI* canli) {
    return canli->tur == 'P' || canli->tur == 'S';
}

char* bitki_gorunum(struct BITKI* bitki) {
		return "B";
}