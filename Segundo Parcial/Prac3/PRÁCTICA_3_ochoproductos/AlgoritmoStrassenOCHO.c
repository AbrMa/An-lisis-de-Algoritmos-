#include <stdio.h>
#include <string.h>
#include <curses.h>
#include <math.h>
#include <stdlib.h>

void strassen_ocho_productos(int *A, int *B, int *C, int m, int n);

int main(){
	
    int i,j,n,m;
	char nombreM_A[100], nombreM_B[100];
	FILE*f;
	
	system("clear");
	printf("Escriba m x n\n");
    scanf("%d%d",&m,&n);
	
	int A[m][n],B[m][n],C[m][m];
	printf("\nMatriz A\n");
	fflush(stdin);
	gets(nombreM_A);

	f = fopen(nombreM_A,"r");
	if(f == NULL){printf("Error: No se ha podido abrir el fichero\n");exit(0);}
	else
	{
		for (i=0; i<m; i++)
			for (j=0; j<n; j++){fscanf(f,"%d", &A[i][j]);}
		fclose(f);
	}
	printf("\nMatriz B\n");
	fflush(stdin);
	gets(nombreM_B);
	f = fopen(nombreM_B,"r");
	if(f == NULL){printf("Error: No se ha podido abrir el fichero\n");exit(0);}
	else
	{
		for (i=0; i<m; i++)
			for (j=0; j<n; j++){fscanf(f,"%d", &B[i][j]);}
		fclose(f);
	}
    
    for(i=0;i<m;i++)
        for(j=0;j<m;j++)
            C[i][j]=0;

	strassen_ocho_productos(*A,*B,*C,m,m);
	system("clear");

	printf ("\nMatriz A\n");
    for(i=0;i<m;i++){
        printf("\n\t|\t");
        for(j=0;j<m;j++){printf("%d\t",A[i][j]);}
		printf ("|");	
    }

   	printf ("\nMatriz B\n");
    for(i=0;i<m;i++){
        printf("\n\t|\t");
        for(j=0;j<m;j++){printf("%d\t",B[i][j]);}
		printf ("|");	
    }

   	printf ("\nMatriz C\n");
    for(i=0;i<m;i++){
        printf("\n\t|\t");
        for(j=0;j<m;j++){printf("%d\t",C[i][j]);}
		printf ("|");	
    }
	
	return 0;
}

void strassen_ocho_productos(int *A, int *B, int *C, int m, int n)
{
	if(m==2)
	{
        
		int uno = *A * *B;
		int dos = *(A + 1) * *(B + n); 
		int tres = *A * *(B + 1);
		int cuatro = *(A + 1) * *(B + n + 1) ; 
		int cinco = *(A + n) * *B;
		int seis =  *(A + n + 1) * *(B + n);  
		int siete = *(A + n) * *(B + 1);
		int ocho = *(A + n + 1) * *(B + n + 1); 
        *C = *C + uno + dos; 
        *(C + 1) = *(C + 1) + tres + cuatro;
		*(C + n) = *(C + n)+ cinco + seis;  
        *(C + n + 1) = *(C + n + 1) + siete + ocho;  
    }
    else
    {
        m /= 2;
        strassen_ocho_productos(A, B, C, m, n);
        strassen_ocho_productos(A + m, B + (m * n), C, m, n);
        strassen_ocho_productos(A, B + m, C + m, m, n);
        strassen_ocho_productos(A + m, B + m * (n + 1), C + m, m, n);
        strassen_ocho_productos(A + (m * n), B, C + (m * n), m, n);
        strassen_ocho_productos(A + (m * (n + 1)), B + (n * m), C + (m * n), m, n);
		strassen_ocho_productos(A + (m * n), B + m, C + (m * (n + 1)), m, n);
        strassen_ocho_productos(A + (m * (n + 1)) , B + (m * (n + 1)), C + (m * (n + 1)), m, n);
    }
}