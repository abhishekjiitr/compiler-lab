#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;

#define s0 "NULL"
#define s1 "CLOSED"
#define s2 "SYNSENT"
#define s3 "CONNECTED"
#define s4 "FINWAIT"

int main()
{
    freopen("client_input.in", "r", stdin);
    string state = s0;   
    string input;

    while ( true )
    {
        getline(cin, input);
        cout << input;

        if ( state == s0 )
        {
            if ( input == "srt_client_sock()" )
                state = s1;
        }
        else if ( state == s1 )
        {

        }
        else if ( state == s2 )
        {

        }
        else if ( state == s3 )
        {

        }
        else
        {

        }
    }


}