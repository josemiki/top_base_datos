#include<iostream>
#include<string>
#include<fstream>
#include<cstdio>
#include<unordered_map>
#include<cmath>
#include<vector>
#include<algorithm>

using namespace std;

#define INF 0.0
#define size_m 25
#define hash unordered_map<string,int> 
#define myvec vector < MyStruct >
hash nombres;
hash libros;

void load_hash()
{
    ifstream dataset("Movie_Ratings.csv");
    ifstream lib("libros.txt");
    string buffer;
    getline(dataset,buffer,',');
    int i=0;
    while(1)
    {
        if(i<24)
        {
            getline(dataset,buffer,',');
            nombres.insert({buffer,i});
        }
        getline(dataset,buffer);
        nombres.insert({buffer,i});
        break;
    }
    while(!lib.eof())
    {
        getline(lib,buffer);
        if(!buffer.empty())
            libros.insert({buffer,i});
    }
}
float matrix[size_m][size_m];

float distancia_manhattan(int col1,int col2)
{
    float resultado=0.0;
    for(int i=0;i<size_m;i++)
    {
        resultado=resultado+=(fabs(matrix[i][col1]-matrix[i][col2]));
    }
    return resultado;
}

float distancia_euclidea(int col1,int col2)
{
    float resultado=0.0;
    for(int i=0;i<size_m;i++)
    {
	    if((matrix[i][col1]!=0.0 && matrix[i][col2]!=0.0))
	    {
	        //cout<<"col1: "<<matrix[i][col1]<<" col2: "<<matrix[i][col2]<<" res: "<<resultado<<endl;
	        resultado+=(pow((matrix[i][col1]-matrix[i][col2]),2.0));
	    }
    }
    return sqrt(resultado);
}
float distancia_minkowski(int col1,int col2,float t)
{
    float resultado=0.0;
    for(int i=0;i<size_m;i++)
    {
        resultado=resultado+=pow(fabs((matrix[i][col1]-matrix[i][col2])),t);
    }
    return pow(resultado,1.0/t);
	//return sqrt(resultado);

}

float similitud_coseno(int col1,int col2)
{
    float resultado_x=0.0, resultado_y=0.0, resultado_p=0.0, resultado=0.0;
    for(int i=0;i<size_m;i++)
    {
        resultado_p=resultado_p+=(matrix[i][col1]*matrix[i][col2]);
        resultado_x=resultado_x+=pow(matrix[i][col1],2.0);
        resultado_y=resultado_y+=pow(matrix[i][col2],2.0);
    }
    
    resultado=resultado_p/(pow(resultado_x,0.5)*(pow(resultado_y,0.5)));
    return resultado;

}
void load_matrix(string file)
{
    ifstream input(file);
    string buffer;
	float i=0.0;
	int col=0;
	int fil=0;
    while(!input.eof())
    {
		if(col<24)
		{
			getline(input,buffer,',');
			if(!buffer.empty())
			{
				i = std::stof(buffer);
				//cout<<"fil: "<<fil<<endl;
				//cout<<"col: "<<col<<endl;
				//cout<<"matrix["<<fil<<"]["<<col<<"]:"<<i<<endl;
                
				matrix[fil][col]=i;
                i=0.0;
				col++;
                buffer.clear();
			}
			else
			{
                //cout<<"matrix["<<fil<<"]["<<col<<"]:"<<i<<endl;
				matrix[fil][col]=INF;
				col++;
                buffer.clear();
			}
		}
		else
		{
			getline(input,buffer);
            if(!buffer.empty())
			{
				i = std::stof(buffer);
				//cout<<"fil: "<<fil<<endl;
				//cout<<"col: "<<col<<endl;
				//cout<<"matrix["<<fil<<"]["<<col<<"]:"<<i<<endl;
                
				matrix[fil][col]=i;
                i=0.0;
				col++;
                buffer.clear();
			}
			else
			{
                //cout<<"matrix["<<fil<<"]["<<col<<"]:"<<i<<endl;
				matrix[fil][col]=INF;
				col++;
                buffer.clear();
			}
            col=0;
			fil++;
            buffer.clear();
		}
    }
    /*
    for(int i=0;i<size_m;i++)
    {
        for(int j=0;j<size_m;j++)
        {
            cout<<matrix[i][j]<<",";
        }
        cout<<endl;
    }*/
    
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
    vec.erase(vec.begin());
    //for(int i=0;i<25;i++)
      //  cout<<vec[i].key<<","<<vec[i].euclidia<<"."<<vec[i].pearson<<endl;
    //cout<<"ordenado"<<endl;
    //cout<<"vec_size"<<vec.size()<<endl;
    /*int fin=(vec.size()-k);

    for(int i=0;i<fin;i++)
        vec.pop_back();
    //cout<<"vec_size"<<vec.size()<<endl;*/
    cout<<"fin:\t"<<vec.size()-k<<endl;
    int fin=(vec.size()-k);
    for(int i=0;i<fin;i++)
        vec.pop_back();
    
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

        resultado+=knn[i].influencia*matrix[libro][(knn[i].key)];
        cout<<knn[i].influencia*matrix[libro][(knn[i].key)]<<endl;

    }
    cout<<resultado;
    return resultado;
}
int main()
{
    //load_hash();
    load_matrix("../data/data_movies.csv");
    //cout<<"Distancia Manhattan:\t"<<distancia_manhattan(0,1)<<endl;
    cout<<"Distancia Euclidea:\t"<<distancia_euclidea(0,1)<<endl;
    cout<<"Distancia Euclidea:\t"<<distancia_euclidea(4,7)<<endl;
    cout<<"Correlacion de Pearson:\t"<<correlacion_pearson(6,8)<<endl;
    //cout<<"Correlacion de Pearson:\t"<<correlacion_pearson(nombres.find("Patrick C")->second,14)<<endl;
    //cout<<"Correlacion de Pearson:\t"<<correlacion_pearson(nombres.find("Patrick C")->second,3)<<endl;
    //cout<<"Correlacion de Pearson:\t"<<correlacion_pearson(nombres.find("Patrick C")->second,20)<<endl;
    //cout<<"Distancia Euclidea:\t"<<distancia_euclidea(4,5)<<endl;
    //cout<<"Distancia Euclidea:\t"<<distancia_euclidea(0,1)<<endl;
    //cout<<"Distancia minkowski:\t"<<distancia_minkowski(0,1,1.0)<<endl;
    //cout<<"Similitud Coseno:\t"<<similitud_coseno(0,7)<<endl;
    //myvec knn=k_nn(nombres.find("Patrick C")->second,3);
    myvec knn=k_nn(4,2);
    //calcular_influencia(nombres.find("Patrick C")->second,knn);
 
    calcular_influencia(4,knn);
    for(int i=0;i<knn.size();i++)
    {
            cout<<knn[i].key<<" ; "<<knn[i].euclidia<<" ; "<<knn[i].pearson<<" ; "<<knn[i].influencia;

        cout<<endl;
    }
    //cout<<"proyeccion:\t"<<proyectado_knn(knn,libros.find("Avatar")->second)<<endl;
    cout<<"proyeccion:\t"<<proyectado_knn(knn,9)<<endl;

    return 0;
}
