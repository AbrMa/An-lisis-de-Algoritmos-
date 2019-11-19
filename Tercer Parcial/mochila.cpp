#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <algorithm>
#include <string>
#define TAM 1000
#define rojito     "\x1b[31m"
#define verdesito  "\x1b[32m"
#define NORMAL   "\x1b[0m"
using namespace std;

int how_many[TAM][TAM];
int color[TAM][TAM];
char yes_no[TAM][TAM];
pair<int,int> origin[TAM][TAM];
vector<string> ans;

void initialize_values(int number_of_items, int capacity);
void dp(int number_of_items, int capacity, vector <int> item_benefit, vector <int> item_weight, vector<string> item_name);
void print_answer(int number_of_items, int capacity, vector <int> item_benefit, vector <int> item_weight, vector <string> item_name);

int main()
{
	int number_of_items, capacity;
	cin >> number_of_items >> capacity;
	vector <int> item_weight(number_of_items + 1);
	vector <int> item_benefit(number_of_items + 1);
	vector <string> item_name(number_of_items + 1);
	item_weight.push_back(0);
	item_benefit.push_back(0);
	item_name.push_back("");
	for (int i = 1; i <= number_of_items; i++)
		cin >> item_name[i] >> item_benefit[i] >> item_weight[i];	
	
	initialize_values(number_of_items, capacity);
	dp(number_of_items, capacity, item_benefit, item_weight, item_name);
	print_answer(number_of_items, capacity, item_benefit, item_weight, item_name);
	return 0;
}

void initialize_values(int number_of_items, int capacity)
{
	for (int i = 0; i <= number_of_items; i++)
		for (int j = 0; j <= capacity; j++)
		{
			color[i][j] = how_many[i][j] = origin[i][j].first = origin[i][j].second = 0;
			yes_no[i][j] = 'N';
		}
}

void dp(int number_of_items, int capacity, vector <int> item_benefit, vector <int> item_weight, vector<string> item_name)
{
	for (int i = 1; i <= number_of_items; i++)
		for (int j = 1; j <= capacity; j++)
		{
			if (j < item_weight[i])
			{
				how_many[i][j] = how_many[i - 1][j];	
				origin[i][j].second = j;
			}
			else
			{
				int yes = item_benefit[i] + how_many[i - 1][j - item_weight[i]];
				int no = how_many[i - 1][j];
				if (yes >= no)
				{
					how_many[i][j] = yes;
					yes_no[i][j] = 'S';
					origin[i][j].second = j - item_weight[i];
				}
				else
				{
					how_many[i][j] = no;
					origin[i][j].second = j;
				}
			}
			origin[i][j].first = i - 1;
		}
	int i = number_of_items, j = capacity;
	while (i > 0 || j > 0)
	{
		cout << " i " << i << " j " << j << endl;
		color[i][j] = 1;
		if (yes_no[i][j] == 'S')
			ans.push_back(item_name[i]);
		int m = origin[i][j].first;
		int k = origin[i][j].second;
		i = m;
		j = k;
	}
}

void print_answer(int number_of_items, int capacity, vector <int> item_benefit, vector <int> item_weight, vector <string> item_name)
{
	system("clear");

	cout << "Ren\t\tObj\t\tBen\t\tPes" << endl << endl;
	for (int i = 1; i <= number_of_items; i++)
		cout << i << "\t\t" << item_name[i] << "\t\t" << item_benefit[i] << "\t\t" << item_weight[i] << endl;
	cout << endl << endl;

	cout << "Ren\tCapacidad" << endl << endl <<"\t";
	for (int i = 0; i <= capacity; i++)
		cout << verdesito  << i << NORMAL  << "\t";
	cout << endl << endl;
	for (int i = 0; i <= number_of_items; i++)
	{
		cout << verdesito << i << NORMAL << "\t";
		for (int j = 0; j <= capacity; j++)
		{
			if (i > 0 && j > 0)
			{
				if (color[i][j] > 0)
					cout << rojito << yes_no[i][j] << "(" << origin[i][j].first << "," << origin[i][j].second << ")\t" << NORMAL;
				else
					cout << yes_no[i][j] << "(" << origin[i][j].first << "," << origin[i][j].second << ")\t";
			}
			else
				cout << "\t";
		}
		cout << endl << "\t";
		for (int j = 0; j <= capacity; j++)
		{
			if (color[i][j] > 0)
				cout << rojito << how_many[i][j] << "\t" << NORMAL;
			else
				cout << how_many[i][j] << "\t";
		}
		cout << endl << endl;
	}

	cout << "Se debe tomar lo siguiente" << endl;
	for (int i = 0; i <= number_of_items; i++)
		cout << ans[i] << "\t";
	cout << endl;
}
