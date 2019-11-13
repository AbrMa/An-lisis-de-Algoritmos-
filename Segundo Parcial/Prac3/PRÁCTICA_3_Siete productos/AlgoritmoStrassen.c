#include <stdio.h>
#include <string.h>
#include <curses.h>
#include <math.h>
#include <stdlib.h>

void strassen(int *, int *, int *, int, int);

int main(){
	
    int i,j,n,m;
	char nombreM_A[100], nombreM_B[100], txt[]=".txt";
	FILE*f;
	
	system("clear");

	printf("Multiplicacion de Matriz A y B\n\n");
	printf("Escriba m x n");
    scanf("%d%d",&m,&n);
	int A[m][n];
	printf("\nNombre Archivo Matriz A\n");
	fflush(stdin);
	gets(nombreM_A);
	
	f = fopen(nombreM_A,"r");
	if(f == NULL){printf("Error: No se ha podido abrir el fichero\n");exit(0);}
	else{
		for (i=0; i<m; i++)
			for (j=0; j<n; j++){fscanf(f,"%d", &A[i][j]);}
		fclose(f);
		}
	int B[m][n];
	printf("\nNombre Archivo Matriz A\n");
	fflush(stdin);
	gets(nombreM_B);
	f = fopen(nombreM_B,"r");
	if(f == NULL){printf("Error: No se ha podido abrir el fichero\n");exit(0);}
	else{
		for (i=0; i<m; i++)
			for (j=0; j<n; j++){fscanf(f,"%d", &B[i][j]);}
		fclose(f);
		}
    int C[m][m];
    for(i=0;i<m;i++)
        for(j=0;j<m;j++)
            C[i][j]=0;
	strassen(A,B,C,m,m);
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

   	printf ("\nMatriz resultado\n");
    for(i=0;i<m;i++){
        printf("\n\t|\t");
        for(j=0;j<m;j++){printf("%d\t",C[i][j]);}
		printf ("|");	
    }
	
	return 0;
}

void strassen(int *A, int *B, int *C, int m, int n){
	if(m==2){
        
		int P=(*A+*(A+n+1))*(*B+*(B+n+1)); 
		int Q=(*(A+n)+*(A+n+1))*(*B);   
		int R=(*A)*(*(B+1)-*(B+n+1));   
		int S=(*(A+n+1))*(*(B+n)-*B);   
		int T=(*A+*(A+1))*(*(B+n+1));   
		int U=(*(A+n)-*A)*(*B+*(B+1));  
		int V=(*(A+1)-*(A+n+1))*(*(B+n)+*(B+n+1));  

        *C=*C+P+S-T+V;  
        *(C+1)=*(C+1)+R+T;

		*(C+n)=*(C+n)+Q+S;  
        *(C+n+1)=*(C+n+1)+P+R-Q+U;  
    }
    else{
        m=m/2;

        strassen(A,B,C,m,n);
		strassen(A,B+m,C+m,m,n);
        strassen(A+m,B+m*n,C,m,n);
        strassen(A+m,B+m*(n+1),C+m,m,n);
        strassen(A+m*n,B,C+m*n,m,n);
        strassen(A+m*n,B+m,C+m*(n+1),m,n);
        strassen(A+m*(n+1),B+m*n,C+m*n,m,n);
        strassen(A+m*(n+1),B+m*(n+1),C+m*(n+1),m,n);
    }
}
