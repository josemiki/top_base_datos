#include<iostream>
#include<string>
#include<fstream>
#include<cstdio>
#include<cmath>

using namespace std;


float matrix[8][8]={{3.5,2.0,5.0,3.0,0.0,0.0,5.0,3.0},
                        {2.0,3.5,1.0,4.0,4.0,4.5,2.0,0.0},
                        {0.0,4.0,1.0,4.5,1.0,4.0,0.0,0.0},
                        {4.5,0.0,3.0,0.0,4.0,5.0,3.0,5.0},
                        {5.0,2.0,5.0,3.0,0.0,5.0,5.0,4.0},
                        {1.5,3.5,1.0,4.5,0.0,4.5,4.0,2.5},
                        {2.5,0.0,0.0,4.0,4.0,4.0,5.0,3.0},
                        {2.0,3.0,0.0,2.0,1.0,4.0,0.0,0.0}};
float matrix_m[26][25];

float distancia_manhattan(int col1,int col2)
{
    float resultado=0.0;
    for(int i=0;i<8;i++)
    {
        resultado=resultado+=(fabs(matrix[i][col1]-matrix[i][col2]));
    }
    return resultado;
}

float distancia_euclidea(int col1,int col2)
{
    float resultado=0.0;
    for(int i=0;i<8;i++)
    {
	if((matrix[i][col1]!=0.0&&matrix[i][col2]!=0.0))
	//cout<<"x1:  "<<matrix[i][col1]<<"  "<<"x2:  "<<matrix[i][col2]<<endl;
	//cout<<"x1-x2:  "<<matrix[i][col1]-matrix[i][col2]<<endl;
	//cout<<"potencia:   "<<pow((matrix[i][col1]-matrix[i][col2]),2.0)<<endl;
	//cout<<pow((matrix[i][col1]-matrix[i][col2]),2)<<endl;
        resultado=resultado+=(pow((matrix[i][col1]-matrix[i][col2]),2.0));
	//cout<<"resultado:   "<<resultado<<endl;
    }
    return sqrt(resultado);
//    return pow(resultado,0.5);
}
float distancia_minkowski(int col1,int col2,float t)
{
    float resultado=0.0;
    for(int i=0;i<8;i++)
    {
        resultado=resultado+=pow(fabs((matrix[i][col1]-matrix[i][col2])),t);
    }
    return pow(resultado,1.0/t);
	//return sqrt(resultado);

}

float similitud_coseno(int col1,int col2)
{
    float resultado_x=0.0, resultado_y=0.0, resultado_p=0.0, resultado=0.0;
    for(int i=0;i<8;i++)
    {
        resultado_p=resultado_p+=(matrix[i][col1]*matrix[i][col2]);
        resultado_x=resultado_x+=pow(matrix[i][col1],2.0);
        resultado_y=resultado_y+=pow(matrix[i][col2],2.0);
    }
    
    resultado=resultado_p/(pow(resultado_x,0.5)*(pow(resultado_y,0.5)));
    return resultado;

}
void load_matrix()
{
    ifstream input("data_movies.csv");
    string buffer;
    std::string::size_type sz;
	int i=0;
	int col=0;
	int fil=0;
    while(!input.eof())
    {
		if(col<24)
		{
			getline(input,buffer,',');
			if(buffer.size()!=0)
			{
				i = std::stoi(buffer);
				//cout<<"fil: "<<fil<<endl;
				//cout<<"col: "<<col<<endl;
				cout<<"matrix_m["<<fil<<"]["<<col<<"]:"<<i<<endl;

				matrix_m[fil][col]=i;
				col++;
			}
			else
			{
				matrix_m[fil][col]=0.0;
				col++;
			}
		}
		else
		{
			getline(input,buffer);
			col=0;
			fil++;
		}
    }
    
}

int main()
{
    
    //cout<<"Distancia Manhattan:\t"<<distancia_manhattan(0,1)<<endl;
    //cout<<"Distancia Euclidea:\t"<<distancia_euclidea(0,1)<<endl;
    //cout<<"Distancia Euclidea:\t"<<distancia_euclidea(4,7)<<endl;
    //cout<<"Distancia Euclidea:\t"<<distancia_euclidea(4,5)<<endl;
    //cout<<"Distancia Euclidea:\t"<<distancia_euclidea(0,1)<<endl;
    //cout<<"Distancia minkowski:\t"<<distancia_minkowski(0,1,1.0)<<endl;
    //cout<<"Similitud Coseno:\t"<<similitud_coseno(0,7)<<endl;
    load_matrix();
    return 0;
}
