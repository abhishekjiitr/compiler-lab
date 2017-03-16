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
    bool b1, b2;
    cout<<"S "<<savedCur<<endl;
    cursor = savedCur;
    b1 = E1(savedCur);
    cursor = savedCur;
    b2 = E2(savedCur);
    return b1 || b2;
}
int main()
{
    s = "aaaaaa";
    if ( S(0) and cursor == s.length() )
        printf("Parsed");
        
        printf("Cannot Parse");
    // cout<<endl<<cursor;
}