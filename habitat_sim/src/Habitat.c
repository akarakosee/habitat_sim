/**
* @author Ayberk Karaköse
* @since 02.05.2024
*/
#include <ctype.h>
#include <conio.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "Habitat.h"
#include "Canli.h"
#include "Bitki.h"
#include "Bocek.h"
#include "Sinek.h"
#include "Pire.h"

int** veri_oku(const char* dosya_adi, int* satir_sayisi, int* sutun_sayisi) {
    FILE* dosya = fopen(dosya_adi, "r");
    if (!dosya) {
        fprintf(stderr, "Dosya acilamadi: %s\n", dosya_adi);
        return NULL;
    }

    *satir_sayisi = 0;
    *sutun_sayisi = 0;
    int sayi;
    char karakter;
    int satirin_sutun_sayisi = 0;
    int max_sutun_sayisi = 0;

    while ((karakter = fgetc(dosya)) != EOF) {
        if (karakter == '\n' || karakter == '\r') {
            if (satirin_sutun_sayisi > 0) {  // Geçerli veri içeren satır varsa say
                (*satir_sayisi)++;
                if (satirin_sutun_sayisi > max_sutun_sayisi) {
                    max_sutun_sayisi = satirin_sutun_sayisi;
                }
                satirin_sutun_sayisi = 0; // Sütun sayısını sıfırla
            }
        } else if (isdigit(karakter)) {
            ungetc(karakter, dosya);
            fscanf(dosya, "%d", &sayi);
            satirin_sutun_sayisi++;
        }
    }

    // Dosya sonunda okunan verileri kontrol et
    if (satirin_sutun_sayisi > 0) {
        (*satir_sayisi)++;
        if (satirin_sutun_sayisi > max_sutun_sayisi) {
            max_sutun_sayisi = satirin_sutun_sayisi;
        }
    }

    *sutun_sayisi = max_sutun_sayisi; // En geniş sütun sayısını ayarla

    // Matris için hafıza ayır ve verileri tekrar oku
    rewind(dosya);
    int** matris = (int**)malloc(*satir_sayisi * sizeof(int*));
    for (int i = 0; i < *satir_sayisi; i++) {
        matris[i] = (int*)malloc(*sutun_sayisi * sizeof(int));
        for (int j = 0; j < *sutun_sayisi; j++) {
            if (fscanf(dosya, "%d", &matris[i][j]) != 1) {
                matris[i][j] = 0; // Eğer sayı okunamazsa, varsayılan olarak 0 değerini ata
            }
        }
    }

    fclose(dosya);
    return matris;
}

int** sayisal_degerler_matrisi_olustur(const char* dosya_adi, int* satir_sayisi, int* sutun_sayisi) {
    int** matris = veri_oku(dosya_adi, satir_sayisi, sutun_sayisi);
    if (!matris) {
        return NULL;
    }

    int** sayisal_matris = (int**)malloc(*satir_sayisi * sizeof(int*));
    for (int i = 0; i < *satir_sayisi; i++) {
        sayisal_matris[i] = (int*)malloc(*sutun_sayisi * sizeof(int));
        for (int j = 0; j < *sutun_sayisi; j++) {
            sayisal_matris[i][j] = matris[i][j];
        }
    }

    return sayisal_matris;
}

struct CANLI*** matris_canlilara_donustur(int** matris, int satir_sayisi, int sutun_sayisi) {
    struct CANLI*** canlilar = (struct CANLI***)malloc(satir_sayisi * sizeof(struct CANLI**));
    for (int i = 0; i < satir_sayisi; i++) {
        canlilar[i] = (struct CANLI**)malloc(sutun_sayisi * sizeof(struct CANLI*));
        for (int j = 0; j < sutun_sayisi; j++) {
            int deger = matris[i][j];
            if (deger >= 1 && deger <= 9) {
                struct BITKI* bitki = (struct BITKI*)malloc(sizeof(struct BITKI));
                bitki_olustur(bitki, deger);
                canlilar[i][j] = (struct CANLI*)bitki;
            } else if (deger >= 10 && deger <= 20) {
                struct BOCEK* bocek = (struct BOCEK*)malloc(sizeof(struct BOCEK));
                bocek_olustur(bocek, deger, 'C');
                canlilar[i][j] = (struct CANLI*)bocek;
            } else if (deger >= 21 && deger <= 50) {
                struct SINEK* sinek = (struct SINEK*)malloc(sizeof(struct SINEK));
                sinek_olustur(sinek, deger);
                canlilar[i][j] = (struct CANLI*)sinek;
            } else if (deger >= 51 && deger <= 99) {
                struct PIRE* pire = (struct PIRE*)malloc(sizeof(struct PIRE));
                pire_olustur(pire, deger);
                canlilar[i][j] = (struct CANLI*)pire;
            } else {
                fprintf(stderr, "Gecersiz deger: %d\n", deger);
                exit(1);
            }
        }
    }
    return canlilar;
}

