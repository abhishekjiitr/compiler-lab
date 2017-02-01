#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;

#define s1 "CLOSED"
#define s2 "LISTEN"
#define s3 "CONNECTED"
#define s4 "CLOSEWAIT"
#define invalid "INVALID"

int main()
{
    freopen("server_input.in", "r", stdin);
    string state = s1;   
    string input;
    cout << "SERVER SOCKET CREATED\n";
    while ( getline(cin, input) )
    {
        cout << "\nCurrent State: " << state << endl;
        cout << "INPUT: "<<input << endl;

        if ( state == s1 )  /*CLOSED*/
        {
            if ( input == "srt_svr_accept()" )
                state = s2;
            else if ( input == "srt_svr_close()" )
            {
                cout << "\nSERVER SOCKET CLOSING\n";
                cout << "EXITING PROGRAM...";
                break;
            }
            else
                state = invalid;
        }
        else if ( state == s2 ) /*LISTENING*/
        {
            if ( input == "receive SYN" )
            {
                cout << "send SYNACK\n";
                state = s3;
            }
            else
                state = invalid;
        }
        else if ( state == s3 ) /*CONNECTED*/
        {
            if ( input == "receive SYN" )
                cout << "send SYNACK\n";
            else if ( input == "receive FIN" )
            {
                cout << "send FINACK\n";
                state = s4;
            }
            else
                state = invalid;
        }
        else if ( state == s4 ) /*CLOSEWAIT*/
        {
            if ( input == "receive FINACK" )
                cout << "send FINACK\n";
            else if ( input == "CLOSE_WAIT_TIMEOUT" )
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