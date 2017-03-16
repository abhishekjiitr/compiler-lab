#include <iostream>
#include <stdio.h>
using namespace std;
bool S(int savedCur);
string s;
int cursor;
int savedCursor;
bool match(char x)
{   
    return cursor < s.length() and x == s[cursor++];
}
bool E1(int savedCur)
{
    // cout<<"E1 "<<savedCur<<endl;
    cursor = savedCur;
    return match('a') and S(cursor) and match('b') and S(cursor);
}
bool E2(int savedCur)
{
    // cout<<"E2 "<<savedCur<<endl;
    savedCursor = savedCur;
    return match('b') and S(cursor) and match('a') and S(cursor);
}
bool S(int savedCur)
{
    // cout<<"S "<<savedCur<<endl;
    cursor = savedCur;
    if (E1(savedCur))
        return  true;
    cursor = savedCur;
    if (E2(savedCur))
        return true;
    cursor = savedCur;
    return true;
}
int main()
{
    s = "aa";
    if ( S(0) and cursor == s.length() )
        printf("Parsed");
    else
        printf("Cannot Parse");
    // cout<<endl<<cursor;
}