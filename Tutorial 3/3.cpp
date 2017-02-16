#include <iostream>
#include <stdio.h>

using namespace std;

int dfa[][2] = {
	{0, 1},
	{0, 2},
	{0, 2}
};


int main()
{
	freopen("input", "r", stdin);
	string s;
	cin >> s;
	int n = s.length();
	
	int state = 0;
	int index = 0, input;
	bool accepted = false;

	while ( index < n )
	{
		input = s[index] - 'a';
		state = dfa[state][input];
		if ( state < 0 )
		{
			accepted = false;
			break;
		}

		if ( state == 2 )
			accepted = true;
		else
			accepted = false;	
		index++;	
	}

	if ( accepted )
		cout << "Input " << s << " is ACCEPTED";
	else
		cout << "Input " << s <<" is not ACCEPTED";
}