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

#define list_average unordered_map<string,float>

#define myvec vector < Normalizado >
#define myhash unordered_map <string , Normalizado >

columna_u matrix_user;
columna_b matrix_book;

users hash_users;
books hash_books;

list_average hash_similitud;

list_average hash_avg;




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

    /*ifstream user("../../bd/BX-Users.csv");
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
    */

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
void calc_average()
{
    auto itc=matrix_user.begin();
    //auto itmb=matrix_book.begin();
    int n=0;
    float avg=0.0;
    //fila_u* fu=new fila_u();
    //fu->insert({u,rat});
    //matrix_book.insert({"average",fu});
    while(itc!=matrix_user.end())
    {
        auto itf=itc->second->begin();
        while(itf!=itc->second->end())
        {
            avg+=itf->second;
            n++;
            itf++;
        }
        avg=(avg/float(n));
        cout<<"User: "<<itc->first<<" Avg: "<<avg<<endl;
        hash_avg.insert({itc->first,avg});
        //matrix_book.find("average")->second->insert({itc->first,avg});
        //itc->second->insert({"average",avg});
        n=0;
        avg=0.0;
        itc++;
    }
    cout<<"size average"<<hash_avg.size()<<endl;
}

float similitud_books(string col1, string col2)
{
    //cout<<"books a evaluar: "<<col1<<" y "<<col2<<endl;
    float resultado=0.0;
    float numerador=0.0;
    float denominador=0.0;
    auto itc1=matrix_book.find(col1); 
    auto itc2=matrix_book.find(col2);    
    auto it_matrix_end=matrix_book.end();
    auto itf1=itc1->second->begin();

    float a=0.0,b=0.0;

    while(itf1!=itc1->second->end() && itc1!=it_matrix_end && itc2!=it_matrix_end && itc1->second->begin()!=itc2->second->end())
    {
        auto itf2=itc2->second->find(itf1->first);
        if(itf1 != itc1->second->end() && itf2 != itc2->second->end())
        {
            if(itf1->first==itf2->first)
            {
                cout<<"User1: "<<itf1->first<<"  Valu1: "<<itf1->second<<"  Valu2: "<<itf2->second<<"  Avg: "<<hash_avg.find(itf1->first)->second<<endl;
                numerador+=((itf1->second-hash_avg.find(itf1->first)->second)*(itf2->second-hash_avg.find(itf2->first)->second));
                a+=powf((hash_avg.find(itf1->first)->second-itf1->second),2.0);
                b+=powf((hash_avg.find(itf2->first)->second-itf2->second),2.0);
                //numerador+=((hash_avg.find(itf1->first)->second-itf1->second)*(hash_avg.find(itf2->first)->second-itf2->second));
                //a+=powf((hash_avg.find(itf1->first)->second-itf1->second),2.0);
                //b+=powf((hash_avg.find(itf2->first)->second-itf2->second),2.0);
            }
        }
        itf1++;         
    }
    
    denominador=(sqrtf(a)*sqrtf(b));
    //cout<<"Numerador: "<<numerador<<" Denominador: "<<denominador<<endl;
    resultado=numerador/denominador;
    if(isnan(resultado))
        return 0;
    
    else
    {
        cout<<"Resultado: "<<resultado<<endl;
        return resultado;
    }
}
void calcular_matrix_similitud(string book,string user)
{
    auto it_user=matrix_user.find(user)->second;
    auto book_per_user=it_user->begin();
    while(book_per_user!=it_user->end())
    {
        //cout<<"similitud books: "<<similitud_books(book,book_per_user->first)<<endl;
        hash_similitud.insert({book_per_user->first,similitud_books(book,book_per_user->first)});
        book_per_user++;
    }
    cout<<"size col matrix similitud: "<<hash_similitud.size()<<endl;
    /*while(itc!=it_matrix_end)
    {
        itf1=itc->second->begin();
        cout<<"Evaluando movie: "<<itf1->first<<endl;

        auto itf2 = matrix_book.begin();
        while(itf2!=it_matrix_end && itf2->first!="average" && itc->first!="average")
        {
            auto itm1=matrix_similitud.find(itf1->first);
            auto itm2=matrix_similitud.find(itf2->first);
            float sb=similitud_books(itf1->first,itf2->first);

            if(itm1!=matrix_similitud.end())
            {
                cout<<"Insertando b1:  "<<itf1->first<<" b2:  "<<itf2->first<<endl;
                //float sb=similitud_books(itf1->first,itf2->first);
                itm1->second->insert({itf2->first,sb});
            {
            }
            if(itm2!=matrix_similitud.end())
            {
                cout<<"Insertando b2:  "<<itf2->first<<" b1:  "<<itf1->first<<endl;
                //float sb=similitud_books(itf1->first,itf2->first);
                itm2->second->insert({itf1->first,sb});
            }
            else
                //float sb=similitud_books(itf1->first,itf2->first);
                cout<<"Insertando NUEVO b1:  "<<itf1->first<<" b2:  "<<itf2->first<<endl;
                fila_b * fb=new fila_b();
                fb->insert({itf2->first,sb});
                matrix_similitud.insert({itf1->first,fb});
                
                fila_b * bf=new fila_b();
                bf->insert({itf1->first,sb});
                matrix_similitud.insert({itf2->first,bf});
            }
            itf2++;
        }
        //itf1++;
        itc++;
    }
    cout<<"size col matrix similitud: "<<matrix_similitud.size()<<endl;
    //auto itc = matrix_book.begin();
    auto it_matrix_end = matrix_book.end();
    float sb;
    //#pragma omp parallel for
    for(auto itf1 = matrix_book.begin();itf1!=it_matrix_end;itf1++)
    {
        auto itf2 = itf1;
        itf2++;
        
        for(;itf2!=it_matrix_end;itf2++)
        {
            sb=similitud_books(itf1->first,itf2->first);
            auto itmb1=matrix_similitud.find(itf1->first);    
            auto itmb2=matrix_similitud.find(itf2->first);    
            if(itmb1!=matrix_similitud.end())
            {
                cout<<"Insertando b1:  "<<itf1->first<<" b2:  "<<itf2->first<<endl;
                itmb1->second->insert({itf2->first,sb});
            }
            else
            {
                cout<<"Creando NUEVO b1:  "<<itf1->first<<" b2:  "<<itf2->first<<endl;
                fila_b * fb=new fila_b();
                fb->insert({itf2->first,sb});
                matrix_similitud.insert({itf1->first,fb});
                
                if(itmb2!=matrix_similitud.end())
                {
                    cout<<"Insertando b2:  "<<itf2->first<<" b1:  "<<itf1->first<<endl;
                    //float sb=similitud_books(itf1->first,itf2->first);
                    itmb2->second->insert({itf1->first,sb});
                }
                else
                {
                    cout<<"Creando NUEVO b2:  "<<itf1->first<<" b1:  "<<itf2->first<<endl;
                    fila_b * bf=new fila_b();
                    bf->insert({itf1->first,sb});
                    matrix_similitud.insert({itf2->first,bf});
                }
            }
        }
    }
    cout<<"size col matrix similitud: "<<matrix_similitud.size()<<endl;
    
    */
}

