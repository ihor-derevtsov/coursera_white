#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std;

int GCD(int u, int v) {
    while (v != 0) {
            int r = u % v;
            u = v;
            v = r;
        }
    return u;
}

int findNOK (int u, int v) {
    if (v != 0) {
        return (u*v / GCD(u, v));
    }
    else return 0;
}

class Rational {
public:
    Rational() {
        num = 0;
        den = 1;
    }

    Rational(int numerator, int denominator) {
        int NOD = GCD(numerator, denominator);

        if (NOD == 1) { 
            num = numerator; 
            den = denominator; 
        }
        else {
            num = numerator / NOD;
            den = denominator / NOD;
        }
        if(den < 0 && num > 0 || den < 0 && num < 0) { num = -num; den = -den; }
        else if (num == 0) { den = 1; };
    }

    int Numerator() const {
        return num;
    }

    int Denominator() const {
        return den;
    }

private:
    int num;
    int den;
};

bool operator==(const Rational& lhs, const Rational& rhs) {
    return (lhs.Numerator() == rhs.Numerator() && lhs.Denominator() == rhs.Denominator());
}

// Реализуйте для класса Rational оператор(ы), необходимые для использования его
// в качестве ключа map'а и элемента set'а
Rational operator/(const Rational& lhs, const Rational& rhs) {
    if(rhs.Numerator() != 0 && lhs.Denominator() != 0) {
        int new_rhs_num = rhs.Denominator();
        int new_rhs_den = rhs.Numerator();
        int new_num = lhs.Numerator() * new_rhs_num;
        int new_den = lhs.Denominator() * new_rhs_den;
        return Rational(new_num, new_den);
    }
}


Rational operator-(const Rational& lhs, const Rational& rhs) {
    if (lhs.Denominator() == rhs.Denominator()) {
        int new_num = lhs.Numerator() - rhs.Numerator();
        int new_den = lhs.Denominator();
        return Rational(new_num, new_den);
    }
    else {
        int NOK = findNOK(lhs.Denominator(), rhs.Denominator());
        int for_lhs = NOK / lhs.Denominator();
        int for_rhs = NOK / rhs.Denominator();
        int new_num = lhs.Numerator() * for_lhs - rhs.Numerator() * for_rhs;
        return Rational(new_num, NOK);
    }
}


bool operator<(const Rational& lhs, const Rational& rhs) {
    
    Rational res = lhs - rhs;
    return (res.Numerator() < 0);
    
}

int main() {
    {
        const set<Rational> rs = {{1, 2}, {1, 25}, {3, 4}, {3, 4}, {1, 2}};
        if (rs.size() != 3) {
            cout << "Wrong amount of items in the set" << endl;
            return 1;
        }

        vector<Rational> v;
        for (auto x : rs) {
            v.push_back(x);
        }
        if (v != vector<Rational>{{1, 25}, {1, 2}, {3, 4}}) {
            cout << "Rationals comparison works incorrectly" << endl;
            return 2;
        }
    }

    {
        map<Rational, int> count;
        ++count[{1, 2}];
        ++count[{1, 2}];

        ++count[{2, 3}];

        if (count.size() != 2) {
            cout << "Wrong amount of items in the map" << endl;
            return 3;
        }
    }

    cout << "OK" << endl;
    return 0;
}
