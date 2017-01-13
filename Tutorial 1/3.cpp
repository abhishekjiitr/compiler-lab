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
	freopen("input3.in", "r", stdin);
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
	map<char, int>* dfa = new map<char, int> [n];
	for ( int i = 0 ; i < n ; i++ )
	{
		int transitions, next_state;
		char X;
		cout << "Enter number of transitions for state " << i << endl;
		cin >> transitions;
		cout << "Enter symbols and corresponding next states\n";
		for ( int j = 0 ; j < transitions ; j++ )
		{
			cin >> X;
			cin >> next_state;
			dfa[i][X] = next_state;
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
	cout << "\nInitial State: " << state << ", Final State: " << final_state << endl; 
	for ( int i = 0 ; i < S.length() ; i++ )
	{
		string prefix = S.substr(0, i);
		if ( state == final_state )
			cout << "String input so far: "<< prefix <<" is ACCEPTED\n";
		else
			cout << "String input so far: "<< prefix <<" is NOT ACCEPTED\n";

		printf("Current State: %d,", state);
		char symbol = S[i];
		if ( dfa[state].find(symbol) == dfa[state].end() )
		{
			printf("  Unkown Symbol: %c", symbol);
			break;
		}
		printf("  Current Symbol: %c\n", symbol);
		state = dfa[state][symbol];

		if ( i == S.length() - 1 && state == final_state)
			accepted = true;
	}

	if ( accepted )
		printf("\nFinal Status: String Succesfully Accepted\n");
	else
		printf("\nFinal Status: String Not Accepted\n");
}
