#include <stdio.h>
#include <stdlib.h>

//Métodos para árbol de búsqueda binaria (necesarios).
struct nodo {
	int numero;
	struct nodo *izquierdo, *derecho;
};

typedef struct nodo Nodo;

Nodo* crearNodo(int dato);
void insertar(Nodo** raiz, int dato);

//Métodos de Búsqueda
Nodo* buscar(Nodo* raiz, int dato, int* pasos);
void buscar_Arbol(Nodo *raiz, int num_a_buscar);
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

	printf("BÚSQUEDA Árbol cargado a la izquierda\n");
	Nodo* raiz2 = NULL;
	insertar(&raiz2, 20);
	insertar(&raiz2, 19);
	insertar(&raiz2, 18);
	insertar(&raiz2, 17);
	insertar(&raiz2, 16);
	insertar(&raiz2, 15);
	insertar(&raiz2, 14);
	insertar(&raiz2, 13);
	insertar(&raiz2, 12);
	insertar(&raiz2, 11);
	insertar(&raiz2, 10);
	insertar(&raiz2, 9);
	insertar(&raiz2, 8);
	insertar(&raiz2, 7);
	insertar(&raiz2, 6);
	insertar(&raiz2, 5);
	insertar(&raiz2, 4);
	insertar(&raiz2, 3);
	insertar(&raiz2, 2);
	insertar(&raiz2, 1);
	buscar_Arbol(raiz2,1);
	buscar_Arbol(raiz2,10);
	printf("\n\n");

	printf("BÚSQUEDA Árbol Balanceado\n");
	Nodo* raiz = NULL;
	insertar(&raiz, 8);
	insertar(&raiz, 4);
	insertar(&raiz, 16);
	insertar(&raiz, 2);
	insertar(&raiz, 6);
	insertar(&raiz, 8);
	insertar(&raiz, 1);
	insertar(&raiz, 3);
	insertar(&raiz, 5);
	insertar(&raiz, 7);
	insertar(&raiz, 12);
	insertar(&raiz, 18);
	insertar(&raiz, 10);
	insertar(&raiz, 14);
	insertar(&raiz, 9);
	insertar(&raiz, 11);
	insertar(&raiz, 13);
	insertar(&raiz, 15);
	insertar(&raiz, 17);
	insertar(&raiz, 19);
	insertar(&raiz, 20);
	buscar_Arbol(raiz,20);
	buscar_Arbol(raiz,880);
	printf("\n\n");

	return 0;
}
//TAD Árbol de búsqueda
Nodo* crearNodo(int dato)
{
	Nodo* t;
	t = (Nodo*)malloc(sizeof(Nodo));
	t -> numero = dato;
	t -> izquierdo = t -> derecho = NULL;
	return t;
}

void insertar(Nodo **raiz, int dato)
{
	if (!(*raiz))
		*raiz = crearNodo(dato);
	else if (dato < (*raiz) -> numero)
		insertar(&((*raiz) -> izquierdo), dato);
	else
		insertar(&((*raiz) -> derecho), dato);
}

//Métodos de búsqueda
Nodo* buscar(Nodo* raiz, int dato, int* pasos)
{
	int encontrado = 0;
	while (!encontrado && raiz != NULL)
	{
		*pasos += 1;
		if (dato == raiz -> numero)
			encontrado = 1;
		else if (dato < raiz -> numero)
			raiz = raiz -> izquierdo;
		else if (dato > raiz -> numero)
			raiz = raiz -> derecho;
	}
	return raiz;
}

void buscar_Arbol(Nodo *raiz, int num_a_buscar)
{
	int pasos = 0;
	if(!buscar(raiz,num_a_buscar,&pasos))
		printf("No se encontró el número %d en el árbol, se dieron %d pasos.\n", num_a_buscar, pasos);
	else
		printf("Se encontró el número %d en el árbol, se dieron %d pasos.\n", num_a_buscar, pasos);
}

void busqueda_secuencial(int *arreglo, int tam, int num_a_buscar)
{
	int i, bandera = 0;
	for (i = 0; i < tam && bandera == 0; i++)
		if (num_a_buscar == arreglo[i])
			bandera = 1;
	if (bandera == 0)
		printf("No se encontró el número %d en el arreglo, se dieron %d pasos.\n", num_a_buscar, i);
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
		printf("No se encontró el número %d en el arreglo, se dieron %d pasos.\n", num_a_buscar, pasos);
	else
		printf("Se encontró el número %d en el la posición %d, en %d pasos.\n", num_a_buscar, m, pasos);
}
