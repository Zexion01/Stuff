/*-- tlg.h --- LISTA SIMPLU INLANTUITA GENERICA ---*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

#ifndef _LISTA_GENERICA_
#define _LISTA_GENERICA_

typedef struct celulag
{ 
  void* info;           /* adresa informatie */
  struct celulag *urm;   /* adresa urmatoarei celule */
} TCelulaG, *TLG, **ALG; /* tipurile Celula, Lista si Adresa_Lista */

typedef int (*TFElem)(void*);     /* functie prelucrare element */
typedef int (*TFCmp)(void*, void*); /* functie de comparare doua elemente */

typedef void (*TF)(void*);     /* functie afisare/eliberare un element */

typedef int (*TFHash)(void*);

typedef struct
{
	size_t M;
	TFHash fh;
	TLG *v;
} TH;


/*- inserare la inceput reusita sau nu (1/0) -*/
int InsLG(ALG, void*, size_t);

void DistrugeLG(ALG, TF fe); /* eliminare celula si element */

void Distruge(ALG aL, TF fe); /* distruge lista */

size_t LungimeLG(ALG);   /* numarul de elemente din lista */

/* afiseaza elementele din lista, folosind o functie de tip TFAfi */
void Afisare(ALG, TF);
        
TH* IniTH(size_t M, TFHash fh);
typedef void (*TF) (void*);
void DistrTH(TH**aa, TF fe);
void AfiTH(TH*a, TF afiEl);
void *ExistaTH(TH*a, void*ae, TFCmp f);
int InsTH(TH*a, void*ae, size_t d, TFCmp f);
int ExtrTH(TH*a, void*ae, TFCmp f);
#endif
