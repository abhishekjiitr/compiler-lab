#include <iostream>
#include <stdio.h>
#include <vector>
#include <set>
#include <algorithm>
#include <iterator>
#include <stack>
#define myit set<char>::iterator
using namespace std;

#define eps '{'
#define id 'x'

class CFG
{
    public:
        stack<char> lrstack;
        vector< pair<char, string>  > myrules; 
        set<char> FIRST[256], FOLLOW[256];
        vector<string> R[256];
        char S;
        bool changeFirst, changeFollow, parsingTable;
        string lrtable[256][256];
        int T[256], V[256];
        void printTerminals()
        {
            cout << "Terminals: ";
            for(int i=0; i<256; i++)
            {
                if (T[i])
                    cout << char(i) << " ";
            }
            cout << endl;
        }
        void printVariables()
        {
            cout << "Variables: ";
            for(int i=0; i<256; i++)
            {
                if (V[i])
                    cout << char(i) << " ";
            }
            cout << endl;
        }
        bool isUpper(char c)
        {
            return c >= 'A' and c <= 'Z';
        }
        CFG()
        {
            for(int i=0 ; i<256 ; i++)
            {
                T[i] = 0; V[i] = 0;
                for(int j=0; j<256; j++)
                    lrtable[i][j] = "";
            }
            changeFirst = false;
            parsingTable = true;
        }
        vector<string> mysplit(string s)  // splits the string using '|' as a separator
        {
          vector<string> result;
          int n = s.length();
          int i = 0;
          string current = "";
          while ( i < n )
          {
            if ( s[i] == '|' )
            {
              result.push_back(current);
              current = "";
            }
            else
              current += s[i];
            i++;
          }
          result.push_back(current);
          return result;
        }
        void addStartVariable(char S)
        {
            this -> S = S;
            FOLLOW[S].insert('$');

        }
        void addProduction(char A, string s)
        {
            vector<string> res = mysplit(s);
            // cout << res.size() << endl;

            for(int i=0; i<res.size() ; i++)
            {
                myrules.push_back(make_pair(A, res[i]));
            }
            R[A] = res;
            V[A] = 1;
            for(int i=0; i<s.length() ; i++)
            {
                char c = s[i];
                if ( c != '|' )
                {
                    if ( isUpper(c) )
                        V[c] = 1;
                    else T[c] = 1;
                }
            }
        }
        void printSet(set<char> myset)
        {
            set<char>::iterator it;
            for(it = myset.begin() ; it != myset.end() ; it++)
            {
                cout << *it << " ";
            }
            cout << endl;
        }
        void printLRTable()
        {
            cout << "\nOPERATOR PRECEDENCE PARSING TABLE\n";
            cout << "   ";
            for(int i=0;i<256;i++)
            {
                if ( (T[i] || i == '$') and i != '{' )
                    cout << char(i) << "  ";
            }
            cout << endl;
            for(int i=0; i<256 ; i++)
            {
                if ( (T[i] || i == '$') and i != '{'  )
                {
                    cout << char(i) << " ";
                    for(int j=0; j<256 ; j++)
                    {
                        if ( (T[j] || j == '$') and j != eps)
                        {
                            // cout << lrtable[i][j] << " ";
                            cout << lrtable[i][j] << " ";
                        }
                    }
                    cout << endl;
                }
            }
            cout << endl;
        }

        bool parse(string s)
        {
            bool possible = false;
            s += "$";
            lrstack.push('0');
            int i=0;
            while ( i < s.length() )
            {
                char curr = lrstack.top();
                cout << "Stack: " << char(curr)<< ", String: " << s[i] << endl;
                char strsymbol = s[i];
                string res = lrtable[curr][strsymbol];
                if ( res.compare("accept") == 0 )
                    {
                        possible = true;
                        break;
                    }
                if ( res.length() == 1 )
                {
                    // GOTO
                    int next = res[0]-48;
                }
                else if ( res[0] == 's' )
                {
                    char next = res[1];
                    lrstack.push(strsymbol);
                    lrstack.push(next);
                        i++;
                }
                else if ( res[0] == 'r' )
                {
                    char next = res[1], symbol;
                    pair<char, string> myrule = myrules[next-49];
                    int reductions = myrule.second.length();
                    cout << "Reducing using rule: " << myrule.first << " -> " << myrule.second << endl;
                    while ( reductions )
                    {
                        lrstack.pop();
                        lrstack.pop();
                        reductions--;
                    }
                    char prev = lrstack.top();
                    lrstack.push(myrule.first);
                    char next_state = lrtable[prev][myrule.first][0];
                    lrstack.push(next_state);
                }
            }
        }
        void constructLRTable()
        {
            lrtable['0']['a'] = "s3";
            lrtable['0']['b'] = "s4";
            lrtable['0']['A'] = "2";
            lrtable['0']['S'] = "1";

            lrtable['1']['$'] = "accept";
    
            lrtable['2']['a'] = "s3";
            lrtable['2']['b'] = "s4";
            lrtable['2']['A'] = "5";


            lrtable['3']['a'] = "s3";
            lrtable['3']['b'] = "s4";
            lrtable['3']['A'] = "6";

            lrtable['4']['a'] = "r3";
            lrtable['4']['b'] = "r3";
            lrtable['4']['$'] = "r3";

            lrtable['5']['a'] = "r1";
            lrtable['5']['b'] = "r1";
            lrtable['5']['$'] = "r1";

            lrtable['6']['a'] = "r2";
            lrtable['6']['b'] = "r2";
            lrtable['6']['$'] = "r2";

        }
};

int main()
{
    CFG gmr;
    gmr.addStartVariable('S');
    gmr.addProduction('S', "AA");
    gmr.addProduction('A', "aA|b");
    gmr.printTerminals();
    gmr.printVariables();
    gmr.constructLRTable();
    // gmr.printLRTable();
    string inp = "aabb";
    if ( gmr.parse(inp) )
        cout << "String Parsed Successfully\n";
    else
        cout << "Cannot Parse given string\n";
}