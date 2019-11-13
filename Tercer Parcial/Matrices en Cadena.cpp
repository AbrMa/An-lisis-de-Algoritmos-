#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <string>
using namespace std;
#define MAX 10000
#define rojito     "\x1b[31m"
#define verdesito  "\x1b[32m"
#define NORMAL   "\x1b[0m"

pair<int,int> M[MAX][MAX];
pair<int, pair <int,int> > O[MAX][MAX];
pair<string, string> S[MAX][MAX];

void llenarDiagonal(int num_matrices, vector< pair <int,int> > A);
void imprimeMatriz(int num_matrices);
void dp(int num_matrices, vector< pair <int,int> > A);
void imprimeOrden(int num_matrices);

int main()
{
	int num_matrices;
	cin >> num_matrices;
	vector< pair <int,int> > matrices(num_matrices);
	for (int i = 0; i < num_matrices; i++)
	{
		int a, b;
		cin >> a >> b;
		matrices[i].first = a;
		matrices[i].second = b;
	}
	llenarDiagonal(num_matrices, matrices);
	dp(num_matrices, matrices);
	imprimeMatriz(num_matrices);
	imprimeOrden(num_matrices);
	return 0;
}

void llenarDiagonal(int num_matrices, vector< pair <int,int> > A)
{
	for (int i = 0; i < num_matrices; i++)
		for (int j = 0; j < num_matrices; j++)
		{
			M[i][j].first = O[i][j].first = O[i][j].second.first = O[i][j].second.second = 0; 
			S[i][j].first = "";
		}

	for (int i = 1; i < num_matrices ; i++)
	{
		M[i - 1][i].first = A[i - 1].first * A[i - 1].second * A[i].second;	
		O[i - 1][i].first = A[i - 1].first;
		O[i - 1][i].second.first = A[i - 1].second;
		O[i - 1][i].second.second = A[i].second;
		S[i - 1][i].first = S[i - 1][i].second = to_string(i - 1).append(to_string(i));
	}
}

void imprimeMatriz(int num_matrices)
{
	system("clear");
	cout << endl << endl;
	cout << "COSTO MIN" << endl << "\t";
	for (int i = 0; i < num_matrices; i++)
		cout << "|\t" << i << "\t\t";
	cout << endl << endl;
	cout << "\t";
	for (int i = 0; i < num_matrices; i++)
		cout << "|\tMAX\tMIN" <<"\t";
	cout << endl << endl;
	for (int i = 0; i < num_matrices; i++)
	{
		cout << i << "\t";
		for (int j = 0; j < num_matrices; j++)
		{ 
			cout << "|\t";
			if (M[i][j].second == 0)
				cout << "x"<< "\t";
			else
				cout << rojito << M[i][j].second << NORMAL << "\t";
			if (M[i][j].first == 0)
				cout << "x"<< "\t";
			else
				cout << verdesito <<  M[i][j].first << NORMAL  << "\t";
		}
		cout << endl;		
	}
}

void imprimeOrden(int num_matrices)
{
	cout << endl << endl;
	cout << "ORDEN MIN" << endl << "\t";
	for (int i = 0; i < num_matrices; i++)
		cout << "|\t" << i << "\t\t";
	cout << endl << endl;
	for (int i = 0; i < num_matrices; i++)
	{
		cout << i << "\t";
		for (int j = 0; j < num_matrices; j++)
		{ 
			cout << "|\t";
			if (M[i][j].first == 0)
				cout << "x"<< "\t\t";
			else
				cout << verdesito <<  S[i][j].first << NORMAL  << "\t\t";
		}
		cout << endl;		
	}

	cout << endl << endl;
	cout << "ORDEN MAX" << endl << "\t";
	for (int i = 0; i < num_matrices; i++)
		cout << "|\t" << i << "\t\t";
	cout << endl << endl;
	for (int i = 0; i < num_matrices; i++)
	{
		cout << i << "\t";
		for (int j = 0; j < num_matrices; j++)
		{ 
			cout << "|\t";
			if (M[i][j].first == 0)
				cout << "x"<< "\t\t";
			else
				cout << rojito <<  S[i][j].second << NORMAL  << "\t\t";
		}
		cout << endl;		
	}

	/*
	cout << endl << endl;
	for (int i = 0; i < num_matrices; i++)
		cout << "\t|\t" << i << "\t\t";
	cout << endl << endl;
	for (int i = 0; i < num_matrices; i++)
	{
		cout << i << "\t";
		for (int j = 0; j < num_matrices; j++)
		{ 
			cout << "|\t";
			if (M[i][j].first == 0)
				cout << "x"<< "\t\t";
			else
				cout << rojito <<  O[i][j].first  << "*" << O[i][j].second.first  <<"*" << O[i][j].second.second << NORMAL  << "\t\t";
		}
		cout << endl;		
	}
	*/
}

void dp(int num_matrices, vector< pair <int,int> > A)
{
	for (int i = 2; i < num_matrices; i++)
	{
		int cont = 0;
		for (int j = i; j < num_matrices; j++)
		{

			//Guardar costos
			int izquierdo = M[cont][j - 1].first + O[cont][j - 1].first * O[cont][j - 1].second.second * A[j].second;
			int abajo = M[cont + 1][j].first + A[cont].first * A[cont].second * A[j].second;
			M[cont][j].first = min(izquierdo, abajo);
			M[cont][j].second = max(izquierdo, abajo);

			//Guardar orden
			string cad_izq = "(" + S[cont][j - 1].first + ")" + to_string(j);
			string cad_abj = to_string(cont) + "(" + S[cont + 1][j].first + ")";
			if (izquierdo <= abajo)
			{
				S[cont][j].first = cad_izq;
				S[cont][j].second = cad_abj;
			}
			else
			{
				S[cont][j].first = cad_abj;
				S[cont][j].second = cad_izq;
			}

			//Guardar dimensiones	
			if (izquierdo > abajo)
			{
				O[cont][j].first = O[cont][j - 1].first;
				O[cont][j].second.first = O[cont][j - 1].second.second;
			}
			else
			{
				O[cont][j].first = A[cont].first;
				O[cont][j].second.first = A[cont].second;
			}
			O[cont][j].second.second = A[j].second;

			cont++;			
		}
	}
}
