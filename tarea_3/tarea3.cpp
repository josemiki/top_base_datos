#include<iostream>
#include<fstream>
#include<string>
#include<unordered_map>
#include<algorithm>
#include<cstdio>
#include<cmath>

using namespace std;

#define fila_b unordered_map<string,float>
#define columna_u unordered_map<string,fila_b*>

#define fila_u unordered_map<string,float>
#define columna_b unordered_map<string,fila_u*>

#define users unordered_map<string,string>
#define books unordered_map<string,string>

#define myvec vector < MyStruct >

columna_u matrix_user;
columna_b matrix_book;

users hash_users;
books hash_books;

void load_hash_header()
{
    ifstream book("../../bd/BX-Books.csv");
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
    
    cout<<"load books \n size_books: "<<hash_books.size()<<endl;

    ifstream user("../../bd/BX-Users.csv");
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
    cout<<"load users \n size_users: "<<hash_users.size()<<endl;
    

}
void load_matrix()
{
    ifstream input("../../bd/BX-Book-Ratings.csv");
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
            //erase(r.size()-1,1);
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

    /*auto it=matrix_user.begin();
    
    while(it!=matrix_user.end())
    {
        cout<<it->first<<" size hash: "<<(it->second)->size()<<endl;
        auto it2=it->second->begin();
        while(it2!=it->second->end())
        {
            cout<<"   "<<it2->first<<" , "<<it2->second<<"    ";
            it2++;
        }
        cout<<endl;
        it++;
    }*/

    cout<<"load matriz users \n size_matrix_user: "<<matrix_user.size()<<endl;
    cout<<"load matriz books \n size_matrix_book: "<<matrix_book.size()<<endl;
}
float distancia_euclidea(string col1,string col2)
{
    float resultado=0.0;

    auto itc1=matrix_user.find(col1);

    //cout<<"itc1: "<<itc1->first<<endl;
    
    auto itc2=matrix_user.find(col2);

    //cout<<"itc2: "<<itc2->first<<endl;
    
    auto it_matrix_end=matrix_user.end();

    auto itf1=itc1->second->begin();

    

    while(itf1!=itc1->second->end() && itc1!=it_matrix_end && itc2!=it_matrix_end && itc1->second->begin()!=itc2->second->end())
    {
        //cout<<"primer while"<<endl;
        //auto itf1=itc2->second->find(itc1->first);
        

        //cout<<"itf"<<itf->first<<endl;

        auto itf2=itc2->second->find(itf1->first);

        if(itf1 != itc1->second->end() && itf2 != itc2->second->end())
        {
            cout<<"entro 1 if"<<endl;
            if(itf1->first==itf2->first)
            {
                cout<<itf2->second<<endl;
                resultado+=pow((itf1->second - itf2->second),2.0);
            }
            //itf1++;
        }
        cout<<"no hay coincidencia"<<endl;
        itf1++;    
        
    }

    return sqrt(resultado);
}

float correlacion_pearson(string col1, string col2)
{
    float sum_x_m_y=0.0;
    float sum_x=0.0;
    float sum_y=0.0;
    float sum_c_x=0.0;
    float sum_c_y=0.0;
    float resultado=0.0;

    int n=0;
    
    auto itc1=matrix_user.find(col1); 
    auto itc2=matrix_user.find(col2);    
    auto it_matrix_end=matrix_user.end();
    auto itf1=itc1->second->begin();

    while(itf1!=itc1->second->end() && itc1!=it_matrix_end && itc2!=it_matrix_end && itc1->second->begin()!=itc2->second->end())
    {
        auto itf2=itc2->second->find(itf1->first);

        if(itf1 != itc1->second->end() && itf2 != itc2->second->end())
        {
            //cout<<"entro 1 if"<<endl;
            if(itf1->first==itf2->first)
            {
                sum_x=sum_x+=itf1->second;
                sum_y=sum_y+=itf2->second; 
                sum_c_x=sum_c_x+=pow(itf1->second,2.0);
                sum_c_y=sum_c_y+=pow(itf2->second,2.0);
                sum_x_m_y=sum_x_m_y+=(itf1->second*itf2->second);
                n++;
                //cout<<itf2->second<<endl;
                //resultado+=pow((itf1->second - itf2->second),2.0);
            }
            
        }
        //cout<<"no hay coincidencia"<<endl;
        itf1++; 
    }
    

    resultado=(sum_x_m_y-((sum_x*sum_y)/n))/
    ((sqrt(sum_c_x-(pow(sum_x,2.0)/n)))*(sqrt(sum_c_y-(pow(sum_y,2.0)/n))));
    
    return resultado;
}
struct MyStruct
{
    string key;
    float euclidia;
    float pearson;
    float influencia;

    MyStruct(string k, float e,float p,float i) : key(k), euclidia(e), pearson(p),influencia(i) {}
};

struct less_than_key
{
    inline bool operator() (const MyStruct& struct1, const MyStruct& struct2)
    {
        return (struct1.euclidia > struct2.euclidia);
    }
};

