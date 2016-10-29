#include <stdio.h>

int main ()
{	
	int i, n, min, poz, j, aux, v[50];
	scanf ("%d", &n);
	printf ("\n");
	for ( i = 0; i <= n-1; i++)
	{
		scanf ("%d", &v[i]);
	}
	printf ("\n");
	for ( i = 0; i <= n-1; i++)
	{
		min = v[i];
		poz = i;
		for (j = i; j <= n-1; j++)
		{
			if (v[j] < v[i])
			{
				min = v[j];
				poz = j;
			}
		}
		aux = v[i];
		v[i] = min;
		v[poz] = aux;
	}
	for ( i = 0; i <= n-1; i++)
	{
		printf ("%d ", v[i]);
	}
	return 0;
}