void habitat_olustur(struct HABITAT* habitat, const char* dosya_adi) {
    int satir_sayisi, sutun_sayisi;

    // Sayısal matrisi dosyadan oku
    int** sayisal_matris = sayisal_degerler_matrisi_olustur(dosya_adi, &satir_sayisi, &sutun_sayisi);
    if (!sayisal_matris) {
        exit(1);
    }

    // Canlıları temsil eden matrisi dosyadan oku
    int** matris = veri_oku(dosya_adi, &habitat->satir_sayisi, &habitat->sutun_sayisi);
    if (!matris) {
        exit(1);
    }
    // Matristen canlı yapılarını oluştur
    habitat->canlilar = matris_canlilara_donustur(matris, habitat->satir_sayisi, habitat->sutun_sayisi);

    // Habitat simülasyonunu başlat
    habitat_simuleet(habitat, sayisal_matris);

    // belleği serbest bırak
    for (int i = 0; i < satir_sayisi; i++) {
        free(sayisal_matris[i]);
    }
    free(sayisal_matris);
}

void habitat_yoket(struct HABITAT* habitat) {
    for (int i = 0; i < habitat->satir_sayisi; i++) {
        for (int j = 0; j < habitat->sutun_sayisi; j++) {
            free(habitat->canlilar[i][j]);
        }
        free(habitat->canlilar[i]);
    }
    free(habitat->canlilar);
}

void habitat_yazdir(struct HABITAT* habitat) {
    for (int i = 0; i < habitat->satir_sayisi; i++) {
        for (int j = 0; j < habitat->sutun_sayisi; j++) {
            printf("%c ", habitat->canlilar[i][j]->tur);
        }
        printf("\n");
    }
}

