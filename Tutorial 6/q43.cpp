#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;
void S(int,vector <char>);
string s;
int cursor;
void match(char x, vector <char> v)
{   
    if ( cursor == s.length()-1  and x == s[cursor++])
    {
        for(int i = 0 ; i < v.size() ; i++)
            cout << v[i] << " ";
        cout  << endl;
    }
}
void E1(int savedCur, vector <char> v)
{
    v.push_back('1');
    // cout<<"E1 "<<savedCur<<endl;
    cursor = savedCur;
    match('a',v);
    S(cursor,v);
    match('a',v);
}
void E2(int savedCur, vector <char> v)
{
    v.push_back('2');
    // cout<<"E2 "<<savedCur<<endl;
    cursor = savedCur;
    match('a',v);
    match('a',v);
}
void S(int savedCur, vector<char> v)
{
    v.push_back('S');
    // cout<<"S "<<savedCur<<endl;
    cursor = savedCur;
    E1(savedCur,v);
    cursor = savedCur;
    E2(savedCur,v);
}
int main()
{
    s = "aaaa";
    vector <char> v;
    S(0,v);
    //     printf("Parsed");
    // else
    //     printf("Cannot Parse");
    // cout<<endl<<cursor;
}