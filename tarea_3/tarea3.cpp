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

void load_matrix_file()
{
 ifstream input("../../bd/BX-Book-Ratings.csv");
    string u,b,r;
    
    float rat=0.0;
    int line=1;
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
            //cout<<" user: "<<u<<" book: "<<b<<" rat: "<<rat<<endl;
            //fila_b fb;
            //fb.insert({b,rat});

            //fila_u fu;
            //fu.insert({u,rat});
            
       

            
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
            
            //cout<<"line: "<<line<<" user: "<<u<<" book: "<<b<<" rat: "<<rat<<endl;
            ++line;
        }

    }

    auto it=matrix_user.begin();
    int size_hash_y=0;
    while(it!=matrix_user.end())
    {
        //cout<<it->first<<" size hash: "<<(it->second)->size()<<endl;

        auto it2=it->second->begin();
        while(it2!=it->second->end())
        {
            //cout<<"   "<<it2->first<<" , "<<it2->second<<"    ";
            size_hash_y++;
            it2++;
        }
        //cout<<endl;
        it++;
    }
    cout<<"size_hash:\t"<<size_hash_y<<endl;

    cout<<"load matriz users \n size_matrix_user: "<<matrix_user.size()<<endl;
    cout<<"load matriz books \n size_matrix_book: "<<matrix_book.size()<<endl;

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
            cout<<" user: "<<u<<" book: "<<b<<" rat: "<<rat<<endl;
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

    

    cout<<"load matriz users \n size_matrix_user: "<<matrix_user.size()<<endl;
    cout<<"load matriz books \n size_matrix_book: "<<matrix_book.size()<<endl;
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
                //cout<<"col1: "<<itf1->second<<" col2: "<<itf2->second<<" res: "<<resultado<<endl;
                //cout<<itf2->second<<endl;
                resultado+=pow((itf1->second - itf2->second),2.0);
            }
            //itf1++;
        }
        //cout<<"no hay coincidencia"<<endl;
        itf1++;    
        
    }

    return sqrt(resultado);
    /*    float resultado=0.0;
    auto itc1=matrix_user.find(col1)->second->begin();
    auto itc2=matrix_user.find(col2)->second;
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
    return sqrt(resultado);
    */
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



    if(n==0||n==1||sum_x_m_y==0.0)
        resultado=-1.0;
    if(n>=2)
    {
        /*cout<<"=================================="<<endl;
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
        cout<<"=================================="<<endl;*/
        
    }
    //cout<<"resultado de Pearson:\t"<<resultado<<endl;

    return resultado;
    
}
/*
float correlacion_pearson(string col1, string col2)
{
   // cout<<"Usuarios a evaluar: "<<col1<<" ; "<<col2<<endl;
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
    //cout<<"size_books col1: "<<itc1->second->size()<<endl;
    
    
    while(itf1!=itc1->second->end() && itc1!=it_matrix_end && itc2!=it_matrix_end && itc1->second->begin()!=itc2->second->end())
    {
        auto itf2=itc2->second->find(itf1->first);
        //cout<<"libro a buscar:\t"<<itf1->first<<endl;
        if(itf1 != itc1->second->end() && itf2 != itc2->second->end())
        {
            //cout<<"coincidencia libro:\t"<<itf1->first<<" ; "<<itf2->first<<endl;
            if(itf1->first==itf2->first)
            {
                //cout<<"coincidencia libro:\t"<<itf1->first<<" ; "<<itf2->first<<endl;
                //cout<<"coincidencia rating:\t"<<itf1->second<<" ; "<<itf2->second<<endl;
                sum_x+=itf1->second;
                sum_y+=itf2->second; 
                sum_c_x+=pow(itf1->second,2.0);
                sum_c_y+=pow(itf2->second,2.0);
                sum_x_m_y+=(itf1->second*itf2->second);
                n++;
                //cout<<"sum_x: "<<sum_x<<endl;
                //cout<<"sum_y: "<<sum_y<<endl; 
                //cout<<"sum_c_x: "<<sum_c_x<<endl;
                //cout<<"sum_c_y: "<<sum_c_y<<endl;
                //cout<<"sum_x_m_y: "<<sum_x_m_y<<endl;
                //cout<<n<<endl;
                //cout<<itf2->second<<endl;
                //resultado+=pow((itf1->second - itf2->second),2.0);
            }
            //itf1++;
            
        }
        //cout<<"no hay coincidencia"<<endl;
        itf1++; 
    }
    

    resultado=(sum_x_m_y-((sum_x*sum_y)/n))/
    ((sqrt(sum_c_x-(pow(sum_x,2.0)/n)))*(sqrt(sum_c_y-(pow(sum_y,2.0)/n))));
    //cout<<"Correlacion de Pearson: "<<resultado<<endl;

    return resultado;
}
*/

