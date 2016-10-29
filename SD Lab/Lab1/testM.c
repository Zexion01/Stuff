/*-- testM-nesortate-int.c --*/
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef int(*TFComp)(const void *, const void *);

typedef struct
{ size_t d;        /* dimensiune elemente */
   void *p, *s, *t; /* adrese vector, sfarsit zona utila, disponibila */
   TFComp cmp; /* functia care verifica identitatea a doua elemente */
} TMultime;

#define VidaM(m) ((m)->s == (m)->p) 
#define PlinaM(m) ((m)->s == (m)->t) 

/*--- initializari ---*/


/*-- functiiM.c --*/

/*--- functii de initializare ---*/
void Copie(void* dest, void* sursa, size_t n)
{
  char *s = (char *)sursa, *sf=(char*)sursa + n, *d=(char *)dest;
  for(;s<sf;s++,d++)
    *d=*s;
}

TMultime *InitD(size_t n, size_t d, TFComp fcmp)
     /* creeaza multime, alocand dinamic spatiu pentru descriptor
        si n elemente de dimensiune d; intoarce adr.multime sau NULL */        
{ char *sf;
  TMultime *m = (TMultime*)calloc(1,sizeof(TMultime));
  if(!m) return NULL;                      /* alocare esuata */
  m->p = calloc(n, d);
  if(!m->p) { free(m); return NULL;}       /* alocare esuata */
  m->d = d;
  m->s = m->p;
  sf = (char*)(m->p) + d * n;
  m->t = (void*)sf;
  m->cmp = fcmp;
  return m;                          /* initializare reusita */        
}

void DistrugeM(TMultime **m)
{
   free((*m)->p);
   free(*m);
   *m = NULL;
}

int Cardinal(TMultime * m)
{
  return ((char*)m->s - (char*)m->p) / m->d;
}


/*--- operatii asupra multimilor NESORTATE ---*/

int Apartine(void * x, TMultime* m)
     /* intoarce 1/0 - elementul x exista/nu exista in multimea m */ 
{
  char *pm, *sf = (char*)(m->s);
  for(pm = (char*)(m->p); pm < sf; pm += m->d)
    if(m->cmp(x, (void*)pm) == 0) return 1;
  return 0;
}


int Adauga(void *nou, TMultime *m)
   /* obiectiv: adaugarea unui nou element la sfarsitul vectorului;
      intoarce 1/0/-1 - succes/exista deja/nu exista spatiu */
{ 
  char *sf = (char*)m->s;
  if(PlinaM(m)) return -1;         /* multime plina */
  if(Apartine(nou, m)) return 0;   /* nou exista deja in m -> gata */
  memcpy(m->s, nou, m->d);         /* copiaza nou la sfarsit m */
  sf += m->d;                      /* actualizeaza sfarsit */    
  m->s = (void*)sf;
  return 1;                        /* elementul a fost adaugat */
}

int DiferentaO(TMultime *a, TMultime *b, TMultime *r)
{
  int contor=0;
  char *pa,*sfa=(char*)(a->s);
  for(pa=(char*)(a->p);pa<sfa;pa+=a->d)
  {
    int gasit=0;
    char* pb,*sfb=(char*)(b->s);
    for(pb=(char*)(b->p);pb<sfb;pb+=b->d)
    {
      if(a->cmp(pa,pb)==0)
      {
        gasit=1;
        break;
      }
    }
    if(gasit==0)
    {
      Copie(r->s,pa,a->d);
      r->s+=a->d;
      contor++;
    }
  }
return contor;
}

int Intersectie(TMultime *a, TMultime *b, TMultime *r)
{
  int contor=0;
  char *pa,*sfa=(char*)(a->s);
  for(pa=(char*)(a->p);pa<sfa;pa+=a->d)
  {
    int gasit=0;
    char* pb,*sfb=(char*)(b->s);
    for(pb=(char*)(b->p);pb<sfb;pb+=b->d)
    {
      if(a->cmp(pa,pb)==0)
      {
        gasit=1;
        break;
      }
    }
    if(gasit==1)
    {
      Copie(r->s,pa,a->d);
      r->s+=a->d;
      contor++;
    }
  }
return contor;
}






/*-- functie de afisare multime intregi --*/
void AfisareMultime_int(TMultime *m)
{ int *x = (int*)(m->p), n = Cardinal(m), i = 0;
  printf("[");
  for( ; i < n; i++) 
	if(i != n-1) printf(" %i,", x[i]);
	else printf(" %i ]\n", x[i]);
}
                                                                                     
int compI(const void *a, const void *b) /*-- functie de comparare --*/
{ return *(int*)a - *(int*)b; }

int main()
{ 
  int max_dim;
  int va[20] = {-1, 23, 4, 6, -9, 4, 10}, nva = 7,
      vb[10] = {2, 4, -9, 12, 10, 1, 11}, nvb = 7; 
  
  TMultime *a, *b,*r;
  int i, rez;
  char* sf;
  
  /* constructie multime a */
  a = InitD(7, sizeof(int), compI);
  if(!a) {printf("eroare initializare\n"); return 1;}
  printf("\nConstructie multime a, cu elementele: ");
  for(i = 0; i < nva; i++) printf("%i ", va[i]);
  printf("\n");
  for(i = 0; i < nva; i++) 
  { 
    rez = Adauga((void*)(va+i), a);
    printf("%i %s\n", va[i], rez? "adaugat" : "exista deja");
  }
  printf("Cardinal(a) = %d,  ", Cardinal(a)); 
  printf("a: "); AfisareMultime_int(a);

                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
  /* constructie multime b */
  b=InitD(10, sizeof(int), compI); 
  printf("\nConstructie multime b, cu elementele: ");
  for(i = 0; i < nvb; i++) printf("%i ", vb[i]);
  printf("\n");
  for(i = 0; i < nvb; i++) 
  { rez = Adauga((void*)(vb+i), b);
    printf("%i %s\n", vb[i], rez? "adaugat" : "exista deja");
  }
  printf("Cardinal(b) = %d, ", Cardinal(b)); 
  printf("b: "); AfisareMultime_int(b);

  if (Cardinal(a)>Cardinal(b))
    max_dim=Cardinal(a);
  else
    max_dim=Cardinal(b);
  r=(TMultime*)calloc(1,sizeof(TMultime));
  r->d=a->d;
  r->p=calloc(max_dim,r->d);
  r->s=r->p;
  sf=(char*)r->p + max_dim * r->d;
  r->t=(void*)sf;
  printf("Dif:\n");
  DiferentaO(a,b,r);
  //qsort(r->p,Cardinal(r),r->d,r->cmp);
  AfisareMultime_int(r);

  r->s=r->p;
  printf("Int:\n");
  Intersectie(a,b,r);
  AfisareMultime_int(r);

  
  /* apeluri functii implementate */


  DistrugeM(&a);
  DistrugeM(&b);
  DistrugeM(&r); 
  return 0;
}
