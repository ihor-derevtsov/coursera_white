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
        if (denominator == 0) { throw invalid_argument("Invalid argument"); }
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

Rational operator/(const Rational& lhs, const Rational& rhs) {
    if (rhs.Numerator() == 0) { throw domain_error("Division by zero"); }
    int new_rhs_num = rhs.Denominator();
    int new_rhs_den = rhs.Numerator();
    int new_num = lhs.Numerator() * new_rhs_num;
    int new_den = lhs.Denominator() * new_rhs_den;
    return Rational(new_num, new_den);
}

Rational operator*(const Rational& lhs, const Rational& rhs) {
    int new_num = lhs.Numerator() * rhs.Numerator();
    int new_den = lhs.Denominator() * rhs.Denominator();
    return Rational(new_num, new_den);
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

bool operator<(const Rational& lhs, const Rational& rhs) {
    
    Rational res = lhs - rhs;
    return (res.Numerator() < 0);
}

bool operator==(const Rational& lhs, const Rational& rhs) {
    return (lhs.Numerator() == rhs.Numerator() && lhs.Denominator() == rhs.Denominator());
}

ostream& operator<<(ostream& stream, const Rational& object) {
    stream << object.Numerator() << "/" << object.Denominator();
    return stream;
}

istream& operator>>(istream& stream, Rational& object) {
    int num{0}, num2{0};
    char slash;
    stream >> num;
    stream >> slash;
    stream >> num2;
    if (slash == '/' && stream) { object = {num, num2}; } 
    return stream;
}

Rational MakeOperation(const Rational& lhs, const Rational& rhs, const char& operation) {
    if (operation == '+') { return lhs + rhs; }
    else if (operation == '-') { return lhs - rhs; }
    else if (operation == '*') { return lhs * rhs; }
    else { return lhs / rhs; }
}


int main() {
    int x{0}, y{0};
    char slash;
    try {
        cin >> x;
        cin.ignore(1);
        cin >> y;
        Rational obj1(x, y);
        cin >> slash;
        cin >> x;
        cin.ignore(1);
        cin >> y;
        Rational obj2(x, y);
        cout << MakeOperation(obj1, obj2, slash);
    }
    catch (exception& ex) {
        cout << ex.what() << endl;
    }
    
    return 0;
}