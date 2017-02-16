#include <iostream>
#include <stdio.h>

using namespace std;

int dfa[][2] = {
	{-1, 1},
	{2, 1},
	{2, 3},
	{3, 4},
	{-1, 4}
};

int main()
{
	// freopen("input", "r", stdin);
	string s;
	cin >> s;
	int n = s.length();
	
	int state = 0, index = 0, input;
	bool accepted = false;

	while ( index < n )
	{
		input = s[index] - '0';
		state = dfa[state][input];
		if ( state < 0 )
		{
			accepted = false;
			break;
		}

		if ( state == 3 || state == 4 )
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