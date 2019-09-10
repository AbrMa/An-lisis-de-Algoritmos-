#include <stdio.h>
#include <stdlib.h>

void busqueda_secuencial(int *arreglo, int tam, int num_a_buscar);
void busqueda_binaria(int *arreglo, int tam, int num_a_buscar);

int main()
{
	int arreglo[20] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};

	printf("BÚSQUEDA SECUENCIAL\n");
	busqueda_secuencial(arreglo, 20, 1);
	busqueda_secuencial(arreglo, 20, 10);
	busqueda_secuencial(arreglo, 20, 20);
	busqueda_secuencial(arreglo, 20, 880);
	printf("\n\n");
	
	printf("BÚSQUEDA Binaria\n");
	busqueda_binaria(arreglo, 20, 1);
	busqueda_binaria(arreglo, 20, 10);
	busqueda_binaria(arreglo, 20, 20);
	busqueda_binaria(arreglo, 20, 880);
	printf("\n\n");


	return 0;
}

void busqueda_secuencial(int *arreglo, int tam, int num_a_buscar)
{
	int i, bandera = 0;
	for (i = 0; i < tam && bandera == 0; i++)
		if (num_a_buscar == arreglo[i])
			bandera = 1;
	if (bandera == 0)
		printf("No se encontró el número %d en el arreglo\n", num_a_buscar);
	else
		printf("Se encontró el número %d en el la posición %d, en %d pasos.\n", num_a_buscar, i - 1, i);
}

void busqueda_binaria(int *arreglo, int tam, int num_a_buscar)
{
	int i = 0, j = tam - 1, m, pasos = 0, bandera = 0;
	while (i <= j && bandera == 0)
	{
		m = i + (j - i) / 2;
		if (arreglo[m] == num_a_buscar)
			bandera = 1;
		if (arreglo[m] < num_a_buscar)
			i = m + 1;
		else
			j = m - 1;
		pasos++;
	}
	if (bandera == 0)
		printf("No se encontró el número %d en el arreglo\n", num_a_buscar);
	else
		printf("Se encontró el número %d en el la posición %d, en %d pasos.\n", num_a_buscar, m, pasos);
}
