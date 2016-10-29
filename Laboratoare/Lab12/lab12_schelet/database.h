/*-- database.h --*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct
  { char nume[30], ocupatie[14], cod_identif[16];
    int grupa_sanguina, *analize;  /* adresa vector rez.analize */
  } Pers;
typedef struct
  { Pers *vect_pers; /* adrese vector pers */
    int nr_pers_curent, nr_analize, *vect_analize;
    int nr_pers_max;
  } DB, *ADB;


ADB aloca(int MP, int NA);
void afiseaza(DB *ag);
void elibereaza(ADB* aag);
int readFromText(char *filename, DB **ag);
int writeToBinary(char *filename, DB *ag);
