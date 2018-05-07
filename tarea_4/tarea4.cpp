#include<iostream>
#include<vector>
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

#define vec_atrib vector<string>
#define users unordered_map<string,vec_atrib*>
#define books unordered_map<string,vec_atrib*>

#define myvec vector < MyStruct >

columna_u matrix_user;
columna_b matrix_book;

users hash_users;
books hash_books;


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
            if(itf1->first==itf2->first)
            {
                resultado+=pow((itf1->second - itf2->second),2.0);
            }
        }
        itf1++;         
    }
    return sqrt(resultado);
}

float correlacion_pearson(string col1, string col2)
{
    //cout<<"columnas a evaluar: "<<col1<<" , "<<col2<<endl;
    float sum_x_m_y=0.0;
    float sum_x=0.0;
    float sum_y=0.0;
    float sum_c_x=0.0;
    float sum_c_y=0.0;
    //float resultado=0.0;

    int n=0;
    
    auto itc1=matrix_user.find(col1); 
    auto itc2=matrix_user.find(col2);

    if(itc1==matrix_user.end())
        cout<<"columna 1 no existe: "<<col1<<endl;
    if(itc2==matrix_user.end())
        cout<<"columna 2 no existe: "<<col2<<endl;
    
    
    auto it_matrix_end=matrix_user.end();
    auto itf1=itc1->second->begin();

    while(itf1!=itc1->second->end() && itc1!=it_matrix_end && itc2!=it_matrix_end && itc1->second->begin()!=itc2->second->end())
    {
        auto itf2=itc2->second->find(itf1->first);

        if(itf1 != itc1->second->end() && itf2 != itc2->second->end())
        {
            //cout<<"entro 1 if"<<endl;
            
                //cout<<itf1->second<<","<<itf2->second<<endl;

                sum_x=sum_x+itf1->second;
                //cout<<"sum_x: "<<sum_x<<endl;
                
                sum_y=sum_y+itf2->second; 
                //cout<<"sum_y: "<<sum_y<<endl;

                sum_c_x=sum_c_x+powf(itf1->second,2.0);
                //cout<<"sum_c_x: "<<sum_c_x<<endl;
                
                sum_c_y=sum_c_y+powf(itf2->second,2.0);
                //cout<<"sum_c_y: "<<sum_c_y<<endl;
                
                sum_x_m_y=sum_x_m_y+(itf1->second*itf2->second);
                //cout<<"sum_x_m_y: "<<sum_x_m_y<<endl;

                n++;
                //cout<<"n: "<<n<<endl;
                
            
           
            
        }
         //cout<<"===========>"<<endl;
        //cout<<"no hay coincidencia"<<endl;
        itf1++; 
    }
    
    //resultado=(sum_x_m_y-((sum_x*sum_y)/n))/((sqrt(sum_c_x-(pow(sum_x,2.0)/n)))*(sqrt(sum_c_y-(pow(sum_y,2.0)/n))));
    float sum=(sum_x*sum_y)/n;
    float numerador=sum_x_m_y-sum;
    
    float mx=powf(sum_x,2.0);
    mx=mx/n;
    float sqrt1=sqrtf(sum_c_x-mx);
    
    float my=powf(sum_y,2.0);
    my=my/n;
    float sqrt2=sqrtf(sum_c_y-my);
    
    float denominador=sqrt1*sqrt2;

    float resultado=numerador/denominador;

    if(n==0||n==1||isnan(resultado))
        return resultado=-1.0;
    
    //cout<<"resultado de Pearson:\t"<<resultado<<endl;
    /*if(n>=3 && numerador>0 && denominador>0)
    {
        cout<<"=================================="<<endl;
        cout<<"columnas a evaluar: "<<col1<<" , "<<col2<<endl;
        cout<<"sum_x: "<<sum_x<<endl;  
        cout<<"sum_y: "<<sum_y<<endl;
        cout<<"sum_c_x: "<<sum_c_x<<endl;
        cout<<"sum_c_y: "<<sum_c_y<<endl;
        cout<<"sum_x_m_y: "<<sum_x_m_y<<endl;
        cout<<"n: "<<n<<endl;
        
        cout<<"numerador: "<<numerador<<endl;
        cout<<"sqrt1: "<<sqrt1<<endl;
        cout<<"sqrt2: "<<sqrt2<<endl;
        cout<<"denominador: "<<denominador<<endl;
        
        cout<<"resultado de Pearson:\t"<<resultado<<endl;
        cout<<"=================================="<<endl;
         return resultado;
        
    }
    */
    else
        return resultado;


   
    
}

