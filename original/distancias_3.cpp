#include<iostream>
#include<string>
#include<fstream>
#include<cstdio>
#include<cmath>
#include<unordered_map>

using namespace std;

#define INF 0.0
//#define std::unordered_map<std::string,int>::const_iterator element

int main()
{
    string buffer;
    ifstream users("BX-Dump/BX-Dump/BX-Users.csv");
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
    //std::cout << "my hash_users contains:" << std::endl;
    //for (auto& x: hash_users)
    //std::cout << x.first << ": " << x.second << std::endl;

    ifstream books("BX-Dump/BX-Dump/BX-Books.csv");
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

    ifstream ratings("BX-Dump/BX-Dump/BX-Book-Ratings.csv");
    int fila=hash_books.size();
    int columna=hash_users.size();
    cout<<"fila:\t"<<fila<<" columa:\t"<<columna<<endl;
    //float matrix[hash_books.size()][hash_users.size()];
    float matrix[fila][columna];
    cout<<"crea matrix"<<endl;
    string row,col,rating;
    while(!ratings.eof())
    {
        getline(ratings,col,';');
        getline(ratings,row,';');
        getline(ratings,rating);
        cout<<"paso el getline"<<endl;
        if(!col.empty())
            matrix[hash_books.at(row)][hash_users.at(col)]=stof(rating);
    }

    return 0;
}