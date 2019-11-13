#include <stdio.h>
#include <stdlib.h>

int **crea_matriz(int n, int m);
int **ingresa_datos(int** matriz,int n, int m);
int validacion(int n, int m);
void imprime_matriz(int **matriz, int n, int m);
int **multiplicacion_matrices(int **matrizA, int **matrizB, int n, int m, int o, int p);

int main()
{
	int n, m, o, p, **matrizA, **matrizB;
	printf("Ingrese n m para la matriz A\n");
	scanf("%d %d", &n, &m);
	printf("Ingrese n m para la matriz B\n");
	scanf("%d %d", &o, &p);
	if (validacion(m,o))
	{
		matrizA = crea_matriz(n,m);		
		matrizB = crea_matriz(o,p);		
		system("clear");
		printf("Ingrese datos matriz A\n");
		matrizA = ingresa_datos(matrizA, n, m);	
		system("clear");
		printf("Ingrese datos matriz B\n");
		matrizB = ingresa_datos(matrizB, o, p);	
		system("clear");
		printf("La matriz A es: \n\n");
		imprime_matriz(matrizA, n, m);
		printf("\n\n");
		printf("La matriz B es: \n\n");
		imprime_matriz(matrizB, o, p);
		printf("\n\n");
		int **matrizC;
		matrizC = crea_matriz(n,p);
		matrizC = multiplicacion_matrices(matrizA,matrizB,n,m,o,p); 
		printf("La matriz C = A x B \n\n");
		imprime_matriz(matrizC, n, p);
		printf("\n\n");
	}
	else
		printf ("Las matrices no se pueden multiplicar %d != %d\n", m , o);
	return 0;
}

int **crea_matriz(int n, int m)
{
	int i, **matriz = NULL;
	matriz = (int**)malloc(n*sizeof(int*));
	for (i = 0; i < n; i++)
		matriz[i] = (int*)malloc(m*sizeof(int));
	return matriz;
}

int **ingresa_datos(int** matriz, int n, int m)
{
	int i, j;
	for (i = 0; i < n; i++)
		for (j = 0; j < m; j++)
		{
			printf("Ingrese pos (%d,%d)\n", i , j);
			scanf("%d", &matriz[i][j]);
		}
	return matriz;
}

void imprime_matriz(int **matriz, int n, int m)
{
	int i, j;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
			printf("%d\t", matriz[i][j]);
		printf("\n");
	}
}

int validacion(int n, int m)
{
	return n == m;
}

int **multiplicacion_matrices(int **matrizA, int **matrizB, int n, int m, int o, int p)
{
	int ** resultado = crea_matriz(n,p);
	int i, j, k, casilla = 0;
	for (i = 0; i < n; i++)
		for (j = 0; j < p; j++)
		{
			for (k = 0; k < m ; k++)
				casilla += matrizA[i][k] * matrizB[k][j];
			resultado[i][j] = casilla;
			casilla = 0;
		}
	return resultado;
}
