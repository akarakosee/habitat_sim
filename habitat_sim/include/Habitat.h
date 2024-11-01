/**
* @author Ayberk Karaköse
* @since 02.05.2024
*/
#ifndef HABITAT_H
#define HABITAT_H

#include <stdbool.h>
#include "Canli.h"

struct HABITAT {
    struct CANLI*** canlilar;
    int satir_sayisi;
    int sutun_sayisi;
};

void guncelleAktifVeDigerCanli(struct HABITAT* habitat, int* aktif_i, int* aktif_j, int* diger_i, int* diger_j, bool *devamEt);
int** sayisal_degerler_matrisi_olustur(const char* dosya_adi, int* satir_sayisi, int* sutun_sayisi);
double uzaklik_hesapla(int x1, int y1, int x2, int y2);
void habitat_olustur(struct HABITAT* habitat, const char* dosya_adi);
void habitat_yoket(struct HABITAT* habitat);
void habitat_yazdir(struct HABITAT* habitat);
void habitat_simuleet(struct HABITAT* habitat, int** sayisal_degerler_matrisi); 
struct CANLI* kazanani_bul(struct HABITAT* habitat, int *kazanan_i, int *kazanan_j);
bool canli_etkilesimi(struct HABITAT* habitat, int i, int* j);
bool yiyebilir(struct CANLI* aktif_canli, struct CANLI* diger_canli);
#endif