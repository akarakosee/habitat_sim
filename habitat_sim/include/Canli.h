/**
* @author Ayberk Karaköse
* @since 02.05.2024
*/
#ifndef CANLI_H
#define CANLI_H

struct CANLI {
    int deger;
    char tur;
    char* (*gorunum)(); 
};

void canli_olustur(struct CANLI* canli, int deger, char tur);
void canli_yoket(struct CANLI* canli);

#endif