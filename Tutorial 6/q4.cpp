#include <iostream>
#include <stdio.h>
using namespace std;
bool S(int savedCur);
string s;
int cursor;
bool match(char x)
{   
    return cursor < s.length() and x == s[cursor++];
}
bool E1(int savedCur)
{
    cout<<"E1 "<<savedCur<<endl;
    cursor = savedCur;
    return match('a') and S(cursor) and match('a');
}
bool E2(int savedCur)
{
    cout<<"E2 "<<savedCur<<endl;
    cursor = savedCur;
    return match('a') and match('a');
}
bool S(int savedCur)
{
    cout<<"S "<<savedCur<<endl;
    cursor = savedCur;
    if (E1(savedCur))
        return  true;
    cursor = savedCur;
    E2(savedCur);
}
int main()
{
    s = "aaaaaa";
    if ( S(0) and cursor == s.length() )
        printf("Parsed");
        
        printf("Cannot Parse");
    // cout<<endl<<cursor;
}