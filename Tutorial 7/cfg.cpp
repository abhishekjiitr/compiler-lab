#include <iostream>
#include <stdio.h>
#include <vector>
#include <set>
#include <algorithm>
#include <iterator>
using namespace std;

#define eps '{'

class CFG
{
    public:
        set<char> FIRST[256], FOLLOW[256];
        vector<string> R[256];
        char S;
        bool changeFirst, changeFollow;
        int T[256], V[256];
        void printFirst()
        {
            cout << "FIRST SET\n";
            for(int i=0;i<256;i++)
            {
                set<char> fst = FIRST[i];
                set<char>::iterator it;
                if ( R[i].size() )
                {
                    cout << char(i) << ": ";
                    if (fst.size())
                        {           
                            for(it=fst.begin(); it != fst.end() ;it++)
                                cout << *it << " ";
                        }
                    cout << endl;
                }
            }
        }
        void printFollow()
        {
            cout << "FOLLOW SET\n";
            for(int i=0;i<256;i++)
            {
                set<char> fst = FOLLOW[i];
                set<char>::iterator it;
                if ( R[i].size() )
                {
                    cout << char(i) << ": ";
                    if (fst.size())
                        {           
                            for(it=fst.begin(); it != fst.end() ;it++)
                                cout << *it << " ";
                        }
                    cout << endl;
                }
            }
        }
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
            }
            changeFirst = false;
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
        void addFirst(int i, int j, int index)
        {
            if ( index >= R[i][j].size() )
                return;
            int sz1 = FIRST[i].size();
            char c = R[i][j][index];
            if ( not isUpper(c) )
            {
                FIRST[i].insert(c);
            }
            else
            {
                set<char> uni, a = FIRST[i], b = FIRST[c];
                    set_union (a.begin(), a.end(),
                               b.begin(), b.end(),
                               inserter(uni, uni.begin()));

                if ( b.find(eps) != b.end() )
                {
                    uni.erase(eps);
                    FIRST[i] = uni;
                    if ( index == R[i][j].size()-1 )
                        FIRST[i].insert(eps);
                    else
                        addFirst(i, j, index+1);
                    
                }
                else
                {
                    FIRST[i] = uni;
                }
            }
            int sz2 = FIRST[i].size();
            if ( not changeFirst )
                changeFirst = sz1 != sz2;
        }
        void computeFirst()
        {
            // printFirst();
            // cout << "CALLED\n";
            changeFirst = false;
            for(int i=0; i<256; i++)
            {
                vector<string> res = R[i];
                for(int j=0; j<res.size() ; j++)
                {
                    // cout << char(i) <<" -> " << res[j] <<endl;
                    addFirst(i, j, 0);
                }
            }
            if ( changeFirst )
            {
                // cout << "CHANGED\n";
                computeFirst();
            }
        }
        void addFollow(int v, int i, int j, int k)
        {
            int sz1 = FOLLOW[v].size();
            vector<string> res = R[i];
            string currentRule = res[j];
            if ( k == currentRule.length() )
                {
                    set<char> uni, a = FOLLOW[v], b = FOLLOW[i];
                        set_union (a.begin(), a.end(),
                                   b.begin(), b.end(),
                                   inserter(uni, uni.begin()));
                    FOLLOW[v] = uni;
                    return;
                }
            if( k > currentRule.length() )
                return;
            char c = currentRule[k];
            if ( not isUpper(c) )
            {
                FOLLOW[v].insert(c);
            }
            else
            {
                set<char> uni, a = FOLLOW[v], b = FIRST[c];
                    set_union (a.begin(), a.end(),
                               b.begin(), b.end(),
                               inserter(uni, uni.begin()));
                if ( b.find(eps) != b.end() )
                {
                    uni.erase(eps);
                    FOLLOW[v] = uni;
                    if (  k == currentRule.length()-1 )
                        {
                            set<char> uni, a = FOLLOW[v], b = FOLLOW[i];
                                set_union (a.begin(), a.end(),
                                           b.begin(), b.end(),
                                           inserter(uni, uni.begin()));
                            FOLLOW[v] = uni;
                        }
                    else
                        addFirst(i, j, k+1);
                    
                }
                else
                {
                    FOLLOW[v] = uni;
                }
            }
            int sz2 = FOLLOW[v].size();
            if ( not changeFollow )
                changeFollow = sz1 != sz2;
        }
        void computeFollow()
        {
            changeFollow = false;
            for(int v=0;v<256;v++)
            {
                if ( V[v] )
                {
                    for(int i=0;i<256;i++)
                    {
                        vector<string> res = R[i];
                        for(int j=0; j < res.size(); j++)
                        {
                            string currentRule = res[j];
                            for(int k=0; k < currentRule.size() ; k++)
                            {
                                // cout << currentRule[k];
                                if ( currentRule[k] == v )
                                {
                                    addFollow(v, i, j, k+1);
                                }
                            }
                        }
                    }
                }
            }
            if ( changeFollow )
            {
                computeFollow();
            }
        }
};

int main()
{
    CFG gmr;
    gmr.addStartVariable('S');
    gmr.addProduction('S', "xyz|aBC");
    gmr.addProduction('B', "c|cd");
    gmr.addProduction('C', "eg|df");
    gmr.printTerminals();
    gmr.printVariables();
    gmr.computeFirst();
    gmr.printFirst();
    gmr.computeFollow();
    gmr.printFollow();
}