#include <iostream>
#include <stdio.h>
using namespace std;
bool E(int);
string s;
int cursor;
bool match(char x)
{   
    return cursor < s.length() and x == s[cursor++];
}
bool F(int savedCur)
{
    cursor = savedCur;
    if (match('c') and F(cursor))
        return true;
    cursor = savedCur;
    if (match('(') and E(cursor) and match(')'))
        return true;
    cursor = savedCur;
    if (match('d'))
        return true;
    cursor = savedCur;
    return match('e');
}
bool H(int savedCur)
{
    cursor = savedCur;
    if (match('b') and F(cursor) and H(cursor))
        return true;
    cursor = savedCur;
    return true;
}
bool T(int savedCur)
{
    cursor = savedCur;
    return F(cursor) and H(cursor);
}
bool G(int savedCur)
{
    cursor = savedCur;
    if (match('a') and T(cursor) and G(cursor))
        return true;
    cursor = savedCur;
    return true;
}
bool E(int savedCur)
{
    cursor = savedCur;
    return T(cursor) and G(cursor);
}
string ReplaceString(string subject, const string& search,
                          const string& replace) {
    size_t pos = 0;
    while ((pos = subject.find(search, pos)) != string::npos) {
         subject.replace(pos, search.length(), replace);
         pos += replace.length();
    }
    return subject;
}
int main()
{
    s = "not not true";
    s = ReplaceString(s, "not", "c");
    s = ReplaceString(s, "true", "d");
    s = ReplaceString(s, "false", "e");
    s = ReplaceString(s, "or", "a");
    s = ReplaceString(s, "and", "b");
    s = ReplaceString(s, " ", "");
    // cout << s;
    if ( E(0) and cursor == s.length() )
        printf("Parsed");
    else
        printf("Cannot Parse");
}