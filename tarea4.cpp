#include<iostream>
#include<string>
#include<fstream>
#include<cstdio>
//#include<unordered_map>
#include<cmath>
#include<vector>
#include<algorithm>
#include<utility>

using namespace std;

float matrix[5][5]={{9.9,3.0,5.0,4.0,1.0},
                    {9.9,3.0,4.0,4.0,1.0},
                    {4.0,3.0,9.9,3.0,1.0},
                    {4.0,4.0,4.0,3.0,1.0},
                    {5.0,4.0,5.0,9.9,3.3}};


vector<float> puntaje;
void promedio()
{
	float resultado=0.0;
	int n=0;
	for(int i=0;i<5;i++)
	{
		for(int j=0;j<5;j++)
		{	
			if(9.9!=matrix[i][j])
			{

				resultado+=matrix[i][j];
				cout<<resultado<<" , ";
				++n;
			}
		}
		cout<<endl;
		puntaje.push_back(resultado/n);
		resultado=0.0;
	}
}
int main()
{
	promedio();
	cout<<puntaje.size()<<endl;
}