double uzaklik_hesapla(int x1, int y1, int x2, int y2) {
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

void guncelleAktifVeDigerCanli(struct HABITAT* habitat, int* aktif_i, int* aktif_j, int* diger_i, int* diger_j, bool *devamEt) {
    bool aktifBulundu = false;
    for (int i = 0; i < habitat->satir_sayisi; i++) {
        for (int j = 0; j < habitat->sutun_sayisi; j++) {
            if (habitat->canlilar[i][j]->tur != 'X') {
                *aktif_i = i;
                *aktif_j = j;
                aktifBulundu = true;
                break;
            }
        }
        if (aktifBulundu) break;
    }

    if (!aktifBulundu) {
        *aktif_i = -1;
        *aktif_j = -1;
        *diger_i = -1;
        *diger_j = -1;
        *devamEt = false;
        return;
    }

    bool digerBulundu = false;
    for (int i = *aktif_i; i < habitat->satir_sayisi; i++) {
        for (int j = (i == *aktif_i ? *aktif_j + 1 : 0); j < habitat->sutun_sayisi; j++) {
            if (habitat->canlilar[i][j]->tur != 'X') {
                *diger_i = i;
                *diger_j = j;
                digerBulundu = true;
                break;
            }
        }
        if (digerBulundu) break;
    }

    if (!digerBulundu) {
        *diger_i = -1;
        *diger_j = -1;
        *devamEt = false;  // Diğer canlı bulunamazsa döngüyü sonlandır
    } else {
        *devamEt = true;  // Diğer canlı bulunduysa devam et
    }
}

bool yiyebilir(struct CANLI* aktif, struct CANLI* diger) {
    switch (aktif->tur) {
        case 'B': 
            return bitki_yiyebilir(diger);
        case 'C': 
            return bocek_yiyebilir(diger);
        case 'S': 
            return sinek_yiyebilir(diger);
        case 'P': 
            return pire_yiyebilir(diger);
        default:
            return false;
    }
}

bool canli_etkilesimi(struct HABITAT* habitat, int i, int* j) {
    struct CANLI* aktif_canli = habitat->canlilar[i][*j];
    if (aktif_canli->tur == 'X') return false;

    int k = *j + 1;
    while (k < habitat->sutun_sayisi && habitat->canlilar[i][k]->tur != 'X' && aktif_canli->tur != 'X') { 
        struct CANLI* karsilastirilan = habitat->canlilar[i][k];
        if (aktif_canli->deger > karsilastirilan->deger) {
            habitat->canlilar[i][k]->tur = 'X';
            *j = k; 
        } else {
            aktif_canli->tur = 'X'; 
            *j = k; 
            return false; 
        }
        k++; 
    }

    *j = k - 1; 
    return true; 
}

struct CANLI* kazanani_bul(struct HABITAT* habitat, int *kazanan_i, int *kazanan_j) {
    for (int i = 0; i < habitat->satir_sayisi; i++) {
        for (int j = 0; j < habitat->sutun_sayisi; j++) {
            if (habitat->canlilar[i][j]->tur != 'X') { // Eğer canlı hala yaşıyorsa
                *kazanan_i = i; // Kazananın satır indexini kaydet
                *kazanan_j = j; // Kazananın sütun indexini kaydet
                return habitat->canlilar[i][j]; // Kazanan canlıyı döndür
            }
        }
    }
    return NULL; // Eğer kazanan yoksa NULL döndür
}

void habitat_simuleet(struct HABITAT* habitat, int** sayisal_degerler_matrisi) {
    int aktif_i = 0;
    int aktif_j = 0;
    int diger_i = 0;
    int diger_j = 1; // Başlangıçta diğer canlı aktif canlının sağındaki canlı
    bool devamEt = true;

    guncelleAktifVeDigerCanli(habitat, &aktif_i, &aktif_j, &diger_i, &diger_j, &devamEt); // İlk güncelleme

    while (devamEt) {
		printf("\033[2J\033[H");
        habitat_yazdir(habitat);
	
        if (aktif_i == -1 || aktif_j == -1) break; // Tüm canlılar öldüyse döngüyü kır

        // Diğer canlının 'X' olup olmadığını kontrol et ve gerekirse diger_j'yi artır
        while (diger_j < habitat->sutun_sayisi && habitat->canlilar[diger_i][diger_j]->tur == 'X') {
            diger_j++;
        }

        // Diğer canlı satır sonuna ulaştıysa, bir sonraki satıra geç
        if (diger_j == habitat->sutun_sayisi && diger_i < habitat->satir_sayisi - 1) {
            diger_i++;
            diger_j = 0;
        }

        // Hem aktif hem de diğer canlı hayatta ise etkileşimi gerçekleştir
        if (habitat->canlilar[aktif_i][aktif_j]->tur != 'X' && diger_i < habitat->satir_sayisi && 
            habitat->canlilar[diger_i][diger_j]->tur != 'X') {
            struct CANLI* aktif_canli = habitat->canlilar[aktif_i][aktif_j];
            struct CANLI* diger_canli = habitat->canlilar[diger_i][diger_j];

            if (aktif_canli->tur == diger_canli->tur) {
                int aktif_deger = sayisal_degerler_matrisi[aktif_i][aktif_j];
                int diger_deger = sayisal_degerler_matrisi[diger_i][diger_j];

                if (aktif_deger > diger_deger) {
                    diger_canli->tur = 'X';
                } else if (aktif_deger < diger_deger) {
                    aktif_canli->tur = 'X';
                    // Aktif canlı öldüğü için yeni aktif canlı belirlenmesi gerekiyor
                } else {
                    double aktif_uzaklik = uzaklik_hesapla(aktif_i, aktif_j, habitat->satir_sayisi - 1, habitat->sutun_sayisi - 1);
                    double diger_uzaklik = uzaklik_hesapla(diger_i, diger_j, habitat->satir_sayisi - 1, habitat->sutun_sayisi - 1);
                    if (aktif_uzaklik < diger_uzaklik) {
                        aktif_canli->tur = 'X';
                    } else {
                        diger_canli->tur = 'X';
                    }
                }
            } else {
                // Farklı tür etkileşimi, yeme yeteneğini kontrol et
                if (yiyebilir(aktif_canli, diger_canli)) {
                    diger_canli->tur = 'X';
                } else if (yiyebilir(diger_canli, aktif_canli)) {
                    aktif_canli->tur = 'X';
                }
            }
            guncelleAktifVeDigerCanli(habitat, &aktif_i, &aktif_j, &diger_i, &diger_j, &devamEt); // Güncelleme ve devam kontrolü
        } else {
            devamEt = false; // Etkileşim imkanı yoksa döngüyü sonlandır
        }
    }

	printf("\033[2J\033[H");
    habitat_yazdir(habitat);

    int kazanan_i = -1, kazanan_j = -1;
    struct CANLI* kazanan = kazanani_bul(habitat, &kazanan_i, &kazanan_j);

    if (kazanan) {
        printf("Kazanan: %c : (%d,%d)\n", kazanan->tur, kazanan_i, kazanan_j);
    } else {
        printf("Kazanan yok!\n");
    }
}