float similitud_coseno(string col1,string col2)
{
    float resultado_x=0.0, resultado_y=0.0, resultado_p=0.0, resultado=0.0;

    auto itc1=matrix_user.find(col1); 
    auto itc2=matrix_user.find(col2);    
    auto it_matrix_end=matrix_user.end();
    auto itf1=itc1->second->begin();

    std::unordered_map< string, std::vector< float > > map ;
    

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
        return (struct1.euclidia < struct2.euclidia);
    }
};

struct more_than_key
{
    inline bool operator() (const MyStruct& struct1, const MyStruct& struct2)
    {
        return (struct1.euclidia > struct2.euclidia);
    }
};

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
                //cout<<"col1: "<<itf1->second<<" col2: "<<itf2->second<<" res: "<<resultado<<endl;
                //cout<<itf2->second<<endl;
                //resultado+=(fabs(itr->second[0]-itr->second[1]));
                resultado+=fabs(itf1->second - itf2->second);
            }
            //itf1++;
        }
        //cout<<"no hay coincidencia"<<endl;
        itf1++;    
        
    }

   
    return resultado;
}

myvec k_nn_pearson(string col,int k)
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
        //cout<<correlacion_pearson(col,itc2->first)<<endl;
        itc2++;
    }
    cout<<"inicio:\t"<<vec.size()<<endl;

    std::sort(vec.begin(), vec.end(), more_than_key());
    //for(int i=0;i<vec.size();i++)
    //    cout<<vec[i].key<<" , "<<vec[i].euclidia<<" , "<<vec[i].pearson<<endl;

    vec.erase(vec.begin());
    
    int fin=(vec.size()-k);
    for(int i=0;i<fin;i++)
        vec.pop_back();
        
    //for(int i=0;i<vec.size();i++)
    //    cout<<vec[i].key<<" , "<<vec[i].euclidia<<" , "<<vec[i].pearson<<endl;
    //cout<<"ordenado"<<endl

    cout<<"fin:\t"<<vec.size()<<endl;
    
    
    return vec;

}
myvec k_nn_manhattan(string col,int k)
{
    myvec vec;
    auto itc1=matrix_user.find(col); 
    auto itc2=matrix_user.begin();    
    auto it_matrix_end=matrix_user.end();

    while(itc2!=it_matrix_end)
    {
        
        vec.push_back(MyStruct(itc2->first,distancia_manhattan(col,itc2->first),0.0,0.0));
        itc2++;
    }
    cout<<"inicio:\t"<<vec.size()<<endl;
    std::sort(vec.begin(), vec.end(), more_than_key());
    //vec.erase(vec.begin());
    int fin=(vec.size()-k);
    for(int i=0;i<fin;i++)
        vec.pop_back();
    cout<<"fin:\t"<<vec.size()<<endl; 
     std::sort(vec.begin(), vec.end(), less_than_key());
    return vec;

}
myvec k_nn_euclidea(string col,int k)
{
    myvec vec;
    auto itc1=matrix_user.find(col); 
    auto itc2=matrix_user.begin();    
    auto it_matrix_end=matrix_user.end();

    while(itc2!=it_matrix_end)
    {
        
        vec.push_back(MyStruct(itc2->first,distancia_euclidea(col,itc2->first),0.0,0.0));
        itc2++;
    }
    cout<<"inicio:\t"<<vec.size()<<endl;
    std::sort(vec.begin(), vec.end(), less_than_key());
    //vec.erase(vec.begin());
    int fin=(vec.size()-k);
    for(int i=0;i<fin;i++)
        vec.pop_back();
    cout<<"fin:\t"<<vec.size()<<endl;  
    return vec;

}
myvec k_nn_coseno(string col,int k)
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
        //cout<<correlacion_pearson(col,itc2->first)<<endl;
        itc2++;
    }
    //Usando euclidea
    std::sort(vec.begin(), vec.end(), more_than_key());
    vec.erase(vec.begin());
    for(int i=0;i<vec.size();i++)
        cout<<vec[i].key<<" , "<<vec[i].euclidia<<" , "<<vec[i].pearson<<endl;
    cout<<"ordenado"<<endl;
    int fin=(vec.size()-k);
    for(int i=0;i<fin;i++)
        vec.pop_back();
    
    /*
    //original
    

    std::sort(vec.begin(), vec.end(), less_than_key());
    vec.erase(vec.begin());
    
    int fin=(vec.size()-k);
    for(int i=0;i<fin;i++)
        vec.pop_back();

    */
    //for(int i=0;i<vec.size();i++)
    //    cout<<vec[i].key<<" , "<<vec[i].euclidia<<" , "<<vec[i].pearson<<endl;
    //cout<<"ordenado"<<endl;

    

    //cout<<"vec_size"<<vec.size()<<endl;
    /*int fin=(vec.size()-k);

    for(int i=0;i<fin;i++)
        vec.pop_back();
    //cout<<"vec_size"<<vec.size()<<endl;*/

    //cout<<"fin:\t"<<vec.size()-k<<endl;
    
    
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
    //cout<<"entre proyeccion"<<endl;
    int k= knn.size();
    float resultado=0.0;
    //float * puntaje=new float[k];
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
                //cout<<"autor no califico libro"<<endl;
        }//cout<<knn[i].influencia*matrix_book.find(libro)->second->find(knn[i].key)->second<<endl;

    }
    //cout<<resultado;
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
    

    std::sort(vec.begin(), vec.end(), less_than_key());
    vec.erase(vec.begin());
    //cout<<"ordenado"<<endl;
    //cout<<"vec_size"<<vec.size()<<endl;
   
 
    
    auto it =vec.begin();
    while(it!=vec.end())
    {
        
        if(r>(it->euclidia))
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
    lmovie.push_back("Gladiator");
    lmovie.push_back("Alien");
    lmovie.push_back("Avatar");
    lmovie.push_back("Spiderman");
    lmovie.push_back("Star Wars");
    vector<float> lrating;
    lrating.push_back(2.0);
    lrating.push_back(4.0);
    lrating.push_back(3.0);
    lrating.push_back(5.0);
    lrating.push_back(3.0);
    
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
    /*
    vector<string> lmovie;
    lmovie.push_back("Gladiator");
    lmovie.push_back("Alien");
    lmovie.push_back("Avatar");
    lmovie.push_back("Spiderman");
    lmovie.push_back("Star Wars");
    vector<float> lrating;
    lrating.push_back(2.0);
    lrating.push_back(4.0);
    lrating.push_back(3.0);
    lrating.push_back(5.0);
    lrating.push_back(3.0);
    
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
*/
}
int main()
{
    load_hash_header();
    load_matrix_file();
    
    //cout<<"distancia_euclidea: "<<distancia_euclidea("15600","15651");
    //cout<<"distancia_euclidea: "<<correlacion_pearson("15600","15651");ç
    //cout<<"distancia_manhatan: "<<correlacion_pearson("29605","15651");
    cout<<"===> 277752 "<<"k:  "<<8<<endl;
    myvec knn=k_nn_pearson("277752",8);
    for(int i=0;i<knn.size();i++)
    {
            cout<<knn[i].key<<" ; "<<knn[i].euclidia<<" ; "<<knn[i].pearson<<" ; "<<knn[i].influencia;

        cout<<endl;
    }



    cout<<"===> 29605 "<<"k:  "<<10<<endl;
    myvec knn2=k_nn_manhattan("29605",10);
    //myvec knn=k_nn_euclidea("38556",10);
    //calcular_influencia("277752",knn);
    for(int i=0;i<knn.size();i++)
    {
            cout<<knn[i].key<<" ; "<<knn[i].euclidia<<" ; "<<knn[i].pearson<<" ; "<<knn[i].influencia;

        cout<<endl;
    }
    //cout<<"proyeccion:\t"<<proyectado_knn(knn,"Lord of the Rings")<<endl;
    
    return 0;
}