struct Normalizado
{
    string book;
    float real;
    float normalizado;
    float opcional;

    Normalizado(string b, float r,float n,float o) : book(b), real(r), normalizado(n),opcional(o) {}
};
struct less_distance
{
    inline bool operator() (const Normalizado& struct1, const Normalizado& struct2)
    {
        return (struct1.normalizado < struct2.normalizado);
    }
};

struct higher_distance
{
    inline bool operator() (const Normalizado& struct1, const Normalizado& struct2)
    {
        return (struct1.normalizado > struct2.normalizado);
    }
};

myvec normalizar(string user,float &a,float &b)
{
    myvec vec;
    auto it_mat_user=matrix_user.find(user)->second->begin();
    while(it_mat_user!=matrix_user.find(user)->second->end())
    {
        vec.push_back(Normalizado(it_mat_user->first,it_mat_user->second,it_mat_user->second,0.0));
        it_mat_user++;
    }
    std::sort(vec.begin(), vec.end(), less_distance());
    /*for(auto it = vec.begin();it<vec.end();it++)
        cout<<it->normalizado<<endl;
*/
    float min=vec[0].normalizado;
    int fin = vec.size()-1;
    float max=vec[fin].normalizado;

    a=min;
    b=max;

    for(int i=0;i<vec.size();i++)
    {
        vec[i].normalizado=((2*(vec[i].real-min))-(max-min))/(max-min);
    }

    std::sort(vec.begin(), vec.end(), higher_distance());
    for(auto it = vec.begin();it<vec.end();it++)
        cout<<"movie: "<<it->book<<" real: "<<it->real<<" normalizado: "<<it->normalizado<<endl;

    return vec;
}

void predecir_coseno(string user,string book)
{
    calc_average();
    calcular_matrix_similitud(book,user);
    float min=0.0;
    float max=0.0;
    myvec vec=normalizar(user,min,max);


    myhash vec2;
    for(int i=0;i<vec.size();i++)
        vec2.insert({vec[i].book,vec[i]});

    float numerador=0.0;
    float denominador=0.0;

    auto it_similitud=hash_similitud.begin();
    while(it_similitud!=hash_similitud.end())
    {
        auto it_norma=vec2.find(it_similitud->first);
        cout<<"similitud: "<<it_similitud->first<<"   "<<it_similitud->second<<endl;
        numerador+=(it_similitud->second*it_norma->second.normalizado);
        denominador+=fabs(it_similitud->second);
        it_similitud++;    
    }
    float prediccion=numerador/float(denominador);
    cout<<"Prrediccion NOrmalizado: "<<prediccion<<endl;
    prediccion=((0.5*(prediccion+1))*(max-min))+min;
    cout<<"Prrediccion Real: "<<prediccion<<endl;

}

int main()
{

    load_matrix_file();
   
    predecir_coseno("1","39");
    //predecir_sw1("478","67255");
    //predecir("470","3007");
    //cout<<"similitud entre "<<similitud_books("1293","593")<<endl;;
    return 0;
}



