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

columna_u matrix_user;
columna_b matrix_book;

users hash_users;
books hash_books;

void load_hash_header()
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
            //cout<<"line: "<<line<<" book: "<<b1<<" all: "<<b2<<endl;
            ++line;
        }
    }
    cout<<"size_books: "<<hash_books.size()<<endl;

    ifstream user("BX-Users.csv");
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
    

}
void load_matrix()
{
    ifstream input("BX-Book-Ratings.csv");
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
            r.erase(0,1);
            r.erase(r.size()-1,1);
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
        /*getline(input,u,';');
        if(!u.empty())
        {
            //cout<<line<<endl;
            getline(input,b,';');
            getline(input,r);
            //cout<<"line: "<<line<<" user: "<<u<<" book: "<<b<<" rat: "<<r.size()<<endl;
            r.erase(0,1);
            r.erase(r.size()-1,1);
            //cout<<"line: "<<line<<" user: "<<u<<" book: "<<b<<" rat: "<<r<<endl;
            rat=stof(r);
            
            fila_b fb;
            fb.insert({b,rat});

            fila_u fu;
            fu.insert({u,rat});
            
            itcol=hash_users.find(u);
            itfil=hash_books.find(b);

            if(itcol!=hash_users.end()&&itfil!=hash_books.end())
            {
                matrix_user.insert({u,fb});
                matrix_book.insert({b,fu});
            }
            //cout<<"line: "<<line<<" user: "<<u<<" book: "<<b<<" rat: "<<rat<<endl;
            ++line;
        }*/
    }
    cout<<"size_matrix_user: "<<matrix_user.size()<<endl;
    cout<<"size_matrix_book: "<<matrix_book.size()<<endl;
}

int main()
{
    load_hash_header();
    load_matrix();
    //load_matrix_fil();
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
