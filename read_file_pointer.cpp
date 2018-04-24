#include<iostream>
#include<string>
#include<fstream>
#include<cstdio>
#include<cmath>
#include<unordered_map>

using namespace std;

#define INF 0.0
#define fila std::unordered_map<string,float> 
#define columna std::unordered_map<int,fila> 

//Declaracion de variables Globales
//fila  hash_users;
string buffer;
int s_users;
int s_books;
float no = 9999.99;
columna matrix;
//

/*void load_users()
{
    ifstream users("BX-Users.csv");
    unordered_map<string,int> hash_users;
    int i=0;
    buffer.clear();
    while(!users.eof())
    {
        getline(users,buffer,';');
        if(!buffer.empty())
        {
            hash_users.insert({buffer,std::stoi(buffer)});
            i++;
        }   
        getline(users,buffer);
    }
    s_users=hash_users.size();
    cout<<"size of hash_users:\t"<<hash_users.size()<<endl;
}
void load_books()
{
    ifstream books("BX-Books.csv");
    int i=0;
    unordered_map<string,int> hash_books;
    while(!books.eof())
    {
        getline(books,buffer,';');
        if(!buffer.empty())
        {
            hash_books.insert({buffer,i});
            i++;
        }   
        getline(books,buffer);
    }
    cout<<"size of hash_books:\t"<<hash_books.size()<<endl;
}*/
void load_matrix_users()
{
    ifstream ratings("../BX-Book-Ratings.csv");
    string row,col,rating;

    int line=1;
    int c=0;
    float ra=0.0;

    while(!ratings.eof())
    {
        getline(ratings,col,';');
        if(!col.empty())
        {
            
            c=stoi(col);
            getline(ratings,row,';');
            
            getline(ratings,rating);
            ra=stof(rating);

            if(rating.size()==0)
            {
                ra=no;
            }
            //cout<<"Line: "<<line<<" insert: "<<c<<" r: "<<row<<" rating: "<<ra<<endl;

            fila f;
            f.insert({row,ra});
            matrix.insert({c,f});
            line++;
        }
    }
}

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
int main()
{
    
    return 0;
}