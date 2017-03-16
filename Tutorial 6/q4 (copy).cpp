#include <iostream>
#include <stdio.h>
using namespace std;
bool S1(int savedCur);
bool S2(int savedCur);
string s;
int cursor;
bool match(char x)
{   
    return cursor < s.length() and x == s[cursor++];
}
bool E1(int savedCur)
{
    // cout<<"E1 "<<savedCur<<endl;
    bool b1=false, b2 = false;
    cursor = savedCur;
    if ( match('a') )
    {
        if ( S2(cursor) )
        {
            b1 = true;
            if ( match('a') )
                return true;
            cursor = savedCur;

        }
        else if ( S1(cursor))
            {
                if ( match('a') )
                    return true;
            }

    }
    return false;
}
bool E2(int savedCur)
{
    // cout<<"E2 "<<savedCur<<endl;
    cursor = savedCur;
    return match('a') and match('a');
}
bool S1(int savedCur)
{
    // cout<<"S "<<savedCur<<endl;
    cursor = savedCur;
    if (E2(savedCur))
        return  true;
    cursor = savedCur;
    return E1(savedCur);
}
bool S2(int savedCur)
{
    // cout<<"S "<<savedCur<<endl;
    cursor = savedCur;
    if (E2(savedCur))
        return  true;
    cursor = savedCur;
    return E1(savedCur);
}

int main()
{
    s = "aaaaaaaaaa";
    if ( (S1(0) or S2(0) ) and cursor == s.length() )
        printf("Parsed");
    else
        printf("Cannot Parse");
    // cout<<endl<<cursor;
}