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

columna matrix;
//

void load_users()
{
    string buffer;
    ifstream users("BX-Users.csv");
    unordered_map<string,int> hash_users;
    int i=0;
    while(!users.eof())
    {
        getline(users,buffer,';');
        if(!buffer.empty())
        {
            hash_users.insert({buffer,i});
            i++;
        }   
        getline(users,buffer);
    }
    cout<<"size of hash_users:\t"<<hash_users.size()<<endl;
}
void load_books()
{
    //std::cout << "my hash_users contains:" << std::endl;
    //for (auto& x: hash_users)
    //std::cout << x.first << ": " << x.second << std::endl;

    ifstream books("BX-Books.csv");
    i=0;
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
}
void load_matrix()
{
    ifstream ratings("BX-Book-Ratings.csv");
    //cout<<"crear hash"<<endl;
    
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
                ra=9999.99;
            }
            cout<<"Line: "<<line<<" insert: "<<c<<" r: "<<row<<" rating: "<<ra<<endl;

            fila f;
            f.insert({row,ra});
            matrix.insert({c,f});
            line++;
        }
    }

}

int main()
{
    
    return 0;
}