float similitud_coseno(string col1,string col2)
{
    //cout<<"COSENO: "<<col1<<" y "<<col2<<endl;
    float resultado_x=0.0, resultado_y=0.0, resultado_p=0.0, resultado=0.0;

    auto columna1=*(matrix_user.find(col1)->second);
    auto columna2=*(matrix_user.find(col2)->second);
    
    auto itc1=columna1.begin();
    // itc2=columna2.find(itc1->first);

    //cout<<"Columna 2 original size: "<<columna2.size()<<endl;

    while(itc1!=columna1.end())
    {
        
        auto itc2=columna2.find(itc1->first);
        ///cout<<"obtuvo itc2"<<endl;
        if(itc2!=columna2.end() && itc1->first==itc2->first)
        {
            resultado_p+=(itc1->second*itc2->second);
            resultado_x+=powf(itc1->second,2.0);
            resultado_y+=powf(itc2->second,2.0);
            columna2.erase(itc2);
        }
        else
        {
            resultado_x+=powf(itc1->second,2.0);
            
        }
        itc1++;
    }
    //cout<<"Columna 2 erase size: "<<columna2.size()<<endl;
    for(auto itr = columna2.begin(); itr!=columna2.end(); itr++) 
    {
        resultado_y+=powf(itr->second,2.0);
    }

    resultado=resultado_p/(pow(resultado_x,0.5)*(pow(resultado_y,0.5)));
    if(isnan(resultado))
        return -1.0;
    else
        return resultado;   
    
    /*
    float resultado_x=0.0, resultado_y=0.0, resultado_p=0.0, resultado=0.0;

    auto itc1=matrix_user.find(col1); 
    auto itc2=matrix_user.find(col2);    
    auto it_matrix_end=matrix_user.end();
    auto itf1=itc1->second->begin();

    std::unordered_map< string, std::vector< float > > map ;
    
    auto tmp =itc2->second;

    while(itf1!=itc1->second->end()&&itc1!=it_matrix_end && itc2!=it_matrix_end && itc1->second->begin()!=itc2->second->end())
    {
        auto itf2=itc2->second->find(itf1->first);
        if(itf1 != itc1->second->end() && itf2 != itc2->second->end())
        {
            if(itf1->first==itf2->first)
            {
                
                map[itf1->first].push_back(itf1->second);
                map[itf1->first].push_back(itf2->second);
               // cout<<"insert: "<<itf1->second<<" , "<<itf2->second <<endl;
               
            }
                          
        }
        else//if(itf2->first!=itf2->first)
        {
                map[itf1->first].push_back(itf1->second);
                map[itf1->first].push_back(0.0);
                //cout<<"insert2: "<<itf1->second<<" , "<<0.0 <<endl;
        } 
        itf1++;    
        
    }
    auto itf2=itc2->second->begin();
    while(itf2!=itc2->second->end())
    {
        auto it = map.find(itf2->first);
        if(it==map.end())
        {
            //cout<<"newinsert"<<endl;
            map[itf2->first].push_back(0.0);
            map[itf2->first].push_back(itf2->second);
        }
        itf2++;
    }
    
    for(auto itr = map.begin(); itr!=map.end(); itr++) 
    {
      //std::cout<<itr->first<<":";
      
          resultado_p+=(itr->second[0]*itr->second[1]);
          resultado_x+=powf(itr->second[0],2.0);
          resultado_y+=powf(itr->second[1],2.0);
          //std::cout<<*vitr<<",";
      
      //std::cout<<std::endl;
    }
    resultado=resultado_p/(pow(resultado_x,0.5)*(pow(resultado_y,0.5)));
    if(isnan(resultado))
        return -1.0;
    else
        return resultado;   */
}

float distancia_manhattan(string col1,string col2)
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
            
            if(itf1->first==itf2->first)
            {
                resultado+=fabs(itf1->second - itf2->second);
            }
        }
        itf1++;      
    }
    return resultado;
}

struct MyStruct
{
    string key;
    float distancia;
    float pearson;
    float influencia;

    MyStruct(string k, float e,float p,float i) : key(k), distancia(e), pearson(p),influencia(i) {}
};

