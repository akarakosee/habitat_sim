/**
* @author Ayberk Karaköse
* @since 02.05.2024
*/
#include <stdbool.h>
#include "Canli.h"
#include <stdlib.h>

void canli_olustur(struct CANLI* canli, int deger, char tur) {
    canli->deger = deger;
    canli->tur = tur;
    canli->gorunum = NULL; // Türetilmiş sınıflarda tanımlanacak
}

void canli_yoket(struct CANLI* canli) {
    if (canli) {  // canli işaretçisinin NULL olmadığından emin olun
        if (canli->tur == 'B') {
            // Bitki için ayrılan belleği serbest bırak
            struct BITKI* bitki = (struct BITKI*)canli;
            free(bitki);
        } else if (canli->tur == 'C' || canli->tur == 'S' || canli->tur == 'P') {
            // Böcek, Sinek veya Pire için ayrılan belleği serbest bırak
            struct BOCEK* bocek = (struct BOCEK*)canli;
            free(bocek);
        } 
    }
}