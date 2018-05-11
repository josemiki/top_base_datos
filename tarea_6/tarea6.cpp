#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<unordered_map>
#include<algorithm>
#include<cstdio>
#include<cmath>
#include<iterator>

using namespace std;

#define fila_b unordered_map<string,float>
#define columna_u unordered_map<string,fila_b*>

#define fila_u unordered_map<string,float>
#define columna_b unordered_map<string,fila_u*>

#define vec_atrib vector<string>
#define users unordered_map<string,vec_atrib*>
#define books unordered_map<string,vec_atrib*>

#define myvec vector < NewDesv >
#define myhash unordered_map <string , NewDesv >

columna_u matrix_user;
columna_b matrix_book;

users hash_users;
books hash_books;



struct NewDesv
{
    string book;
    float desv;
    int cardinalidad;
    float opcional;

    NewDesv(string b, float r,int n,float o) : book(b), desv(r), cardinalidad(n),opcional(o) {}
};
struct less_distance
{
    inline bool operator() (const NewDesv& struct1, const NewDesv& struct2)
    {
        return (struct1.desv < struct2.desv);
    }
};
myhash list_desv;
void load_hash_header()
{
    ifstream book("../../ml-latest-small/movies.csv");
    string b1,b2,b3;
    int line=1;
    while(!book.eof())
    {
        getline(book,b1,';');
        if(!b1.empty())
        {
            getline(book,b2,';');
            getline(book,b3);
            vec_atrib* new_v = new vec_atrib();
            //new_v->insert.push_back(b2);
            //new_v->insert.push_back(b3);
            hash_books.insert({b1,new_v});
            //cout<<"line: "<<line<<" book: "<<b1<<" all: "<<b2<<endl;
            ++line;
        }
    }
    
    cout<<"load books \n size_books: "<<hash_books.size()<<endl;

}
void load_matrix_file()
{
 ifstream input("../../ml-latest-small/ratings.csv");
    string u,b,r;
    
    float rat=0.0;
    int line=1;
    while(!input.eof())
    {
        getline(input,u,';');
        if(!u.empty())
        {
            getline(input,b,';');
            getline(input,r);
            rat=stof(r);         
                auto it_f_b=matrix_user.find(u);
                auto it_f_u=matrix_book.find(b);
                if(it_f_b!=matrix_user.end())
                {
                    it_f_b->second->insert({b,rat});
                }
                else
                {
                    fila_b* fb=new fila_b();
                    fb->insert({b,rat});
                    matrix_user.insert({u,fb});
                }
                if(it_f_u!=matrix_book.end())
                {
                    it_f_u->second->insert({u,rat});
                }
                else
                {
                    fila_u* fu=new fila_u();
                    fu->insert({u,rat});
                    matrix_book.insert({b,fu});
                }
            ++line;
        }

    }

    

    cout<<"load matriz users \n size_matrix_user: "<<matrix_user.size()<<endl;
    cout<<"load matriz books \n size_matrix_book: "<<matrix_book.size()<<endl;

}

void print_matrix()
{
    auto it=matrix_user.begin();
    int size_hash_y=0;
    while(it!=matrix_user.end())
    {
        auto it2=it->second->begin();
        while(it2!=it->second->end())
        {
            cout<<"["<<it->first<<"  ,  "<<it2->first<<"  ,  "<<it2->second<<"]";
            size_hash_y++;
            it2++;
        }
        cout<<endl;
        it++;
    }
    cout<<"size_hash:\t"<<size_hash_y<<endl;
}


pair<float,int> desv(string col1,string col2)
{
    //cout<<"books a evaluar: "<<col1<<" y "<<col2<<endl;
    float resultado=0.0;
    vector<float> vec_tmp;
    auto itc1=matrix_book.find(col1); 
    auto itc2=matrix_book.find(col2);    
    auto it_matrix_end=matrix_book.end();
    auto itf1=itc1->second->begin();

    float a=0.0,b=0.0;
    int c=0;

    while(itf1!=itc1->second->end() && itc1!=it_matrix_end && itc2!=it_matrix_end && itc1->second->begin()!=itc2->second->end())
    {
        auto itf2=itc2->second->find(itf1->first);
        if(itf1 != itc1->second->end() && itf2 != itc2->second->end())
        {
            if(itf1->first==itf2->first)
            {
                vec_tmp.push_back(itf1->second-itf2->second);
                c++;
            }
        }
        itf1++;         
    }
    for(int i=0;i<vec_tmp.size();i++)
        resultado+=(vec_tmp[i]/float(c));
   
    if(isnan(resultado))
        return make_pair(0.0,c);
    
    else
    {
        //cout<<"Resultado: "<<resultado<<endl;
        return make_pair(resultado,c);
    }
} 
void calcular_desviacion(string user,string book)
{
    auto it_m_user=matrix_user.find(user);
    auto it_book_per_user=it_m_user->second->begin();
    float sum=0.0;
    float sum_card=0.0;

    while(it_book_per_user!=it_m_user->second->end())
    {
        auto p=desv(book,it_book_per_user->first);
        list_desv.insert({it_book_per_user->first,NewDesv(it_book_per_user->first,p.first,p.second,it_book_per_user->second)});
        sum+=((p.first+it_book_per_user->second)*p.second);
        sum_card+=p.second;
        it_book_per_user++;
    }
    cout<<"Resultado: "<<sum/sum_card<<endl;

}
void predecir_sw1(string user,string book)
{
    calcular_desviacion(user,book); 
    //cout<<"size hash: "<<list_desv.size()<<endl;
    
    
    //for(auto it = list_desv.begin();it!=list_desv.end();it++)
    //    cout<<"movie: "<<it->second.book<<" desv: "<<it->second.desv<<" card: "<<it->second.cardinalidad<<" rating: "<<it->second.opcional<<endl;
}
int main()
{

    load_matrix_file();
   
    predecir_sw1("478","67255");
    //predecir("470","3007");
    //cout<<"similitud entre "<<similitud_books("1293","593")<<endl;;
    return 0;
}