struct less_distance
{
    inline bool operator() (const MyStruct& struct1, const MyStruct& struct2)
    {
        return (struct1.distancia < struct2.distancia);
    }
};

struct higher_distance
{
    inline bool operator() (const MyStruct& struct1, const MyStruct& struct2)
    {
        return (struct1.distancia > struct2.distancia);
    }
};


myvec k_nn_pearson(string col,int k)
{
    myvec vec;
    auto itc1=matrix_user.find(col);
    
    auto itc2=matrix_user.begin();    
    auto it_matrix_end=matrix_user.end();
    while(itc2!=it_matrix_end && itc2->first!=col)
    {
        
        vec.push_back(MyStruct(itc2->first,correlacion_pearson(col,itc2->first),0.0,0.0));
        itc2++;
    }
    std::sort(vec.begin(), vec.end(), higher_distance());
    int fin=(vec.size()-k);
    for(int i=0;i<fin;i++)
        vec.pop_back();
    return vec;

}
myvec k_nn_manhattan(string col,int k)
{
    myvec vec;
    auto itc1=matrix_user.find(col); 
    auto itc2=matrix_user.begin();    
    auto it_matrix_end=matrix_user.end();
    float resultado=1.1;
    while(itc2!=it_matrix_end)
    {
        resultado=distancia_manhattan(col,itc2->first);
        if(resultado!=0.0)
            vec.push_back(MyStruct(itc2->first,resultado,0.0,0.0));
        itc2++;
    }
    std::sort(vec.begin(), vec.end(), less_distance());
    
    int fin=(vec.size()-k);
    for(int i=0;i<fin;i++)
        vec.pop_back();
    return vec;

}
myvec k_nn_coseno(string col,int k)
{
    myvec vec;
    auto itc1=matrix_user.find(col); 
    auto itc2=matrix_user.begin();    
    auto it_matrix_end=matrix_user.end();
    while(itc2!=it_matrix_end)
    {
        vec.push_back(MyStruct(itc2->first,similitud_coseno(col,itc2->first),0.0,0.0));
        itc2++;
    }
    cout<<"acabo knn"<<endl;
    std::sort(vec.begin(), vec.end(), higher_distance());
    //for(int i=0;i<vec.size();i++)
    //    cout<<vec[i].key<<" , "<<vec[i].distancia<<" , "<<vec[i].pearson<<endl;
    vec.erase(vec.begin());
    

    int fin=(vec.size()-k);
    for(int i=0;i<fin;i++)
        vec.pop_back();
    
    return vec;

}
myvec k_nn_euclidea(string col,int k)
{
    myvec vec;
    auto itc1=matrix_user.find(col); 
    auto itc2=matrix_user.begin();    
    auto it_matrix_end=matrix_user.end();
    float resultado=1.1;
    while(itc2!=it_matrix_end)
    {
        resultado=distancia_manhattan(col,itc2->first);
        if(resultado!=0.0)
            vec.push_back(MyStruct(itc2->first,distancia_euclidea(col,itc2->first),0.0,0.0));
        itc2++;
    }
    std::sort(vec.begin(), vec.end(), less_distance());
    int fin=(vec.size()-k);
    for(int i=0;i<fin;i++)
        vec.pop_back();
    return vec;
}

