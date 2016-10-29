/*--- TestLista.c ---*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

typedef int TEL;     /* tipurile Element si Adresa_Element */
typedef struct celula
{ TEL info;
  struct celula * urm;
} TCelula, *TLista, **ALista; /* tipurile Celula, Lista si Adresa_Lista */

#define VidaL(L) ((L) == NULL)

TLista AlocCelula(TEL e)          /* adresa celulei create sau NULL */
{ TLista aux = (TLista)malloc(sizeof(TCelula));  /* (1) incearca alocare */
  if (aux)                            /* aux contine adresa noii celule */
  { aux->info = e;                   /* (2,3) completeaza noua celula */
    aux->urm = NULL;
  }
  return aux;             /* rezultatul este adresa noii celule sau NULL */
}


/*-- operatii elementare --*/

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


void prelucreazaLista ( TLista L)
{
	int i = 1;
	for(; L->urm != NULL ; L = L->urm)
	{

		if ((L->info * L->urm->info < 0 && i % 2 == 1))
			printf ("Indicele: %d , Valorile: %d %d\n",i,L->info,L->urm->info);
		i++;
	}
}

int verificaIdentic (TLista A , TLista B)
{
	for (; A->urm != NULL && B->urm != NULL ; A = A->urm , B = B->urm)
	{
		if (A->info != B->info)
			return 0;
	}

	if (A->urm != NULL || B->urm != NULL)
		return 0;
	return 1;
}

int secventaLista (ALista aL ,int *inc ,int *fin)
{
	*inc = -1;
	*fin = -1;
	TLista L=*aL;
	int ok = 0;
	int contor = 1;

	for(; L->urm != NULL ; L = L->urm)
	{
		if (L->info > L->urm->info)
		{
			if (ok == 0)
			{
				*inc = contor;
				*fin = contor+1;
				ok = 1;
			}
			else
			{
				*fin = contor + 1;
			}
		}
		else if (ok == 1)
			break;
		contor++;
	}
	if (ok == 0)
		return 0;
	else
		return *fin-*inc+1;
}

int insert(TLista L)
{

	TLista aux,p,ant=NULL;
	p=L;
	int contor=0;
	while(p)
	{
		if(p->info%2==1)
		{
			aux=AlocCelula(p->info);
			aux->info=p->info;
			aux->urm=p->urm;
			p->urm=aux;
			contor++;
			p=p->urm->urm;
		}
		else
			p=p->urm;
	}
	return contor;

}

int Elimina(ALista aL, TEL x)
{
	TLista p=*aL,ant=NULL;
	while(p)
	{
		if(p->info==x)
			break;
		else
		{
			ant=p;
			p=p->urm;
		}
	}
	if(p==NULL)
		return 0;
	if(ant!=NULL)
	{
		ant->urm=p->urm;
		free(p);
	}
	else
		*aL=(*aL)->urm;

	return 1;
}


int EliminaT(ALista aL, TEL x)
{
  TLista p=*aL,ant=NULL;
  int contor=0;
  while(p)
  {
    if(p->info==x)
    {
      if(ant!=NULL)
      {
        ant->urm=p->urm;
        free(p);
        p=p->urm;
      }
      else
      {
        *aL=(*aL)->urm;
        p=p->urm;
      }
      contor++;
    }
    else
    {
      ant=p;
      p=p->urm;
    }
  }
  return contor;
}
int main ()
{ 
	int el,nr;
	TLista x = NULL;
  TLista y = NULL;	/* Lista prelucrata */
  size_t lx;           /* lungime lista */
	size_t ly;

	for (;;)
  { 
	/* citeste si afiseaza lista */
  		printf("\nIntroduceti valori elemente terminate cu valoare nenumerica:\n");
	 x = CitireL(&lx);
		
		AfisareL(x);
		printf("\n");

		if(!x) 
			continue;
	
		/*
		printf("Introduceti valori pentru y:\n");
		y = CitireL(&ly);
		printf("\n");

		
		if(!y)
			continue;
		*/

		//prelucreazaLista(x);
    		
		/*
		if (verificaIdentic(x,y))
			printf("Sunt identice!\n");
		else
			printf("Nu sunt identice\n");
		*/

		int inc;
		int fin;
		int lungime = 0;
		printf("Elementul care vreti sa fie eliminat\n");
		scanf("%d",&el);
		//EliminaT(&x,el);
    printf("Numarul de eliminari este %d\n",EliminaT(&x,el));
		//printf("Nr de inserari=%d\n",insert(x));
		AfisareL(x);
		//lungime = secventaLista(&x,&inc,&fin);
		
		//printf("Lungime:%d , Inceput:%d , Final:%d\n",lungime,inc,fin);
   		/* apeluri functii implementate */
   		//AfisareL(x);
		DistrugeL(&x);
		printf ("\n  Inca un test ? [d/n]");
		
		if (getchar() == 'n') 
			break;
  	}
}


