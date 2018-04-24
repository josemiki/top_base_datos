#include<iostream>
#include<string>
#include<fstream>
#include<cstdio>
#include<unordered_map>
#include<cmath>
#include<vector>
#include<algorithm>
#include<utility>

using namespace std;

#define fila_b unordered_map<string,float>
#define columna_u unordered_map<string,fila_b*>

#define fila_u unordered_map<string,float>
#define columna_b unordered_map<string,fila_u*>

#define users unordered_map<string,string>
#define books unordered_map<string,string>

columna_u matrix_user;
columna_b matrix_book;

users hash_users;
books hash_books;


void load_hash_header()
{
    ifstream book("Movie_Movies.csv");
    string b1,b2;
    int line=1;
    while(!book.eof())
    {
        getline(book,b1,';');
        if(!b1.empty())
        {
            getline(book,b2);
            hash_books.insert({b1,b2});
            //cout<<"line: "<<line<<" book: "<<b1<<" all: "<<b2<<endl;
            ++line;
        }
    }
    cout<<"size_books: "<<hash_books.size()<<endl;

    ifstream user("Movie_Users.csv");
    line=1;
    //int i=0;
    while(!user.eof())
    {
        getline(user,b1,';');
        if(!b1.empty())
        {            
            getline(user,b2);
            hash_users.insert({b1,b2});
            //cout<<"line: "<<line<<" user: "<<b1<<" all: "<<b2<<endl;
            ++line;
        }
    }
    cout<<"size_users: "<<hash_users.size()<<endl;
/*
    auto it=hash_users.begin();

    while(it!=hash_users.end())
    {
        cout<<it->first<<"size inner hash: "<<(it->second).size()<<endl;
        it++;
    }
*/
}
void load_matrix()
{
    ifstream input("Movie_Ratings.csv");
    string u,b,r;
    
    float rat;
    int line=1;
    auto itcol=hash_users.begin();
    auto itfil=hash_books.begin();
    while(!input.eof())
    {
        getline(input,u,';');
        if(!u.empty())
        {
            //cout<<line<<endl;
            getline(input,b,';');
            getline(input,r);
            //cout<<"line: "<<line<<" user: "<<u<<" book: "<<b<<" rat: "<<r.size()<<endl;
            //r.erase(0,1);
            //r.erase(r.size()-1,1);
            //cout<<"line: "<<line<<" user: "<<u<<" book: "<<b<<" rat: "<<r<<endl;
            rat=stof(r);
            
            //fila_b fb;
            //fb.insert({b,rat});

            //fila_u fu;
            //fu.insert({u,rat});
            
            itcol=hash_users.find(u);
            itfil=hash_books.find(b);

            if(itcol!=hash_users.end()&&itfil!=hash_books.end())
            {
                auto it_f_b=matrix_user.find(u);
                auto it_f_u=matrix_book.find(b);
                if(it_f_b!=matrix_user.end())
                {
                    //cout<<"entro if"<<endl;
                    //cout<<"it_f_b: "<<it_f_b->first<<" , "<<it_f_b->second->size()<<endl;
                    it_f_b->second->insert({b,rat});
                    //cout<<"salio if"<<endl;
                }
                else
                {
                    //cout<<"entro else"<<endl;
                    fila_b* fb=new fila_b();
                    fb->insert({b,rat});
                    matrix_user.insert({u,fb});
                    //cout<<"salio else"<<endl;
                }
                if(it_f_u!=matrix_book.end())
                {
                    //cout<<"entro if"<<endl;
                    //cout<<"it_f_b: "<<it_f_b->first<<" , "<<it_f_b->second->size()<<endl;
                    it_f_u->second->insert({u,rat});
                    //cout<<"salio if"<<endl;
                }
                else
                {
                    //cout<<"entro else"<<endl;
                    fila_u* fu=new fila_u();
                    fu->insert({u,rat});
                    matrix_book.insert({b,fu});
                    //cout<<"salio else"<<endl;
                }
                //matrix_book.insert({b,fu});
            }
            //cout<<"line: "<<line<<" user: "<<u<<" book: "<<b<<" rat: "<<rat<<endl;
            ++line;
        }
    }
    cout<<"size_matrix_user: "<<matrix_user.size()<<endl;
    /*auto it=matrix_user.begin();
    
    while(it!=matrix_user.end())
    {
        cout<<it->first<<"size inner hash: "<<(it->second)->size()<<endl;
        it++;
    }
    */

    cout<<"size_matrix_book: "<<matrix_book.size()<<endl;
    /*it=matrix_book.begin();
    
    while(it!=matrix_book.end())
    {
        cout<<it->first<<"size inner hash: "<<(it->second)->size()<<endl;
        it++;
    }  
    */

}
float distancia_euclidea(string col1,string  col2)
{
    float resultado=0.0;
    for(int i=0;i<size_m;i++)
    {
	if((matrix[i][col1]!=INF&&matrix[i][col2]!=INF))
	    resultado=resultado+=(pow((matrix[i][col1]-matrix[i][col2]),2.0));
    }
    return sqrt(resultado);
}
/*
float distancia_manhattan(int col1,int col2)
{
    float resultado=0.0;
    for(int i=0;i<size_m;i++)
    {
        resultado=resultado+=(fabs(matrix[i][col1]-matrix[i][col2]));
    }
    return resultado;
}


*/
int main()
{
    load_hash_header();
    load_matrix();
    //load_matrix_fil();
    return 0;
}


/*
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
	if((matrix[i][col1]!=INF&&matrix[i][col2]!=INF))
	    resultado=resultado+=(pow((matrix[i][col1]-matrix[i][col2]),2.0));
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
    for(int i=0;i<size_m;i++)
    {
        for(int j=0;j<size_m;j++)
        {
            cout<<matrix[i][j]<<",";
        }
        cout<<endl;
    }
    
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
    //cout<<"vec_size"<<vec.size()<<endl;
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
    load_matrix("data_movies.csv");
    //cout<<"Distancia Manhattan:\t"<<distancia_manhattan(0,1)<<endl;
    //cout<<"Distancia Euclidea:\t"<<distancia_euclidea(0,1)<<endl;
    //cout<<"Distancia Euclidea:\t"<<distancia_euclidea(4,7)<<endl;
    //cout<<"Correlacion de Pearson:\t"<<correlacion_pearson(6,8)<<endl;
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
*/