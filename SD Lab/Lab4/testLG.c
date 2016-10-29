/*-- testLG.c -- prelucrare lista generica de pointeri la puncte din plan */
#include "tlg.h"

typedef struct { int x, y; } TPunct; /* punct in plan */


int InsLG(ALG aL, void* ae, size_t d)
{
  TLG aux = malloc(sizeof(TCelulaG));
  if(!aux) return 0;
  aux->info = malloc(d);
  if (!aux->info)          
  { free(aux); return 0;}
  memcpy(aux->info, ae, d);
  aux->urm = *aL;
  *aL = aux;
  return 1;
}

void DistrugeLG(ALG aL) /* eliminare celula si element */
{ 
  TLG aux = *aL;     /* adresa celulei eliminate */
  if (!aux) return; /* lista vida */
  free(aux->info);  /* elib.spatiul ocupat de element*/
  *aL = aux->urm;    /* deconecteaza celula din lista */
  free(aux);   /* elibereaza spatiul ocupat de celula */
}

void Distruge(ALG aL) /* distruge lista */
{
  while(*aL != NULL)
    DistrugeLG(aL);
}

size_t LungimeLG(ALG a)      /* numarul de elemente din lista */
{ 
  size_t lg = 0;
  TLG p = *a;
  for (; p != NULL; p = p->urm) lg++;  /* parcurge lista, numarand celulele */
  return lg;
}

void AfiElInt(void * ae)
{
  TPunct p = *(TPunct*)ae;
  printf("[%d %d] ", p.x, p.y);
}

void Afisare(ALG aL, TFAfi afiEL)
{ 
  if(!*aL) { printf("Lista vida\n"); return;}
  printf("Lista: ");
  for(; *aL; aL = &(*aL)->urm)
    afiEL((*aL)->info);
  printf("\n");
}

int AfisareCond (TLG a, TLG b) {
	int nr=0;
	TLG p,q;
	TPunct *pa, *pb;
	p=a; 
	for(;p!=NULL;p=p->urm){
		pa=(TPunct *) p->info;
		q=b;
		for(;q!=NULL;q=q->urm) {
			pb=(TPunct *) q->info;
			if(pa->y==pb->y ){
				nr++;
				AfiElInt(p->info);
        
				AfiElInt(q->info);
			}
		}
	}
	return nr;
}

TLG GenerareLG(size_t N, size_t v1, size_t v2)
{
  TLG r = NULL, u, aux;
  TPunct p;
  srand(time(NULL));
  for(; N > 0; N--)
  {
    p.x = rand() % (v2-v1+1) + v1; 
    p.y = rand() % (v2-v1+1) + v1;
    aux = (TLG)malloc(sizeof(TCelulaG));
    if(!aux) return r;
    aux->info = (TPunct*)malloc(sizeof(TPunct));
    if(!aux->info) {free(aux); return r;}
    memcpy(aux->info, &p, sizeof(TPunct));
    aux->urm = NULL;
    if(r == NULL) r = aux;
    else u->urm = aux;
    u = aux;
  }
  return r;
}

TLG Copie (TLG l, TFCmp cmp, int *nr) {
	*nr =0;
	TLG r=NULL, p, ant=NULL;
	ALG u;
	TPunct pa;
	for(p=l; p!=NULL; p=p->urm)
		{pa=*(TPunct *)p->info;
			if(pa.y==-pa.x) {
				u=&r;//adresa de inceput
				while(*u!=NULL){
					if(cmp((*u)->info,p->info)>=0)
						break;
			
					u=&(*u)->urm;
				}
			InsLG(u,p->info,sizeof(TPunct));
			(*nr)++;
			}
	}
	return r;
}

TLG Muta (ALG l, TFCmp cmp, int *nr)
{
	TLG r=NULL,p,ant;
	ALG u;
	*nr=0;
	p=*l; 
  int ok;
	while(p)
  {
    ok=1;
		TPunct pa=*(TPunct *)p->info;
		if(pa.y==-pa.x)
    { 
			u=&r;
			while(*u!=NULL)
      {
				if(cmp((*u)->info,p->info)>=0)
					break;
				u=&(*u)->urm;
			}
			if(*u==NULL || cmp((*u)->info, p->info)>0)
      {
  			InsLG(u, p->info, sizeof(TPunct));
        (*nr)++;
        DistrugeLG(&p);
   			ok=0;
      }
  	}
	 	if(ok==1) 
			p=p->urm;
  }
	return r;
}	

		
int comPunct (void *ae1, void *ae2){
	TPunct p1=*(TPunct *) ae1;
	TPunct p2=*(TPunct *) ae2;
	if(p1.x!=p2.x)
		return p1.x-p2.x;
	return p1.y-p2.y;
}

int main()
{ 
  TLG x = NULL, y=NULL, r=NULL;
  int nr=0;
  x = GenerareLG(10, -5,5);
  Afisare(&x, AfiElInt);
  r=Muta(&x,comPunct,&nr);
  Afisare(&r, AfiElInt);
  Afisare(&x,AfiElInt);
  //printf("\n Elem=");
  //AfisareCond(x,y);
  /* secvente de test */

  
  //Distruge(&x);
  Distruge(&r);
  return 0;
}

