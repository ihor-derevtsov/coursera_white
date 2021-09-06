#include <iostream>
#include <exception>
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
        if (denominator == 0) { throw invalid_argument("Denominator is 0 :("); }
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

// Вставьте сюда реализацию operator / для класса Rational
Rational operator/(const Rational& lhs, const Rational& rhs) {
    if (rhs.Numerator() == 0) { throw domain_error("Denominator is 0 :("); }
    int new_rhs_num = rhs.Denominator();
    int new_rhs_den = rhs.Numerator();
    int new_num = lhs.Numerator() * new_rhs_num;
    int new_den = lhs.Denominator() * new_rhs_den;
    return Rational(new_num, new_den);
}

int main() {
    try {
        Rational r(1, 0);
        cout << "Doesn't throw in case of zero denominator" << endl;
        return 1;
    } catch (invalid_argument&) {
    }

    try {
        auto x = Rational(1, 2) / Rational(0, 1);
        cout << "Doesn't throw in case of division by zero" << endl;
        return 2;
    } catch (domain_error&) {
    }

    cout << "OK" << endl;
    return 0;
}
