/**-- test-ab.c --  prelucreaza arbori binari cu chei intregi --*/
#include "tarb.h"
//#include math.h

/*-- se completeaza cu definitiile functiilor implementate --*/

void RSD(TArb a)
{
	if(!a) {printf("-"); return;}
	if(!a->st && !a->dr) {printf(" %d ", a->info); return;}
	printf(" %d ", a->info);
	printf("(");
	RSD(a->st);
	printf(",");
	RSD(a->dr);
	printf(")");
}

int Numara(TArb a)
{
	if (!a) return 0;
	if(!(a->st) && !(a->dr))
		return 0;
	int s=0;
	if(a->st && a->dr==NULL)
		s+=a->st->info;
	else if(a->dr && a->st==NULL)
		s+=a->dr->info;
	else
		s+=a->dr->info + a->dr->info;
	if(a->info>s)
	{
		printf("%d\n",a->info);
		return 1+Numara(a->st)+Numara(a->dr);
	}
	return Numara(a->st) + Numara(a->dr);
}

int ParcurgeAux(TArb a, int niv)
{
	int ordin=0,ok;
	if(a==NULL)
		return 0;
	if(a->st)
		ordin++;
	if(a->dr)
		ordin++;
	ok=0;
	if(a->info%2==ordin%2)
	{
		printf("%d\n",a->info);
		ok=1;
	}
	niv++;
	return ok+ParcurgeAux(a->st,niv)+ParcurgeAux(a->dr,niv);
}

int Parcurge(TArb a)
{
	return ParcurgeAux(a,0);
}

int Val(TArb a)
{
	int nr=0;
	if(!a)
		return 0;
	return abs(a->info%2) + Val(a->st) + Val(a->dr);
}

int Identice(TArb a, TArb b)
{
	if(a==NULL && b==NULL)
		return 1;
	else if(a!=NULL && b!=NULL)
		return (a->info==b->info && Identice(a->st,b->st) && Identice(a->dr,b->dr));
	else
		return 0;
}
int main ()
{
	TArb arb,b;

	randomize();
	do {
		arb = ConstrAA (5, random(16), -50, 50);
		b = ConstrAA (5, random(16), -50, 50);
		AfiArb (arb);
		printf ("noduri: %i   niveluri: %i\n", 
			NrNoduri(arb), NrNiv(arb));
		AfiArb (b);
		printf ("noduri: %i   niveluri: %i\n", 
			NrNoduri(b), NrNiv(b));
		RSD(b);
		printf("\n");
		printf("%d\n", Identice(arb,b));
		//printf("Numara=%d\n", Numara(arb));
		//printf("Parcurge=%d\n",Parcurge(arb));
		//printf("%d\n", Val(arb));
		/*-- se completeaza cu apelurile functiilor implementate --*/

		DistrArb (&arb);
		printf ("\nInca un arbore ? [D/N] ");

		if (getchar() == 'n') break;
		printf("\n");
	} while (1);

	return 0;
}
