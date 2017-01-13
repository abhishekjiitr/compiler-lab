#include <bits/stdc++.h>
using namespace std;

char ALPHABET[256];
int alphabet_size;

int get_index(char symbol)
{
	int ans = -1;
	for(int i = 0 ; i < alphabet_size ; i++)
	{
		if ( ALPHABET[i] == symbol )
			return i;
	}
	return ans;
}

int main()
{
	freopen("input2.in", "r", stdin);
	printf("Input number of alphabets:\n");
	cin >> alphabet_size;
	printf("Enter the alphabets:\n");
	for(int i=0; i < alphabet_size ; i++)
	{
		cin >> ALPHABET[i];
	}

	int n;
	printf("Enter the number of states:\n");
	cin >> n;
	printf("Enter the state table:\n");
	int** dfa = new int*[n];
	for ( int i = 0 ; i < n ; i++ )
	{
		dfa[i] = new int[alphabet_size];
		int next_state;
		for ( int j = 0 ; j < alphabet_size ; j++ )
		{
			cin >> next_state;
			dfa[i][j] = next_state;
		}
	}
	int state, final_state;
	cout << "Enter initial state:\n";
	cin >> state;
	cout << "Enter final state\n";
	cin >> final_state;
	string S;
	cout << "Enter the string:\n";
	cin >> S;
	bool accepted = false;
	for ( int i = 0 ; i < S.length() ; i++ )
	{
		string prefix = S.substr(0, i);
		if ( state == final_state )
			cout << "String input so far: "<< prefix <<" is ACCEPTED\n";
		else
			cout << "String input so far: "<< prefix <<" is NOT ACCEPTED\n";

		printf("Current State: %d,", state);
		char symbol = S[i];
		int index = get_index(symbol);
		if ( index < 0 )
		{
			printf("  Unkown Symbol: %c", symbol);
			break;
		}
		printf("  Current Symbol: %c\n", symbol);
		state = dfa[state][index];

		if ( i == S.length() - 1 && state == final_state)
			accepted = true;
	}

	if ( accepted )
		printf("\nFinal Status: String Succesfully Accepted\n");
	else
		printf("\nFinal Status: String Not Accepted\n");
}
