#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <set>

using namespace std;

void AddWords(map<string, set<string> >& dict);
void CountSin(map<string, set<string> >& dict);
void CheckSin(map<string, set<string> >& dict);


int main () 
{
    map<string, set<string> > dict;
    set<string> sin;
    int n;
    cin >> n;
    for (int i{0}; i < n; ++i)
    {
        string request;
        cin >> request;
        if (request == "ADD") { AddWords(dict); }
        else if (request == "COUNT") { CountSin(dict); }
        else if (request == "CHECK") { CheckSin(dict); }
        else 
        {
            cout << "ERROR" << endl;
            --i;
        }
    }
    return 0;
}

void AddWords(map<string, set<string> >& dict)
{
    string w1, w2;
    cin >> w1 >> w2;
    dict[w1].insert(w2);
    dict[w2].insert(w1);
}

void CountSin(map<string, set<string> >& dict)
{
    string word;
    cin >> word;
    cout << dict[word].size() << endl;
}

void CheckSin(map<string, set<string> >& dict)
{
    bool indicator{false};
    string w1, w2;
    cin >> w1 >> w2;
    if (dict[w1].count(w2)) { cout << "YES" << endl; }
    else 
    {
        cout << "NO" << endl;
    }
}