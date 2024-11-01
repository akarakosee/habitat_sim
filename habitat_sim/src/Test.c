/**
* @author Ayberk Karaköse
* @since 02.05.2024
*/
#include "Habitat.h"

int main() {
    struct HABITAT habitat;
    habitat_olustur(&habitat, "Veri.txt");

    // İlk durumu yazdır
    matris_yazdir(habitat.canlilar, habitat.satir_sayisi, habitat.sutun_sayisi); 

    habitat_simuleet(&habitat);

    // Matrisi ekrana yazdır
    habitat_yazdir(&habitat);

    habitat_yoket(&habitat);
    return 0;
}
}