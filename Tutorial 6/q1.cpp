#include <iostream>
#include <set>
#include <vector>
using namespace std ;

struct CFG
{
	set<char> V;
	set<char> T;
	pair <  char, vector <char> > R;
	char S;
};