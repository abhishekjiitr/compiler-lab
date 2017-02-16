#include <iostream>
#include <stdio.h>
#include <set>

using namespace std;

char alphabet[256];
set<int> final_states;

bool isFinal(unsigned int num)
{
	unsigned int check=1;
	for(int j=0 ; j < 32 ; j++)
	{
		if ( num & check )
			if ( final_states.find(j) != final_states.end() )
				return true;
		check <<= 1;
	}
	return false;
}

unsigned int addstate(unsigned int state, int pos)
{
	int x=1;
	for(int i=0; i<pos-1; i++)
		x = x << 1;
	return state | x;
}

int main()
{
	freopen("input.in", "r", stdin);
	int asize;
	cin >> asize;
	cout << asize<<endl;
	char myalphabet;
	for(int i=0 ; i<asize ; i++)
		{
			cin >> myalphabet;
			alphabet[myalphabet] = 1;
			cout << myalphabet << endl;
		}
	int n;
	cin >> n;
	int total_states = 1 << n;
	int table[total_states][asize];
	cout << n << " " << total_states;
	for (unsigned int i=0 ; i<n ; i++ )
	{
		for (int j=0 ; j< 256 ; j++ )
		{
			if ( not alphabet[j] )
				continue;

			int to_states;
			cin >> to_states;
			unsigned int state = 0;
			for (int k=0 ; k<to_states ; k++)
			{
				int mystate;
				cin >> mystate;
				state = addstate(state, mystate);
			}
			table[1<<i][j] = state;
		}
	}

	for (unsigned int i=0 ; i< 1<<n ; i++)
	{	
		unsigned int current = i;

		for (int j=0 ; j<256 ; j++ )
		{
			if ( not alphabet[j] )
				continue;
			int check=1;
			for(int k=0 ; k<32 ; k++)
			{
				if ( check & current )
				{
					unsigned int reachable = table[k][j];
					table[current][j] |= reachable;
				}
				check <<= 1;
			}
		}
	}

	int final_size;
	cin >> final_size;
	for(int i=0 ; i<final_size ; i++)
	{
		int fstate;
		cin >> fstate;
		final_states.insert(fstate);
	}

	string s;
	cin >> s;
	
}