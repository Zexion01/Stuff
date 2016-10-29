/*--- TestLista.c ---*/
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

typedef int TEL;     /* tipurile Element si Adresa_Element */
typedef struct celula
{ TEL info;
  struct celula * urm;
} TCelula, *TLista, **ALista; /* tipurile Celula, Lista si Adresa_Lista */

  
TLista AlocCelula(TEL e)          /* adresa celulei create sau NULL */
{ TLista aux = (TLista)malloc(sizeof(TCelula));  /* (1) incearca alocare */
  if (aux)                            /* aux contine adresa noii celule */
  { aux->info = e;                   /* (2,3) completeaza noua celula */
    aux->urm = NULL;
  }
  return aux;             /* rezultatul este adresa noii celule sau NULL */
}

void AfisareL(TLista L)
       /* afiseaza valorile elementelor din lista */
{ 
  printf("Lista: [");                      /* marcheaza inceput lista */
  for (; L != NULL; L = L->urm)       /* pentru fiecare celula */
    printf("%d ", L->info);              /* afiseaza informatie */
  printf("]");                               /* marcheaza sfarsit lista */
}

void DistrugeL(ALista aL)
{
  TLista aux;
  while(*aL)
  {
    aux = *aL;
    *aL = aux->urm;
    free(aux);
  }
}

TLista CitireL(size_t *lg)     /* construieste lista cu elemente citite */
{ TLista L = NULL, u, aux;
  TEL x;
  char ch;
  for(*lg = 0; scanf("%i", &x) == 1; )  
  { 
    aux = AlocCelula(x);           /* incearca inserarea valorii citite */
    if(!aux) return L;              /* alocare esuata => sfarsit citire */
    if(L == NULL) L = aux;
    else u->urm = aux;
    u = aux;
    (*lg)++;
  }
  
  while((ch=getchar()) != EOF && ch != '\n');
  return L;                     /* intoarce lista rezultat */
}

int Elimina(ALista aL, int a, int b, int* nr_elim)
{
  TLista L=*aL,ant=NULL;
  *nr_elim=0;
  int count=0;
  while(L)
  {
    if(L->info >= a && L->info <= b)
    {
      if(ant==NULL)
        {
          *aL=(*aL)->urm;
          L=L->urm;
          (*nr_elim)++;
        }
      else
      {
        ant->urm=L->urm;
        free(L);
        L=L->urm;
        (*nr_elim)++;
      }
    }
    else
    {
      ant=L;
      L=L->urm;
      count++;
    }
  }
  return count;
}

int contains(TLista a, TEL el)
{
  TLista p=a;
  while(p)
  {
    if(p->info==el)
      return 1;
    p=p->urm;
  }
  return 0;
}

TLista Diferenta(TLista a, TLista b, int* lungime)
{
  TLista aux,p,r=NULL;
  *lungime=0;
  p=a;
  while(p)
  {
    if(contains(b,p->info)==0)
    {
      aux=(TLista)malloc(sizeof(TCelula));
      aux->info=p->info;
      if(r==NULL)
      {
        r=aux;
      }
      else
      {
        aux->urm=r;
        r=aux;
      }
      (*lungime)++;
    }
    p=p->urm;
  }
  return r;
}



TLista Muta(TLista L, int a, int b)
{
  TLista r=NULL,p=NULL;
  ALista aP=NULL;

  for(;L;L=L->urm)
  {
    if(L->info >= a)
    {
      p=L;
      break;
    }
  }
  *aP=p;
  for(;*aP;*aP=(*aP)->urm)
  {
    if((*aP)->info >= b)
    {
      if((*aP)->urm)
      {
        L->urm=(*aP)->urm;
        (*aP)->urm=NULL;
        break;
      }
      else if(!(*aP)->urm)
      {
        L->urm=NULL;
        break;
      }
    }
  }
  return p;
}

int main ()
{ TLista x,y = NULL;
  TLista r=NULL;     /* Lista prelucrata */
  size_t lx,ly;
  int lungime;
  int nr_elim; 
  int a,b;          /* lungime lista */
   
  for (;;)
  { 
    /* citeste si afiseaza lista */
    printf("\nIntroduceti valori elemente terminate cu valoare nenumerica:\n");
    x = CitireL(&lx);
    //y = CitireL(&ly);
    //AfisareL(x);
    if(!x) continue;
    /* apeluri functii implementate */
    //printf("Nr de elemente ramase=%d\n", Elimina(&x,a,b,&nr_elim));
    //printf("Nr elim=%d\n",nr_elim);
    //r=Diferenta(x,y,&lungime);
    //printf("Lungime=%d\n",lungime);
    printf("Intervalul:\n");
    scanf("%d%d",&a,&b);
    r=Muta(x,a,b);
    AfisareL(r);
    //Elimina(&x,a,b,&nr_elim);
    printf("Lista x \n");
    AfisareL(x);
    DistrugeL(&x);
    //DistrugeL(&r);
    printf ("\n  Inca un test ? [d/n]");
    if (getchar() == 'n') break;
  }
}
