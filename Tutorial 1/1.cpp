#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;

int dfa[][3] = {
	{1, 0, 1},
	{4, 0, 2},
	{0, 4, 3},
	{2, 3, 4},
	{4, 3, 0}
};

int main()
{
    // freopen("input1.in", "r", stdin);
	string S;
	cout << "Enter input string\n";
	cin >> S;
	int state = 0, final_state = 4;
	bool accepted = false;

	for ( int i = 0 ; i < S.length() ; i++ )
	{
		string prefix = S.substr(0, i);

		if ( state == final_state )
			cout << "String input so far: "<< prefix <<" is ACCEPTED\n";
		else
			cout << "String input so far: "<< prefix <<" is NOT ACCEPTED\n";

		printf("Current State: %c,", char(state+65));
		char X = S[i];
		int symbol = X-48;
		if ( symbol < 0 || symbol >= 3  )
		{
			printf("  Unkown Symbol: %c", X);
			break;
		}
		printf("  Current Symbol: %c\n\n", char(48+symbol));
		state = dfa[state][symbol];
		if ( i == S.length() - 1 && state == final_state)
			accepted = true;
	}

	if ( accepted )
		printf("\nFinal Status: String Succesfully Accepted\n");
	else
		printf("\nFinal Status: String Not Accepted\n");
}