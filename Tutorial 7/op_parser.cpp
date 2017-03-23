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
        stack<char> opstack;
        set<char> FIRST[256], FOLLOW[256];
        vector<string> R[256];
        char S;
        bool changeFirst, changeFollow, parsingTable;
        int optable[256][256];
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
                    optable[i][j] = 0;
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
        void printOPTable()
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
                            // cout << optable[i][j] << " ";
                            printf("%2d ", optable[i][j]);
                        }
                    }
                    cout << endl;
                }
            }
            cout << endl;
        }

        bool parse(string s)
        {
            s += "$";
            opstack.push('$');

            {
                char curr = opstack.top();

                if ( optable[curr][s[i]] < 0 )
                {

                }
                else if ( optable[curr][s[i]] > 0 )
                {
                    
                }
            }

        }
        void constructOPTable()
        {
            optable[id][id] = 0;
            optable[id]['+'] = 1;
            optable[id]['*'] = 1;
            optable[id]['$'] = 1;

            optable['+'][id] = -1;
            optable['+']['+'] = 1;
            optable['+']['*'] = -1;
            optable['+']['$'] = 1;

            optable['*'][id] = -1;
            optable['*']['+'] = 1;
            optable['*']['*'] = 1;
            optable['*']['$'] = 1;


            optable['$'][id] = -1;
            optable['$']['+'] = -1;
            optable['$']['*'] = -1;
            optable['$']['$'] = 0;
        }
};

int main()
{
    CFG gmr;
    gmr.addStartVariable('E');
    gmr.addProduction('E', "E+E|E*E|x");
    gmr.printTerminals();
    gmr.printVariables();
    gmr.constructOPTable();
    gmr.printOPTable();
    string inp = "x+x*x";
    if ( gmr.parse(inp) )
        cout << "String Parsed Successfully\n";
    else
        cout << "Cannot Parse given string\n";
}