#include<iostream>
#include<string>
#include<fstream>
#include<cstdio>
#include<unordered_map>
#include<cmath>
#include<vector>
#include<algorithm>

using namespace std;

#define myvec vector < MyStruct >
#define size_m 8


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
float correlacion_pearson(int col1, int col2)
{
    float sum_x_m_y=0.0;
    float sum_x=0.0;
    float sum_y=0.0;
    float sum_c_x=0.0;
    float sum_c_y=0.0;
    int n=0;
    for(int i=0;i<size_m;i++)
    {

           
        if(matrix[i][col1]!=0.0&&matrix[i][col2]!=0.0)
        {
            
           sum_x=sum_x+=matrix[i][col1];
           sum_y=sum_y+=matrix[i][col2]; 
           sum_c_x=sum_c_x+=pow(matrix[i][col1],2.0);
           sum_c_y=sum_c_y+=pow(matrix[i][col2],2.0);
           sum_x_m_y=sum_x_m_y+=(matrix[i][col1]*matrix[i][col2]);
           n++;
           
        }
    }
    
    //cout<<"sum_x:\t"<<sum_x<<endl;
    //cout<<"sum_y:\t"<<sum_y<<endl;
    //cout<<"sum_x_m_y:\t"<<sum_x_m_y<<endl;
    //cout<<"sum_c_x:\t"<<sum_c_x<<endl;
    //cout<<"sum_c_y:\t"<<sum_c_y<<endl;

    float resultado=(sum_x_m_y-((sum_x*sum_y)/n))/
    ((sqrt(sum_c_x-(pow(sum_x,2.0)/n)))*(sqrt(sum_c_y-(pow(sum_y,2.0)/n))));
    
    return resultado;
}
struct MyStruct
{
    int key;
    float euclidia;
    float pearson;
    float influencia;

    MyStruct(int k, float e,float p,float i) : key(k), euclidia(e), pearson(p),influencia(i) {}
};

struct less_than_key
{
    inline bool operator() (const MyStruct& struct1, const MyStruct& struct2)
    {
        return (struct1.euclidia > struct2.euclidia);
    }
};
myvec k_nn(int col,int k)
{
    myvec vec;
    for(int i =0;i<size_m;i++)
    {
        vec.push_back(MyStruct(i,correlacion_pearson(col,i),0.0,0.0)); 
    }
    std::sort(vec.begin(), vec.end(), less_than_key());
    
    //for(int i=0;i<25;i++)
    //    cout<<vec[i].key<<","<<vec[i].euclidia<<"."<<vec[i].pearson<<endl;
    int fin=(vec.size()-k);
    for(int i=0;i<fin;i++)
        vec.pop_back();
    //cout<<"vec_size"<<vec.size()<<endl;
    return vec;

}
void calcular_influencia(int col, vector < MyStruct >& score)
{
    float suma_pearson=0.0;
    for(int i=0;i<score.size();i++)
    {
        score[i].pearson=correlacion_pearson(col,score[i].key);
        // cout<<suma_pearson<<endl;
        suma_pearson+=score[i].pearson;
    }
    //cout<<suma_pearson<<endl;
    for(int i=0;i<score.size();i++)
    {
        //score[i].influencia=score[i].pearson/suma_pearson*100;
        score[i].influencia=score[i].pearson/suma_pearson;
    }

}

float proyectado_knn(myvec & knn,int libro)
{
    int k= knn.size();
    float resultado=0.0;
    //float * puntaje=new float[k];
    for(int i=0;i<k;i++)
    {
        resultado+=resultado+knn[i].influencia*matrix[libro][(knn[i].key)];
    }
    return resultado;
}
int main()
{
    cout<<"Correlacion de Pearson:\t"<<correlacion_pearson(0,1)<<endl;

    cout<<"Correlacion de Pearson:\t"<<correlacion_pearson(0,4)<<endl;
    cout<<"Correlacion de Pearson:\t"<<correlacion_pearson(0,5)<<endl;
    /*myvec knn=k_nn(5,2);
    calcular_influencia(5,knn);
    for(int i=0;i<knn.size();i++)
    {
            cout<<knn[i].key<<" ; "<<knn[i].euclidia<<" ; "<<knn[i].pearson<<" ; "<<knn[i].influencia;

        cout<<endl;
    }
    cout<<"proyeccion:\t"<<proyectado_knn(knn,1)<<endl;*/
    return 0;
}