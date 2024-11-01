/**
* @author Ayberk Karaköse
* @since 02.05.2024
*/
#include <stdio.h>
#include "Habitat.h"
#include <stdlib.h>

int main() {
    struct HABITAT habitat;
    int satir_sayisi, sutun_sayisi;
   
   int** sayisal_matris = sayisal_degerler_matrisi_olustur("bin/Veri.txt", &satir_sayisi, &sutun_sayisi);
    if (!sayisal_matris) {
        exit(1);
    }
    
	habitat_olustur(&habitat, "bin/Veri.txt"); 
    habitat_simuleet(&habitat, sayisal_matris);
    habitat_yoket(&habitat);

    for (int i = 0; i < satir_sayisi; i++) {
        free(sayisal_matris[i]);
    }
    free(sayisal_matris);

    return 0;
}