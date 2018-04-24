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
        //b1.erase(0,1);
        //b1.erase(b1.size()-1,1);
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
        //u.erase(0,1);
        //u.erase(u.size()-1,1);
        if(!u.empty())
        {
            //cout<<line<<endl;
            getline(input,b,';');
            //b.erase(0,1);
            //b.erase(b.size()-1,1);
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
        cout<<it->first<<" size hash: "<<(it->second)->size()<<endl;
        auto it2=it->second->begin();
        while(it2!=it->second->end())
        {
            cout<<"  "<<it2->first<<","<<it2->second<<"    ";
            it2++;
        }
        cout<<endl;
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

float distancia_euclidea(string col1,string col2)
{
    float resultado=0.0;
    auto itc1=matrix_user.find(col1); 
    auto itc2=matrix_user.find(col2);    
    auto it_matrix_end=matrix_user.end();
    auto itf1=itc1->second->begin();
    while(itf1!=itc1->second->end() && itc1!=it_matrix_end && itc2!=it_matrix_end && itc1->second->begin()!=itc2->second->end())
    {
        auto itf2=itc2->second->find(itf1->first);
        if(itf1 != itc1->second->end() && itf2 != itc2->second->end())
        {
            cout<<"entro 1 if"<<endl;
            if(itf1->first==itf2->first)
            {
                cout<<itf2->second<<endl;
                resultado+=pow((itf1->second - itf2->second),2.0);
            }
            itf1++;
        }
        cout<<"no hay coincidencia"<<endl;
        itf1++;    
        
    }

    return sqrt(resultado);
    /*float resultado=0.0;
    auto itc1=matrix_user.find(col1)->second->begin();
    //auto itc2=matrix_user.find(col2)->second;
    while(itc1!=matrix_user.find(col1)->second->end())
    {
        auto itf=matrix_user.find(col2)->second->find(itc1->first);
        if(itf!=matrix_user.find(col2)->second->end())
        {
            //cout<<"vacioopoopooo"<<endl;
            if(itc1->first==itf->first)
            {
                resultado+=(pow((itc1->second - itf->second),2.0));
            }
        }
        itc1++;

    }
    return sqrt(resultado);*/
}

int main()
{
    load_hash_header();
    load_matrix();
    cout<<"Distancia Euclidea: "<<distancia_euclidea("Patrick C","Heather")<<endl;
    //load_matrix_fil();
    return 0;
}