void calcular_influencia(string col, vector < MyStruct >& score)
{
    float suma_pearson=0.0;
    float resultado;
    for(int i=0;i<score.size();i++)
    {
        resultado=similitud_coseno(col,score[i].key);
        //cout<<"pearson k_nn: "<<col<<" , "<<score[i].key<<"  resultado: "<<resultado<<endl;

        score[i].pearson=resultado;
        // cout<<suma_pearson<<endl;
        suma_pearson+=score[i].pearson;
    }
    cout<<suma_pearson<<endl;
    for(int i=0;i<score.size();i++)
    {
        //score[i].influencia=score[i].pearson/suma_pearson*100;
        score[i].influencia=score[i].pearson/suma_pearson;
    }

}
float proyectado_knn_coseno(string name,string libro,int k)
{
    myvec knn=k_nn_coseno(name,k);
    calcular_influencia(name,knn);

    float resultado=0.0;
    for(int i=0;i<k;i++)
    {
        auto itmb=matrix_book.find(libro);
        if(itmb!=matrix_book.end())
        {
            auto it=itmb->second->find(knn[i].key);
            if(it!=itmb->second->end())
                resultado+=knn[i].influencia*it->second;
            else
                resultado+=0.0;
        }
    }
    for(int i=0;i<knn.size();i++)
    {
            cout<<knn[i].key<<" ; "<<knn[i].distancia<<" ; "<<knn[i].pearson<<" ; "<<knn[i].influencia;

        cout<<endl;
    }
    return resultado;
}
myvec k_nn_rango(string col,float r)
{
    myvec vec;

    auto itc1=matrix_user.find(col); 
    auto itc2=matrix_user.begin();    
    auto it_matrix_end=matrix_user.end();
    //auto itf1=itc1->second->begin();
    //auto itf2=itc2->second->begin();

    while(itc2!=it_matrix_end)
    {
        
        vec.push_back(MyStruct(itc2->first,similitud_coseno(col,itc2->first),0.0,0.0));
        itc2++;
    }
    

    std::sort(vec.begin(), vec.end(), less_distance());
    vec.erase(vec.begin());
    //cout<<"ordenado"<<endl;
    //cout<<"vec_size"<<vec.size()<<endl;
   
 
    
    auto it =vec.begin();
    while(it!=vec.end())
    {
        
        if(r>(it->distancia))
        {
             //   cout<<"if"<<r<<" , "<<it->euclidia<<endl;
            vec.erase(it);
            it=vec.begin();
        }
        it++;
    }
    //for(int i=0;i<vec.size();i++)
    //    cout<<vec[i].key<<","<<vec[i].euclidia<<"."<<endl;
    //cout<<"fin aaaaa"<<endl;
    
    return vec;

}
void crear_usuario(string name)
{
    vector<string> lmovie;
    lmovie.push_back("7");
    lmovie.push_back("285");
    lmovie.push_back("1317");
    lmovie.push_back("5323");
    lmovie.push_back("3581");
    lmovie.push_back("134246");
    lmovie.push_back("63239");
    lmovie.push_back("73531");
    lmovie.push_back("2354");
    lmovie.push_back("82242");

    vector<float> lrating;
    lrating.push_back(3.5);
    lrating.push_back(4.1);
    lrating.push_back(2.0);
    lrating.push_back(1.5);
    lrating.push_back(2.8);
    lrating.push_back(5.0);
    lrating.push_back(3.7);
    lrating.push_back(4.8);
    lrating.push_back(1.8);
    //lrating.push_back(1.8);
    lrating.push_back(4.5);
    
    for(int i=0;i<lmovie.size();i++)
    {
        auto it_f_b=matrix_user.find(name);
        auto it_f_u=matrix_book.find(lmovie[i]);
        if(it_f_b!=matrix_user.end())
        {
            it_f_b->second->insert({lmovie[i],lrating[i]});
        }
        else
        {
            fila_b* fb=new fila_b();
            fb->insert({lmovie[i],lrating[i]});
            matrix_user.insert({name,fb});
        }
        if(it_f_u!=matrix_book.end())
        {
            it_f_u->second->insert({name,lrating[i]});
        }
        else
        {
            fila_u* fu=new fila_u();
            fu->insert({name,lrating[i]});
            matrix_book.insert({lmovie[i],fu});
        }
        
    }
    //auto itmu=
}
int main()
{

    load_matrix_file();
    //cout<<"distancia_euclidea: "<<distancia_euclidea("135","205")<<endl;;
    //cout<<"distancia_manhatan: "<<distancia_manhattan("135","205")<<endl;;
    //cout<<"correlacion de Pearson: "<<correlacion_pearson("135","205")<<endl;;
    //cout<<"similitud_coseno: "<<similitud_coseno("205","207")<<endl;;
    crear_usuario("ben");
    cout<<"correlacion de Pearson: "<<correlacion_pearson("ben","475")<<endl;
    cout<<"proyeccion:\t"<<proyectado_knn_coseno("ben","Desperado (1995)",10)<<endl;
    
    
    
    /*calcular_influencia("ben",knn);
    for(int i=0;i<knn.size();i++)
    {
            cout<<knn[i].key<<" ; "<<knn[i].distancia<<" ; "<<knn[i].pearson<<" ; "<<knn[i].influencia;

        cout<<endl;
    }
    //cout<<"proyeccion:\t"<<proyectado_knn(knn,"Lord of the Rings")<<endl;
    */
    return 0;
}



