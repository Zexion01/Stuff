/*-- lista2.h -- Lista generica dublu inalntuita, circulara, cu santinela
              si info = pointer la element --*/
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>


#ifndef _LISTA_DUBLU_INLANTUITA_
#define _LISTA_DUBLU_INLANTUITA_
typedef struct
{
	char nume[20];
	float nota;
}TStudent;

typedef struct celula2
{ struct celula2 *pre, *urm;  /* legaturi spre celulele vecine */
  void *info;              /* adresa element extern */
} TCelula2, *TLDI;

/* Initializare lista vida; info santinela = NULL */
TLDI InitLDI(); 

/* Inserare dupa celula cu adresa p -> 1/0. Preconditia: spatiul pentru 
   elementul cu adresa x a fost alocat si actualizat la nivelul aplicatiei */
int InsDupa(TLDI p, void* x); 

/* elimina celula de la adresa p; rezultat: adresa elementului sau NULL */
void* ExtrLDI(TLDI p);       
    
/*- functii de eliberare spatiu; parametrul fe � functie care elibereaza 
    spatiul ocupat de element */
void ResetLDI(TLDI s); /* transforma lista in lista vida */
void DistrLDI(TLDI * as);
     /* elibereaza tot spatiul ocupat de lista, inclusiv santinela */
void AfisareLDI(TLDI s, void (*afiEl)(void *));  /* afisare lista */
#endif
 
 int InsDupa(TLDI a, void* x)  /* inserare dupa celula cu adresa a -> 1/0 */
{
	TLDI aux = (TLDI)malloc(sizeof(TCelula2));
	if(!aux) return 0;
	aux->info = x; 
	aux->pre = a; 
	aux->urm = a->urm; 
	a->urm->pre = aux; 
	a->urm = aux;
    return 1;
}


void ResetLDI(TLDI s)
     /* transforma lista in lista vida */
{ 
	TLDI p = s->urm, aux;
	while(p != s)
	{
		aux = p;
		p = p->urm;
		free(aux->info); 
		free(aux);
	}	
	s->urm = s->pre = s;
}

void DistrLDI(TLDI* as)
     /* elibereaza tot spatiul ocupat de lista, inclusiv santinela */
{ 
	ResetLDI(*as);
	free(*as);
	*as = NULL;
}

TLDI InitLDI()
    /* -> lista vida, cu info din santinela specifica aplicatiei */
{ 
	TLDI aux = (TLDI)malloc(sizeof(TCelula2));
    if (!aux) return NULL;
    
	aux->pre = aux->urm = aux;
    aux->info = NULL;
	
	return aux;     /* rezultatul este adresa santinelei sau NULL */
}

void AfisareLDI(TLDI s, void (*afiEl)(void *))
    /* afisare lista */
{
	TLDI p;
	printf("Lista: ");
	if(s->urm == s) 
	{
		printf("vida\n");
		return;
	}
	for(p = s->urm; p != s; p = p->urm)
		afiEl(p->info);
	printf("\n");
}


void AfiInt(void * ax)
{
	printf("%d ", *(int*)ax);
}

void CitireLDI(TLDI s, int* lg)
{
	int *ax, x;
 	char ch;
	
  	printf("se citesc valori numerice, terminate cu caracter nenumeric\n");
	for(*lg = 0; scanf("%i", &x) == 1; )  
  	{ 
        ax = (int*)malloc(sizeof(int));
		if(!ax) return;  
	 	*ax = x;
		InsDupa(s->pre, ax);
    		(*lg)++;
  	}
  	while((ch=getchar()) != EOF && ch != '\n');
}

void AfiStudent(void* x)
{
	TStudent *st;
	st=(TStudent*)x;
	printf("%s  %f \n",st->nume,st->nota);
}

int f(void* x)
{
	TStudent *st;
	st=(TStudent*)x;
	if(st->nota>=5)
		return 1;
	else
		return 0;
}


void parcurgere(TLDI s)
{
	TLDI p=s->urm;
	TLDI q=s->pre;
	int maxp=0;
	int maxi=1;
	while(p!=q && q->urm!=p)
	{
		if(*(int*)p->info % 2 == 0 && *(int*)p->info > maxp)
			maxp=*(int*)p->info;
		if(*(int*)q->info % 2 == 1 && *(int*)q->info > maxi)
			maxi=*(int*)q->info;
		p=p->urm;
		q=q->pre;
	}
	printf("Max par=%d\n Max imp=%d \n",maxp,maxi);
}


void CitireStudenti(TLDI s, int n)
{	
	int not;
	TStudent *ax, x;
 	int i;
	for(i=0;i<n;i++)  
  	{ 
        ax = (TStudent*)malloc(sizeof(TStudent));
        scanf("%s",x.nume);
        scanf("%f",&x.nota);
		if(!ax) return;  
	 	*ax = x;
		InsDupa(s->pre, ax);		
  	}
}

void Copie(TLDI s, int (*f)(void*))
{
	TLDI q=s->pre,el;
	for(el=s->urm;el->pre!=q;el=el->urm)
	{
		if(f(el->info)==1)
			InsDupa(s->pre,el->info);
	}
}

int main()
{
	TLDI s;
	int lg;
	int n;
	printf("Numar de studenti:");
	scanf("%d",&n);

	for(; ; )
	{
		s = InitLDI();
		//CitireLDI(s, &lg);
		//AfisareLDI(s, AfiInt);
	
		/* apeluri functii */
		CitireStudenti(s,n);
		Copie(s,f);
		AfisareLDI(s,AfiStudent);
		//parcurgere(s);
		DistrLDI(&s);
		printf ("\n  Inca un test ? [d/n]");    
		if (getchar() == 'n') break;
	}
    return 1;
}
