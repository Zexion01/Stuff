/*--- functiiLG.c -- operatii de baza pentru lista simplu inlantuita generica---*/
#include "tlg.h"

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

void DistrugeLG(ALG aL, TF free_elem) /* eliminare celula si element */
{ 
  TLG aux = *aL;     /* adresa celulei eliminate */
  if (!aux) return; /* lista vida */
  free_elem(aux->info);  /* elib.spatiul ocupat de element*/
  *aL = aux->urm;    /* deconecteaza celula din lista */
  free(aux);   /* elibereaza spatiul ocupat de celula */
}

void Distruge(ALG aL, TF free_elem) /* distruge lista */
{
  while(*aL != NULL)
    DistrugeLG(aL, free_elem);
}

size_t LungimeLG(ALG a)      /* numarul de elemente din lista */
{ 
  size_t lg = 0;
  TLG p = *a;
  for (; p != NULL; p = p->urm) lg++;  /* parcurge lista, numarand celulele */
  return lg;
}

void Afisare(ALG aL, TF afiEL)
{ 
  if(!*aL) { printf("Lista vida\n"); return;}
  printf("Lista: ");
  for(; *aL; aL = &(*aL)->urm)
    afiEL((*aL)->info);
  printf("\n");
}


//functii facute la curs
TH* IniTH(size_t M, TFHash fh)
{
	TH*h=(TH*)calloc(sizeof(TH),1);
	if (!h) 
	{	
		printf("eroare alocare hash\n");
		return NULL;
	}
	h->v=(TLG*)calloc(M, sizeof(TLG));
	if(!h->v)
	{
		printf("eroare alocare vector de pointeri TLG in hash\n");
		free(h);
		return NULL;
	}
	h->M=M;
	h->fh=fh;
	return h;
}

void DistrTH(TH** ah, TF fe)
{
	TLG*p,el,aux;

	//am folosit parcurgere cu pointeri ca sa o aveti si pe aceasta
	for (p=(*ah)->v;p<(*ah)->v+(*ah)->M;p++)
	{
//daca exista elemente corespunzatoare acestui hash
//eliberam info din celula si apoi eliberam celula
			for(el=*p;el!=NULL;)
			{
				aux=el;
				el=el->urm;
				fe(aux->info);
				free(aux);	
			}	
			
	}
	free((*ah)->v);
	free(*ah);
	*ah=NULL;		
}

void AfiTH(TH*ah, TF afiEl)
{
	TLG*p, el;
	for(p=ah->v; p<ah->v+ah->M;p++)
	{
		if(*p)
		{
			printf("%d: ",p-ah->v);
			for(el=*p;el!=NULL;el=el->urm)
				afiEl(el->info);
			printf("\n");
		}
	}

}

//daca elementul exista intoarcem 0
//altfel incercam sa-l inseram si intoarcem rezultatul inserarii
int InsTH(TH*a,void*ae, size_t d, TFCmp f)
{
	int cod=a->fh(ae), rez;
	TLG el;
    
	for(el=a->v[cod];el!=NULL; el=el->urm)
	{
		if(!f(el->info, ae))
			return 0;	
	}
	rez=InsLG(a->v+cod,ae,d); //reminder: a->v+cod <=> &a->v[cod]
	return rez;	
}


/*-- testLG.c -- prelucrare lista generica de pointeri la puncte din plan */
#include "tlg.h"
#include <string.h>

//persoana are un nume si un nr de telefon
//telefonul are forma 0701234567 (10 caractere intre 0-9)+ \0.
//primul caracter este '0'
typedef struct {char*nume, telMobil[11];}TPers;


//generez un cod  unic pentru primele 2 caractere din sir (convertite la lowercase)
//aa-> intoarce 0
//ab-> intoarce 1
//ba-> intoarce 25...
int codHashNume(void*a)
{
	char *p=((TPers*)a)->nume;
	return (*p-'a')*('z'-'a')+*(p+1)-'a';
}

int codHashTel(void*a)
{
	char *p=((TPers*)a)->telMobil+2;
	//intoarcem numarul format de cifrele 2-4 ale nr de tel
	//ex 0725195234 => 251
	return (*p-'0')*100+(*(p+1)-'0')*10+*(p+2)-'0';
}

void AfiElPers(void * ae)
{
  TPers *p = (TPers*)ae;
  printf("[%s %s]\n ", p->nume, p->telMobil);
}

void* copie (void* el)
{
	TPers* p=(TPers*)el, *rez;
	rez=malloc(sizeof(TPers));
    if(!rez) return NULL;
	strcpy(rez->telMobil, p->telMobil);
	rez->nume=strdup(p->nume);
    if(!rez->nume) {free(rez);return NULL;}
	return rez;

}

TLG GenerareListaPers(size_t nrPers)
{
	/*citesc in ordine pentru nr pers
		numele - o linie de max 100 caractere
		nr telefon - o linie max 10 caractere+\0
	 */
	int i, succes;
	char buf[100];
	TLG r=NULL;
	TPers p;
	for(i=0;i<nrPers;i++)
	{
		fgets(buf,99, stdin);
		p.nume=strdup(buf);
		p.nume[strlen(p.nume)-1]='\0';
		if(!p.nume)
			return r;
		fgets(buf,99,stdin);
		strncpy(p.telMobil, buf,10);
		p.telMobil[10]='\0';
		succes=InsLG(&r,&p,sizeof(TPers));
		if(!succes)
			return r;
	}
	return r;
}

