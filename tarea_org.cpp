#include<iostream>
#include<string>
#include<unordered_map>
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
        resultado=resultado+=(pow((matrix[i][col1]-matrix[i][col2]),2.0));
    }
    return pow(resultado,1.0/2.0);
}
float distancia_minkowski(int col1,int col2,float t)
{
    float resultado=0.0;
    for(int i=0;i<8;i++)
    {
        resultado=resultado+=pow(fabs((matrix[i][col1]-matrix[i][col2])),t);
    }
    return pow(resultado,1.0/t);

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

int main()
{
    
    cout<<"Distancia Manhattan:\t"<<distancia_manhattan(0,3)<<endl;
    cout<<"Distancia Euclidea:\t"<<distancia_euclidea(0,3)<<endl;
    cout<<"Distancia minkowski:\t"<<distancia_minkowski(0,3,1.0)<<endl;
    cout<<"Similitud Coseno:\t"<<similitud_coseno(4,7)<<endl;
    return 0;
}