/*




cout<<"===> 10186 "<<"k:  "<<5<<endl;
    myvec knn=k_nn("10186",5);
    calcular_influencia("10186",knn);
    for(int i=0;i<knn.size();i++)
    {
            cout<<knn[i].key<<" ; "<<knn[i].euclidia<<" ; "<<knn[i].pearson<<" ; "<<knn[i].influencia;

        cout<<endl;
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
                //cout<<itf1->second<<","<<itf2->second<<endl;

                sum_x+=itf1->second;
                //cout<<"sum_x: "<<sum_x<<endl;
                
                sum_y+=itf2->second; 
                //cout<<"sum_y: "<<sum_y<<endl;

                sum_c_x+=pow(itf1->second,2.0);
                //cout<<"sum_c_x: "<<sum_c_x<<endl;
                
                sum_c_y+=pow(itf2->second,2.0);
                //cout<<"sum_c_y: "<<sum_c_y<<endl;
                
                sum_x_m_y+=(itf1->second*itf2->second);
                //cout<<"sum_x_m_y: "<<sum_x_m_y<<endl;

                n++;
                //cout<<"n: "<<n<<endl;
                
            }
           
            
        }
         //cout<<"===========>"<<endl;
        //cout<<"no hay coincidencia"<<endl;
        itf1++; 
    }
    
    
    resultado=(sum_x_m_y-((sum_x*sum_y)/n))/((sqrt(sum_c_x-(pow(sum_x,2.0)/n)))*(sqrt(sum_c_y-(pow(sum_y,2.0)/n))));
    //cout<<"resultado de Pearson:\t"<<resultado<<endl;
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
    //cout<<"vec_size"<<vec.size()<<endl;
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
}*/