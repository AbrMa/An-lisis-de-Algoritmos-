#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <string.h>
using namespace std;

int is_a_power_of_2(int n);
int next_power_of_2(int n);
string fill_with_0(int n, string s);
int multiplication(string x, string y, int n);
string binary_rep(int n);

int main()
{
	string num1,num2;
	cin >> num1 >> num2;
	int n = max(num1.size(),num2.size());
	n = next_power_of_2(n);
	num1 = fill_with_0(n, num1);
	num2 = fill_with_0(n, num2);
	cout << binary_rep(multiplication(num1,num2,n)) << endl;
	return 0;
}

int is_a_power_of_2(int n)
{
	return n && (!(n&(n-1)));
}

int next_power_of_2(int n)
{
    int p = 1;
    if (n && !(n & (n - 1)))
        return n;
    while (p < n)
        p <<= 1;
    return p;
}

string fill_with_0(int n, string s)
{
	if (is_a_power_of_2(s.size()) && s.size() == n)
		return s;
	string s2;
	for (int i = 0; i < n - s.size(); i++)
		s2.append("0"); 
	s2.append(s);
	return s2;
}

int multiplication(string x, string y, int n)
{
	int resultado;
	if (x.size() == 1)
	{
		if (x == "1" && y == "1")
			return 1;
		else
			return 0;
	}
	else
	{
		string xi = x.substr(0,(x.size() / 2));	
		string xd = x.substr((x.size() / 2),(x.size() / 2));	
		string yi = y.substr(0,(y.size() / 2));	
		string yd = y.substr((y.size() / 2),(y.size() / 2));	
		int power_of_2 = 1, half_power_of_2 = 1;
		power_of_2 <<= n;
		half_power_of_2 <<= n / 2;
		resultado = (power_of_2 * multiplication(xi,yi,(n / 2))) + 
			(half_power_of_2 * multiplication(xi,yd,(n / 2))) +  
			(half_power_of_2 * multiplication(xd,yi,(n / 2))) +  
			multiplication(xd,yd,(n / 2));
	}	
	return resultado;
}

string binary_rep(int n)
{
	string s;
	while (n)
	{
		if (n & 1)
			s.append("1");	
		else
			s.append("0");
		n >>= 1;
	}	
	reverse(s.begin(),s.end());
	return s;
}
