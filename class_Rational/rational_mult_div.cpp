#include <iostream>
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

// Реализуйте для класса Rational операторы ==, + и -
bool operator==(const Rational& lhs, const Rational& rhs) {
    return (lhs.Numerator() == rhs.Numerator() && lhs.Denominator() == rhs.Denominator());
}

Rational operator+(const Rational& lhs, const Rational& rhs) {
    if (lhs.Denominator() == rhs.Denominator()) {
        int new_num = lhs.Numerator() + rhs.Numerator();
        int new_den = lhs.Denominator();
        return Rational(new_num, new_den);
    }
    else {
        int NOK = findNOK(lhs.Denominator(), rhs.Denominator());
        int for_lhs = NOK / lhs.Denominator();
        int for_rhs = NOK / rhs.Denominator();
        int new_num = lhs.Numerator() * for_lhs + rhs.Numerator() * for_rhs;
        return Rational(new_num, NOK);
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

// Реализуйте для класса Rational операторы * и /
Rational operator*(const Rational& lhs, const Rational& rhs) {
    int new_num = lhs.Numerator() * rhs.Numerator();
    int new_den = lhs.Denominator() * rhs.Denominator();
    return Rational(new_num, new_den);
}

Rational operator/(const Rational& lhs, const Rational& rhs) {
    int new_rhs_num = rhs.Denominator();
    int new_rhs_den = rhs.Numerator();
    int new_num = lhs.Numerator() * new_rhs_num;
    int new_den = lhs.Denominator() * new_rhs_den;
    return Rational(new_num, new_den);
}


int main() {
    {
        Rational a(2, 3);
        Rational b(4, 3);
        Rational c = a * b;
        bool equal = c == Rational(8, 9);
        if (!equal) {
            cout << "2/3 * 4/3 != 8/9" << endl;
            return 1;
        }
    }

    {
        Rational a(5, 4);
        Rational b(15, 8);
        Rational c = a / b;
        bool equal = c == Rational(2, 3);
        if (!equal) {
            cout << "5/4 / 15/8 != 2/3" << endl;
            return 2;
        }
    }

    cout << "OK" << endl;
    return 0;
}
