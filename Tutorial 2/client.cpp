#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;

#define s1 "CLOSED"
#define s2 "SYNSENT"
#define s3 "CONNECTED"
#define s4 "FINWAIT"
#define invalid "INVALID"

int main()
{
    freopen("client_input.in", "r", stdin);
    string state = s1;   
    string input;
    cout << "CLIENT SOCKET CREATED\n";
    while ( getline(cin, input) )
    {
        cout << "\nCurrent State: " << state << endl;
        cout << "INPUT: "<<input << endl;

        if ( state == s1 )  /*CLOSED*/
        {
            if ( input == "srt_client_connect()" )
            {
                cout << "send SYN\n";
                state = s2;
            }
            else if ( input == "srt_client close()" )
            {
                cout << "CLIENT SOCKET CLOSING\nEXITING...\n";
                break;
            }
            else
                state = invalid;
        }
        else if ( state == s2 ) /*SYNSENT*/
        {
            if ( input == "SYN_TIMEOUT" )
                cout << "send SYN\n";
            else if ( input == "SYN_MAX_RETRY exceed" )
                state = s1;
            else if ( input == "Receive SYNACK" )
                state = s3;
            else
                state = invalid;
        }
        else if ( state == s3 )
        {
            if ( input == "srt_client_disconnect()" )
            {
                cout << "send SYN\n";
                state = s4;
            }
            else
                state = invalid;
        }
        else if ( state == s4 )
        {
            if ( input == "receive FINACK" )
                state = s1;
            else if ( input == "FIN_TIMEOUT" )
            {
                cout << "send FIN";
                state = s4;
            }
            else if ( input == "FIN_MAX_RETRY exceed" )
                state = s1;
            else
                state = invalid;
        }
        if ( state == invalid )
        {
            cout << "\nINVALID INPUT ENTERED\nEXITING PROGRAM....";
            break;
        }
    }


}