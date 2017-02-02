#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

#define c1 "CLOSED"
#define c2 "SYNSENT"
#define c3 "CONNECTED"
#define c4 "FINWAIT"
#define invalid "INVALID"
#define s1 "CLOSED"
#define s2 "LISTENING"
#define s3 "CONNECTED"
#define s4 "CLOSEWAIT"
#define SYN_MAX_RETRY 3
#define FIN_MAX_RETRY 3

class Server
{
	public:
	string state;
	Server()
	{
		state = s1;
		serverState();
		listen();
	}
	void listen()
	{
		int listen = -1;
		while ( listen != 1 )
		{
			cout << "Press 1 to start Server listening:\n";
			cin >> listen;
		}
		serverState();
		state = s2;
	}
	void serverState()
	{
		cout << "Server State: " << state << endl;
	}
	int sendSyn()
	{
		return rand() % 2;
	}
	int sendFyn()
	{
		return rand() % 2;
	}
	void serverConnected()
	{
		state = s3;
		serverState();
	}
	void serverClosed()
	{
		state = s4;
		serverState();
		cout << "CLOSE_WAIT_TIMEOUT\n";
		state = s1;
		listen();
	}

};

int main()
{
	// freopen("input.in", "r", stdin);
	Server svr;
	string cstate = c1, input;
	int result, in, tries;
	while ( true )
	{
		cout << "Client State: " << cstate << endl;
		
		if ( cstate == c1 )
		{
			tries = 0;
			cout << "Press 1 to send SYN\n";
			cin >> in;
			if ( in == 1 )
			{
				result = svr.sendSyn();
				if ( result == 1 )
					svr.serverConnected();
				cstate = c3;
			} 
		}
		else if ( cstate == c2 )
		{
			if ( result == 1 )
			{
				cstate = c3;
				svr.serverConnected();
			}
			else
			{
				tries++;
				if ( tries > SYN_MAX_RETRY  )
					cstate = c1;
				else
				{
					cout << "Press 1 to send SYN\n";
					cin >> in;
					if ( in == 1 )
					{
						result = svr.sendSyn();
					}
				}
			}
		}
		else if ( cstate == c3 )
		{
			tries = 0;
			cout << "Press 1 to send FIN\n";
			cin >> in;
			if ( in == 1 )
			{
				result = svr.sendFyn();
				cstate = c4;
			}
		}	
		else
		{
			if ( result == 1 )
			{
				cstate = c1;
				svr.serverClosed();
			}
			else
			{
				tries++;
				if ( tries > FIN_MAX_RETRY )
					cstate = c1;
				cout << "Press 1 to send FIN\n";
				cin >> in;
				if ( in == 1 )
				{
					result = svr.sendFyn();
				}
			}
		}

		if ( cstate == invalid )
		{
			cout << "Program Exiting\n";
			break;
		}
	}
}