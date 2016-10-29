/*-- main.c --*/
#include "database.h"

/* Spatiu suplimentar alocat "just in case" */
#define EXTRA 5


/* Citesc baza de date dintr-un fisier text */
int readFromText(char *filename, DB **ag)
{ 
  int j, nr_analize, np;
  FILE *f;
  Pers *p;
  

  f = fopen(filename, "rt");
  if (!f) 
  { 
    printf("Eroare deschidere fisier %s\n", filename); 
    return -1; 
  }

  fscanf(f, "%i %i", &nr_analize, &np);

  (*ag) = aloca(np + EXTRA, nr_analize);

  (*ag)->nr_analize = nr_analize;
  (*ag)->nr_pers_curent = np;
  (*ag)->nr_pers_max = np + EXTRA;

  /* pointer folosit pentru parcurgerea vectorului de persoane */
  p = (*ag)->vect_pers;

  while (fscanf(f, "%s%s%s%i", p->nume, p->cod_identif, p->ocupatie, &p->grupa_sanguina) == 4)
  { 
    /* completare vector analize */
    for (j = 0; j < (*ag)->nr_analize; j++) 
      fscanf(f, "%i", p->analize+j);
    
    p++;
  }

  fclose(f);

  return 1;
}


/* Salvez baza de date intr-un fisier binar. */
int writeToBinary(char *filename, DB *ag)
{
  FILE* f;
  f = fopen(filename, "wb");
  if (!f) 
  { 
    printf("Eroare deschidere fisier %s\n", filename); 
    return -1; 
  }

  /* scriu nr analize */
  fwrite(&ag->nr_analize, sizeof(int), 1, f);

  /* scriu nr persoane */
  fwrite(&ag->nr_pers_curent, sizeof(int), 1, f);

  /* scriu vector analize */
  fwrite(ag->vect_analize, sizeof(int), ag->nr_analize * ag->nr_pers_curent, f);

  /* scriu vector persoane */
  fwrite(ag->vect_pers, sizeof(Pers), ag->nr_pers_curent, f);


  fclose(f);

  return 1;
}



int main(int argc, char *argv[])
{ 
  DB *ag, *ap;
  FILE*f;
  char numefis[61];
  int nr_analize, np;
  
  /* Verificam daca avem numarul corect de parametrii. */
  if(argc != 2)
  {
    printf("Numar incorect de argumente!\nVa rugam apelati astfel: \t%s nume_fisier\n", argv[0]);
    return -1;
  }

  /* Functia de citire intoarce 1 in caz de succes. 
  Altfel, nu are rost sa continuam. */
  if(readFromText(argv[1], &ag) != 1)
    return -1;

  /* afisez baza de date */
  //afiseaza(ag);
  apel(ag);
  
  /* eliberez spatiul */
  elibereaza(&ag);

  printf("\nSfarsit program\n");

  return 1;
}