//functii care compara 2 persoane dupa nume respectiv dupa telefon
int cmpPersNume(void *p1,void*p2)
{
	return strcmp( ((TPers*)p1)->nume,((TPers*)p2)->nume );
}

int cmpPersTel(void *p1,void*p2)
{
	return strcmp( ((TPers*)p1)->telMobil,((TPers*)p2)->telMobil );
}

//functie care elibereaza spatiul alocat pentru o persoana
//este folosita de DistrTH
void elibPers(void * p)
{
	free( ((TPers*)p)->nume);
}

//vom folosi 2 hash-uri
//primul este folosit pentru a indexa numele si ia in calcul primele 2 caractere ale numelui (convertite in prealabil la lowercase)
//al doilea hash este folosit pentru a indexa numerele de telefon si ia in calcul cifrele de pe pozitiile 2-4 (primele 2 presupunem ca sunt 07)

TH* GenerareHash(TLG listaPers,TH**ah2)
{
	TH*h1,*h2;//cele 2 hash-uri generate
	TLG p; 
	int rez1,rez2;
	TPers* copiePers;
	//calcul dimensiuni maxime pt hash-uri
	size_t M1=('z'-'a')*('z'-'a'), M2=1000;
	
	//initializez cele 2 hash-uri cu functiile de hashing aferente
	//tratam erorile de alocare
	h1=(TH*)IniTH(M1,codHashNume);
	if(!h1){ *ah2=NULL; return NULL;}
	
	h2=(TH*) IniTH(M2,codHashTel);
	if(!h2){*ah2=NULL; DistrTH(&h1, elibPers); return NULL;}
	
	//pentru fiecare celula din lista creez o copie a informatiei si o inserez in hash
	//daca alocarea nu reuseste distrug cele 2 hash-uri si intorc NULL;
	for(p=listaPers;p!=NULL;p=p->urm)
	{
		copiePers=copie(p->info);	
		if(!copiePers)
		{
			*ah2=NULL;
			DistrTH(&h1, elibPers);
			DistrTH(&h2, elibPers);
			return NULL;
		}
		rez1=InsTH(h1,copiePers, sizeof(TPers), cmpPersNume);
		copiePers=copie(p->info);
		if(!copiePers)
		{
			*ah2=NULL;
			DistrTH(&h1, elibPers);
			DistrTH(&h2, elibPers);
			return NULL;
		}
		rez2=InsTH(h2,copiePers, sizeof(TPers), cmpPersTel);
		//TODO: tratati erorile de inserare
	}
	*ah2=h2;
	return h1;
}


int hasprefix(char* sir, char* prefix)
{
	if(strlen(prefix)>strlen(sir))
		return -1;
	return strncmp(prefix,sir,strlen(prefix));
}

int NumaraPersoane(TH* h,char* prefix)
{
	int nr=0;
	TLG *p;
	TLG el;
	TPers *pers;
	for(p=h->v;p<h->v + h->M;p++)
	{
		if(*p)
		{
			for(el=*p;el!=NULL;el=el->urm)
			{
				pers=(TPers*)el->info;
				if(hasprefix(pers->nume,prefix)==0)
					nr++;
			}
		}
	}
	return nr;
}

int ListeIndice(TLG p, TLG q)
{
	if(LungimeLG(&p)!=LungimeLG(&q))
		return 0;
	while(p && q)
	{
		if(cmpPersNume(p,q)!=0 || cmpPersTel(p,q)!=0)
			return 0;
		p=p->urm;
		q=q->urm;
	}
	return 1;
}


int Identice(TH* h1, TH* h2)
{
	int i;
	if(h1->M!=h2->M)
		return 0;
	TLG *p;
	TLG *q;
	for(i=0;i<h1->M;i++)
	{
		p=h1->v+i;
		q=h2->v+i;
		if(ListeIndice(p,q)==0)
			return 0;
	}
	return 1;

}


int main()
{ 
 	TLG x = NULL;
 	TLG y = NULL;
 	TH *h1=NULL, *h2=NULL;
 	TH *h3=NULL, *h4=NULL;
  	//recomand sa aveti un fisier text cu linii
	//nume pers
	//nr telefon
	//char* prefix=(char*)malloc(20);
 	//printf("Dati prefixul:\n");
 	//fgets(prefix,20,stdin);
 	//prefix[strlen(prefix)-1]=0;
	x = GenerareListaPers(3);
	y = GenerareListaPers(3);
    if(!x && !y)
    {
        printf("Lista nu a putut fi generata\n");
        return 0;
    }
    
  	Afisare(&x, AfiElPers);
    Afisare(&y, AfiElPers);
	h1=GenerareHash(x,&h2);
	h3=GenerareHash(y,&h4);
    printf("tabela hash nume \n");
	AfiTH(h1,AfiElPers);
    
    printf("tabela hash numar telefon \n");
	AfiTH(h2,AfiElPers);
	//printf("Nr de persoane cu prefixul dat:%d\n",NumaraPersoane(h1,prefix));
  	
    /* secvente de test */
	printf("Rez=%d\n", Identice(h1,h2));
  	Distruge(&x, elibPers);
	DistrTH(&h1, elibPers);
	DistrTH(&h2, elibPers);
  	return 0;
}
