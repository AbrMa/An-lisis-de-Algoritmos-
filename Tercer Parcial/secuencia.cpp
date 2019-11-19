#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <algorithm>
#include <string>
#include <set>
#define MAX 10000
#define rojito     "\x1b[31m"
#define verdesito  "\x1b[32m"
#define amarillito "\x1b[33m"
#define azulcito    "\x1b[34m"
#define magentabb "\x1b[35m"
#define cyanbb   "\x1b[36m"
#define NORMAL   "\x1b[0m"
using namespace std;

int single_road = 1;
int roads[MAX][MAX];
int common_subsequence_size[MAX][MAX];
string origin[MAX][MAX];
set<string> answers;

void fill_initial_values(string sequence_one, string sequence_two);
void dp(string sequence_one, string sequence_two);
void print_table(string sequence_one, string sequence_two);
void print_subsequences(string sequence_one, string sequence_two);

int main()
{
	string read_only, sequence_one = "x" , sequence_two = "X";
	cin >> read_only;
	sequence_one.append(read_only);
	cin >> read_only;
	sequence_two.append(read_only);
	fill_initial_values(sequence_one, sequence_two);
	dp(sequence_one, sequence_two);
	print_table(sequence_one, sequence_two);
	print_subsequences(sequence_one, sequence_two);
	return 0;
}

void fill_initial_values(string sequence_one, string sequence_two)
{
	for (int i = 0; i < sequence_one.size(); i++)
		for (int j = 0; j < sequence_two.size(); j++)
		{
			common_subsequence_size[i][j] = roads[i][j] = 0;
			origin[i][j] = "";
		}
}

void dp(string sequence_one, string sequence_two)
{
	int up, left, m, k;
	for (int i = 1; i < sequence_one.size(); i++)
		for (int j = 1; j < sequence_two.size(); j++)
		{
			if (sequence_one[i] == sequence_two[j])
			{
				common_subsequence_size[i][j] = common_subsequence_size[i - 1][j - 1] + 1;
				origin[i][j] = "diag";
			}
			else
			{
				up = common_subsequence_size[i - 1][j];
				left = common_subsequence_size[i][j - 1];
				if (up >= left)
				{
					common_subsequence_size[i][j] = up;
					origin[i][j] = "sup";
				}
				else
				{
					common_subsequence_size[i][j] = left;
					origin[i][j] = "izq";
				}
			}
		}

		for (int i = sequence_one.size() - 1; i >= 1; i--)
		{

			for (int j = sequence_two.size() - 1; j >= 1; j--)
			{
				string ans = "";
				m = i;
				k = j;
				while (m >= 1 && k >= 1)
				{
					if (origin[m][k] == "diag")
					{
						ans.append(string(1,sequence_one[m]));
						m--;
						k--;
					}
					else if (origin[m][k] == "sup")
					{
						m--;
					}
					else if (origin[m][k] == "izq")
					{
						k--;
					}
				}
				reverse(ans.begin(), ans.end());
				if (ans.size()  == common_subsequence_size[sequence_one.size() - 1][sequence_two.size() - 1])
				{
					answers.insert(ans);
					m = i;
					k = j;
					if (roads[m][k] == 0)
					{
						while (m >= 1 && k >= 1)
						{
							if (origin[m][k] == "diag")
							{
								roads[m][k] = single_road;
								m--;
								k--;
							}
							else if (origin[m][k] == "sup")
							{
								roads[m][k] = single_road;
								m--;
							}
							else if (origin[m][k] == "izq")
							{
								roads[m][k] = single_road;
								k--;
							}
						}
						single_road += 1;
					}
				}
			}
		}
}

void print_table(string sequence_one, string sequence_two)
{
	int k = 0;
	system("clear");

	cout << "\t\t";
	for (int i = 1; i < sequence_two.size(); i++)
		cout << verdesito << sequence_two[i] << NORMAL << "\t" ;
	cout << endl << endl;

	for (int i = 0; i < sequence_one.size(); i++)
	{
		if (k)
			cout << verdesito << sequence_one[k] << NORMAL;
		cout << "\t"; 
		for (int j = 0; j < sequence_two.size(); j++)
			cout << common_subsequence_size[i][j] << "\t";
		cout << endl <<"\t";
		for (int j = 0; j < sequence_two.size(); j++)
		{
			if (roads[i][j] > 0)
			{
				if (roads[i][j] == 1)
					cout << rojito << origin[i][j] << "\t" <<NORMAL;	
				if (roads[i][j] == 2)
					cout << azulcito << origin[i][j] << "\t" <<NORMAL;	
				if (roads[i][j] == 3)
					cout << amarillito << origin[i][j] << "\t" <<NORMAL;	
			}
			else
				cout << origin[i][j] << "\t";
		}
		k++;
		cout << endl << endl;
	}
}

void print_subsequences(string sequence_one, string sequence_two)
{

	cout << "Las subsecuencias obtenidas son" << endl << endl;
	for (auto it=answers.begin(); it != answers.end(); ++it) 
        	cout << *it << '\t'; 
	cout << endl;
}
