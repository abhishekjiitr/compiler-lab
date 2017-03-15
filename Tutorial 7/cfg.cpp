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
        int S;
        bool change;
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
            change = false;
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
            if ( not change )
                change = sz1 != sz2;
        }
        void computeFirst()
        {
            // printFirst();
            // cout << "CALLED\n";
            change = false;
            for(int i=0; i<256; i++)
            {
                vector<string> res = R[i];
                for(int j=0; j<res.size() ; j++)
                {
                    // cout << char(i) <<" -> " << res[j] <<endl;
                    addFirst(i, j, 0);
                }
            }
            if ( change )
            {
                // cout << "CHANGED\n";
                computeFirst();
            }
        }
};

int main()
{
    CFG gmr;
    gmr.addStartVariable('A');
    gmr.addProduction('A', "B|d");
    gmr.addProduction('B', "ac|{");
    gmr.computeFirst();
    gmr.printFirst();
}