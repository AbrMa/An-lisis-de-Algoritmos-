#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <string.h>
#include <sstream>
#include <math.h>
#include <stdlib.h>
#define lli long long int
using namespace std;

int is_a_power_of_2(int n);
int next_power_of_2(int n);
string fill_with_0(int n, string s);
lli multiplication(string x, string y, int n, int base);
int normalMultiplication(string x, string y, int base);
string sum(string num1, string num2, int base);
string base_n_rep(lli n, int base);
string binary_rep(lli n);
string hex_rep(lli n);

int main()
{
	lli pene = 0, a, b;
	cin >> a >> b;
	pene = a * b;
	cout << pene << endl;
	int base;
	string num1,num2;
	cin >> base >> num1 >> num2;
	int n = max(num1.size(),num2.size());
	n = next_power_of_2(n);
	num1 = fill_with_0(n, num1);
	num2 = fill_with_0(n, num2);
	cout << base_n_rep(multiplication(num1,num2,n,base),base) << endl;
	return 0;
}

int is_a_power_of_2(int n)
{
	return n && (!(n&(n-1)));
}

int next_power_of_2(int n)
{
	int p = 1;
   	if (is_a_power_of_2(n))
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

lli multiplication(string x, string y, int n, int base) 
{
	lli resultado;
	if (x.size() == 1)
		return normalMultiplication(x,y,base);
	else
	{
		string xi = x.substr(0,(x.size() / 2));	
		string xd = x.substr((x.size() / 2),(x.size() / 2));	
		string yi = y.substr(0,(y.size() / 2));	
		string yd = y.substr((y.size() / 2),(y.size() / 2));	
		string xi_plus_xd = sum(xi,xd,base);
		string yi_plus_yd = sum(yi,yd,base);
		int m = max(xi_plus_xd.size(),yi_plus_yd.size());
		m = next_power_of_2(m);
		xi_plus_xd = fill_with_0(m, xi_plus_xd);
		yi_plus_yd = fill_with_0(m, yi_plus_yd);
		lli p1 = multiplication(xi,yi,n/2,base);
		lli p2 = multiplication(xi_plus_xd,yi_plus_yd,m,base);
		lli p3 = multiplication(xd,yd,n/2,base);
		resultado = ((int)pow(base,n) * p1) + ((int)pow(base,(n / 2)) * (p2 - p1 - p3)) + p3;
	}
	return resultado;
}

string binary_rep(lli n)
{
	string s;
	if (n == 0)
		s.append("0");	
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

int normalMultiplication(string x, string y, int base)
{
	switch (base)
	{
		case 10:
		{
			return stoi(x) * stoi(y);
			break;
		}
		case 2:
		{
			return stoi(x,nullptr,2) * stoi(y,nullptr,2);			
			break;
		}
		case 16:
		{
			return stoi(x,nullptr,16) * stoi(y,nullptr,16);			
			break;
		}
		default:
			return -1;
	}
	return -1;
}

string sum(string num1, string num2, int base)
{
	lli res;
	switch (base)
	{
		case 2:
		{
			res =  stoi(num1,nullptr,2) + stoi(num2,nullptr,2);			
			return binary_rep(res);
			break;	
		}
		case 10:
        	{
            		res = stoi(num1) + stoi(num2);
            		return to_string(res);
            		break;
        	}
		case 16:
		{
			res = stoi(num1,nullptr,16) + stoi(num2,nullptr,16);			
			stringstream ss;
			ss << hex << res;
			string hex_rep = ss.str();
			return hex_rep;
			break;
		}
		default:
			return "0";
	}
	return "0";
}

string base_n_rep(lli n, int base)
{
	switch(base)
	{
		case 10:
		{
			return to_string(n);
			break;
		}
		case 2:
		{
			return binary_rep(n);
			break;
		}
		case 16:
		{
			stringstream ss;
			ss << hex << n;
			string hex_rep = ss.str();
			return hex_rep;
			break;
		}
		default:
			return "Base no válida";
	}
	return "Base no válida";
}