myvec k_nn(string col,int k)
{
    myvec vec;
    auto itc1=matrix_user.find(col); 
    auto itc2=matrix_user.begin();    
    auto it_matrix_end=matrix_user.end();
    //auto itf1=itc1->second->begin();
    //auto itf2=itc2->second->begin();

    while(itc2!=it_matrix_end)
    {
        
        vec.push_back(MyStruct(itc2->first,correlacion_pearson(col,itc2->first),0.0,0.0));
        itc2++;
    }
    std::sort(vec.begin(), vec.end(), less_than_key());
    vec.erase(vec.begin());
    //for(int i=0;i<vec.size();i++)
    //    cout<<vec[i].key<<","<<vec[i].euclidia<<"."<<vec[i].pearson<<endl;
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
void calcular_influencia(string col, vector < MyStruct >& score)
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
float proyectado_knn(myvec & knn,string libro)
{
    int k= knn.size();
    float resultado=0.0;
    //float * puntaje=new float[k];
    for(int i=0;i<k;i++)
    {
        
        resultado+=knn[i].influencia*matrix_book.find(libro)->second->find(knn[i].key)->second;
        cout<<knn[i].influencia*matrix_book.find(libro)->second->find(knn[i].key)->second<<endl;

    }
    cout<<resultado;
    return resultado;
}
int main()
{
    load_hash_header();
    load_matrix();
    cout<<"distancia_euclidea: "<<distancia_euclidea("15600","15651");
    cout<<"distancia_euclidea: "<<correlacion_pearson("15600","15651");
    return 0;
}






















/*
//Reading without comillas 
#define fila unordered_map<string,float>
#define columna unordered_map<int,fila>

#define columnas unordered_map<int,float>
#define filas unordered_map<string,columnas>

#define users unordered_map<int,string>
#define books unordered_map<string,string>

columna matrix;
filas matrix_fil;
users hash_users;
books hash_books;

void load_headers()
{
    ifstream book("BX-Books.csv");
    string b1,b2;
    int line=1;
    while(!book.eof())
    {
        getline(book,b1,';');
        if(!b1.empty())
        {
            getline(book,b2);
            hash_books.insert({b1,b2});
            //cout<<"line: "<<line<<" col: "<<col<<" fil: "<<fil<<" rat: "<<rat<<endl;
            ++line;
        }
    }
    cout<<"size_books: "<<hash_books.size()<<endl;

    ifstream user("BX-Users.csv");
    line=1;
    int i=0;
    while(!user.eof())
    {
        getline(user,b1,';');
        if(!b1.empty())
        {
            //cout<<b1<<endl;
            i=stoi(b1);
            
            getline(user,b2);
            hash_users.insert({i,b2});
            
            //cout<<"inserto:"<<line<<endl;
            //cout<<"line: "<<line<<" col: "<<col<<" fil: "<<fil<<" rat: "<<rat<<endl;
            ++line;
            b2.clear();
            b1.clear();

        }
    }
    cout<<"size_users: "<<hash_users.size()<<endl;
    

}

void load_matrix_col()
{
    ifstream input("BX-Book-Ratings.csv");
    string word,fil;
    int col;
    float rat;
    int line=1;
    auto itcol=hash_users.begin();
    auto itfil=hash_books.begin();
    while(!input.eof())
    {
        getline(input,word,';');
        if(!word.empty())
        {
            col=stoi(word);
            word.clear();
            getline(input,fil,';');
            getline(input,word);
            rat=stof(word);
            fila f;
            f.insert({fil,rat});
            itcol=hash_users.find(col);
            itfil=hash_books.find(fil);
            if(itcol!=hash_users.end()&&itfil!=hash_books.end())
                matrix.insert({col,f});
            //cout<<"line: "<<line<<" col: "<<col<<" fil: "<<fil<<" rat: "<<rat<<endl;
            ++line;
        }
    }
    cout<<"size_matrix: "<<matrix.size()<<endl;

}

void load_matrix_fil()
{
    ifstream input("BX-Book-Ratings.csv");
    string word,fil;
    int col;
    float rat;
    int line=1;
    auto itcol=hash_users.begin();
    auto itfil=hash_books.begin();
    while(!input.eof())
    {
        getline(input,word,';');
        if(!word.empty())
        {
            col=stoi(word);
            word.clear();
            getline(input,fil,';');
            getline(input,word);
            rat=stof(word);
            columnas c;
            c.insert({col,rat});
            itcol=hash_users.find(col);
            itfil=hash_books.find(fil);
            if(itcol!=hash_users.end()&&itfil!=hash_books.end())
                matrix_fil.insert({fil,c});
            //cout<<"line: "<<line<<" col: "<<col<<" fil: "<<fil<<" rat: "<<rat<<endl;
            ++line;
        }
    }
    cout<<"size_matrix_fil: "<<matrix_fil.size()<<endl;

}
*/
