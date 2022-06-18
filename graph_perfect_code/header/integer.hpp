#pragma once

#include <iostream>
#include <string>
#include <random>
#include <dynamic_array.hpp>

using int64 = long long;

class integer {

private:

    std::string num_string;
    bool sign;

public:

    //Constructors:
    integer(long long n = 0);

    integer(const std::string&);

    integer(const char*);

    integer(const integer&);

    integer(integer&&)noexcept;

    integer& operator=(const integer&)noexcept;

    integer& operator = (integer&&)noexcept;

    //Helper Functions:

    friend void divide_by_2(integer& a);

    friend bool Null(const integer&);

    friend int Length(const integer&);

    int operator[](const int)const;

    /* * * * Operator Overloading * * * */

//Direct assignment

   

    //Post/Pre - Incrementation

    integer& operator++();

    integer operator++(int temp);

    integer& operator--();

    integer operator--(int temp);

    //Addition and Subtraction

    friend integer& operator+=(integer&, const integer&);

    friend integer operator+(const integer&, const integer&);

    friend integer operator-(const integer&, const integer&);

    friend integer& operator-=(integer&, const integer&);

    //Comparison operators

    friend bool operator==(const integer&, const integer&);

    friend bool operator!=(const integer&, const integer&);

    friend bool operator>(const integer&, const integer&);

    friend bool operator>=(const integer&, const integer&);

    friend bool operator<(const integer&, const integer&);

    friend bool operator<=(const integer&, const integer&);

    //Multiplication and Division

    friend integer& operator*=(integer&, const integer&);

    friend integer operator*(const integer&, const integer&);

    friend integer& operator/=(integer&, const integer&);

    friend integer operator/(const integer&, const integer&);

    //Modulo

    friend integer operator%(const integer&, const integer&);

    friend integer& operator%=(integer&, const integer&);

    //Power Function

    friend integer& operator^=(integer&, const integer&);

    friend integer operator^(const integer&, const integer&);

    //Square Root Function

    friend integer sqrt(integer& a);

    //Read and Write

    friend std::ostream& operator<<(std::ostream&, const integer&);

    friend std::istream& operator>>(std::istream&, integer&);

    //Others

    friend integer NthCatalan(int n);

    friend integer NthFibonacci(int n);

    friend integer Factorial(int n);

    friend integer pow(const integer& a, const integer& b);

    friend integer pow(const integer& a, const int& b);
};

integer::integer(const std::string& s) {
    num_string = "";
    int limit;

    if (s[0] == '-') {
        sign = true; limit = 1;
    }
    else if (s[0] == '+') {
        sign = false; limit = 1;
    }
    else {
        sign = false; limit = 0;
    }

    int n = (int)s.size();
    for (int i = n - 1; i >= limit; i--) {
        if (!isdigit(s[i]))
            throw("ERROR");
        num_string.push_back(s[i] - '0');
    }
}

integer::integer(long long nr) {
    if (nr < 0) {
        sign = true;
        nr = -nr;
    }
    else sign = false;
    do {
        num_string.push_back(nr % 10);
        nr /= 10;
    } while (nr);
}

integer::integer(const char* s) {
    num_string = "";
    int limit;

    if (s[0] == '-') {
        sign = true; limit = 1;
    }
    else if (s[0] == '+') {
        sign = false; limit = 1;
    }
    else {
        sign = false; limit = 0;
    }
    for (int i = (int)strlen(s) - 1; i >= limit; i--)
    {
        if (!isdigit(s[i]))
            throw("ERROR");
        num_string.push_back(s[i] - '0');
    }
}

integer::integer(const integer& a) {
    num_string = a.num_string;
    sign = a.sign;
}

integer::integer(integer&& a)noexcept
{
    num_string = std::move(a.num_string);
    sign = a.sign;
}

integer& integer::operator = (const integer& that)noexcept
{
    if (this == &that)
    {
        return *this;
    }
    num_string = that.num_string;
    sign = that.sign;

    return *this;
}

integer& integer::operator = (integer&& that)noexcept
{
    if (this == &that)
    {
        return *this;
    }

    num_string = std::move(that.num_string);
    sign = that.sign;

    return *this;
}

bool Null(const integer& a) {
    if (a.num_string.size() == 1 && a.num_string[0] == 0)
        return true;
    return false;
}

int Length(const integer& a) {
    return (int)a.num_string.size();
}

int integer::operator[](const int index)const {
    if (num_string.size() <= index || index < 0)
        throw("ERROR");
    return num_string[index];
}

bool operator==(const integer& a, const integer& b) {
    return a.num_string == b.num_string && a.sign == b.sign;
}

bool operator!=(const integer& a, const integer& b) {
    return !(a == b);
}

bool operator<(const integer& a, const integer& b) {
    if (a.sign > b.sign) return true;
    if (a.sign < b.sign) return false;

    int n = Length(a), m = Length(b);
    if (n != m)
        return n < m;
    while (n--)
        if (a.num_string[n] != b.num_string[n])
            return a.num_string[n] < b.num_string[n];
    return false;
}

bool operator>(const integer& a, const integer& b) {
    return b < a;
}

bool operator>=(const integer& a, const integer& b) {
    return !(a < b);
}

bool operator<=(const integer& a, const integer& b) {
    return !(a > b);
}

integer& integer::operator++() {
    if (sign) {
        sign = false;
        --(*this);
        if (*this != 0ll) sign = true;
        return *this;
    }
    int i, n = (int)num_string.size();
    for (i = 0; i < n && num_string[i] == 9; i++)
        num_string[i] = 0;
    if (i == n)
        num_string.push_back(1);
    else
        num_string[i]++;
    return *this;
}

integer integer::operator++(int temp) {
    integer aux;
    aux = *this;
    ++(*this);
    return aux;
}

integer& integer::operator--() {
    if (sign) {
        sign = false;
        ++(*this);
        sign = true;
        return *this;
    }
    if (num_string[0] == 0 && num_string.size() == 1) {
        ++(*this); sign = true; return *this;
    }
    int i, n = (int)num_string.size();
    for (i = 0; num_string[i] == 0 && i < n; i++)
        num_string[i] = 9;
    num_string[i]--;
    if (n > 1 && num_string[n - 1] == 0)
        num_string.pop_back();
    return *this;
}

integer integer::operator--(int temp) {
    integer aux;
    aux = *this;
    --(*this);
    return aux;
}

integer& operator+= (integer& a, const integer& x) {
    integer b = x;
    if (!a.sign && !b.sign) {
        int t = 0, s, i;
        int n = Length(a), m = Length(b);
        if (m > n)
            a.num_string.append(m - n, 0);
        n = Length(a);
        for (i = 0; i < n; i++) {
            if (i < m)
                s = (a.num_string[i] + b.num_string[i]) + t;
            else
                s = a.num_string[i] + t;
            t = s / 10;
            a.num_string[i] = (s % 10);
        }
        if (t)
            a.num_string.push_back(t);
    }
    else if (!a.sign && b.sign) {
        b.sign = false;
        a -= b;
        b.sign = true;
    }
    else if (a.sign && !b.sign) {
        a.sign = false;
        if (b > a) a = b - a;
        else if (a > b) {
            a = b - a; a.sign = true;
        }
        else a = 0ll;
    }
    else if (a.sign && b.sign) {
        a.sign = false;
        b.sign = false;
        a += b;
        a.sign = true;
        b.sign = true;
    }
    return a;
}

integer operator+(const integer& a, const integer& b) {
    integer temp;
    temp = a;
    temp += b;
    return temp;
}

integer& operator-=(integer& a, const integer& y) {
    integer b = y;
    if (a > b) {
        if (!a.sign && !b.sign) {
            int n = Length(a), m = Length(b);
            int i, t = 0, s;
            for (i = 0; i < n; i++) {
                if (i < m)
                    s = a.num_string[i] - b.num_string[i] + t;
                else
                    s = a.num_string[i] + t;
                if (s < 0)
                    s += 10,
                    t = -1;
                else
                    t = 0;
                a.num_string[i] = s;
            }
            while (n > 1 && a.num_string[n - 1] == 0)
                a.num_string.pop_back(),
                n--;
        }
        else if (a.sign && b.sign) {
            a.sign = false; b.sign = false;
            a -= b;
            a.sign = true; b.sign = true;
        }
        else if (!a.sign && b.sign) {
            b.sign = false;
            a += b;
            b.sign = true;
        }
    }
    else if (a < b) {
        if (!a.sign && !b.sign) {
            a = b - a;
            a.sign = true;
        }
        else if (a.sign && !b.sign) {
            a.sign = false;
            a += b;
            a.sign = true;
        }
        else if (a.sign && b.sign) {
            a.sign = false; b.sign = false;
            a += b;
            a.sign = true; b.sign = true;
        }
    }
    else a = 0ll;

    return a;
}

integer operator-(const integer& a, const integer& b) {
    integer temp;
    temp = a;
    temp -= b;
    return temp;
}

integer& operator*=(integer& a, const integer& b)
{
    if (Null(a) || Null(b)) {
        a = integer();
        return a;
    }
    int n = (int)a.num_string.size(), m = (int)b.num_string.size();
    std::vector<int> v(n + m, 0);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            v[i + j] += (a.num_string[i]) * (b.num_string[j]);
        }
    n += m;
    a.num_string.resize(v.size());
    for (int s, i = 0, t = 0; i < n; i++)
    {
        s = t + v[i];
        v[i] = s % 10;
        t = s / 10;
        a.num_string[i] = v[i];
    }
    for (int i = n - 1; i >= 1 && !v[i]; i--)
        a.num_string.pop_back();

    if ((a.sign && b.sign) || (!a.sign && !b.sign)) a.sign = false;
    else a.sign = true;
    return a;
}

integer operator*(const integer& a, const integer& b) {
    integer temp;
    temp = a;
    temp *= b;
    return temp;
}

integer& operator/=(integer& a, const integer& b) {
    if (Null(b))
        throw("Arithmetic Error: Division By 0");
    if (a < b) {
        a = integer();
        return a;
    }
    if (a == b) {
        a = integer(1);
        return a;
    }
    int i, lgcat = 0, cc;
    int n = Length(a), m = Length(b);
    std::vector<int> cat(n, 0);
    integer t; integer ten = 10;
    for (i = n - 1; t * ten + a.num_string[i] < b; i--) {
        t *= 10;
        t += a.num_string[i];
    }
    for (; i >= 0; i--) {
        t = t * 10 + a.num_string[i];
        for (cc = 9; cc * b > t; cc--);
        t -= cc * b;
        cat[lgcat++] = cc;
    }
    a.num_string.resize(cat.size());
    for (i = 0; i < lgcat; i++)
        a.num_string[i] = cat[lgcat - i - 1];
    a.num_string.resize(lgcat);
    return a;


    if ((a.sign && b.sign) || (!a.sign && !b.sign)) a.sign = false;
    else a.sign = true;

    return a;
}

integer operator/(const integer& a, const integer& b) {
    integer temp;
    temp = a;
    temp /= b;
    return temp;
}

integer& operator%=(integer& a, const integer& b) {
    if (Null(b))
        throw("Arithmetic Error: Division By 0");
    if (a < b) {
        a = integer();
        return a;
    }
    if (a == b) {
        a = integer(1);
        return a;
    }
    int i, lgcat = 0, cc;
    int n = Length(a), m = Length(b);
    std::vector<int> cat(n, 0);
    integer t;
    for (i = n - 1; t * (integer)10ll + a.num_string[i] < b; i--) {
        t *= (integer)10;
        t += a.num_string[i];
    }
    for (; i >= 0; i--) {
        t = t * (integer)10 + a.num_string[i];
        for (cc = 9; cc * b > t; cc--);
        t -= cc * b;
        cat[lgcat++] = cc;
    }
    a = t;
    return a;
}

integer operator%(const integer& a, integer& b) {
    integer temp;
    temp = a;
    temp %= b;
    return temp;
}

integer& operator^=(integer& a, const integer& b) {
    if (b.sign) throw("ERROR");
    integer Exponent, Base(a);
    Exponent = b;
    a = 1;
    while (!Null(Exponent)) {
        if (Exponent[0] & 1)
            a *= Base;
        Base *= Base;
        divide_by_2(Exponent);
    }
    if (a.sign) if ((b.num_string[0] - '0') % 2 == 0) a.sign = false;
    return a;
}

integer operator^(integer& a, integer& b) {
    integer temp(a);
    temp ^= b;
    return temp;
}

integer pow(const integer& a, const integer& b) {
    integer temp(a);
    temp ^= b;
    return temp;
}

integer pow(const integer& a, const int64& b) {
    integer temp(a);
    integer tmp1(b);
    temp ^= tmp1;
    return temp;
}

void divide_by_2(integer& a) {
    int add = 0;
    for (int i = (int)a.num_string.size() - 1; i >= 0; i--) {
        int digit = (a.num_string[i] >> 1) + add;
        add = ((a.num_string[i] & 1) * 5);
        a.num_string[i] = digit;
    }
    while (a.num_string.size() > 1 && !a.num_string.back())
        a.num_string.pop_back();
}

integer sqrt(integer& a) {
    if (a.sign) throw("ERROR");
    integer left(1), right(a), v(1), mid, prod;
    divide_by_2(right);
    while (left <= right) {
        mid += left;
        mid += right;
        divide_by_2(mid);
        prod = (mid * mid);
        if (prod <= a) {
            v = mid;
            ++mid;
            left = mid;
        }
        else {
            --mid;
            right = mid;
        }
        mid = integer();
    }
    return v;
}

integer NthCatalan(int n) {
    integer a(1), b;
    for (int i = 2; i <= n; i++)
        a *= i;
    b = a;
    for (int i = n + 1; i <= 2 * n; i++)
        b *= i;
    a *= a;
    a *= (n + 1);
    b /= a;
    return b;
}

integer NthFibonacci(int n) {
    integer a(1), b(1), c;
    if (!n)
        return c;
    n--;
    while (n--) {
        c = a + b;
        b = a;
        a = c;
    }
    return b;
}

//Int Factorial(int n) {
//    Int f(1);
//    for (int i = 2; i <= n; i++)
//        f *= i;
//    return f;
//}

std::istream& operator>>(std::istream& cin, integer& a) {
    std::string s; int limit;
    cin >> s;


    if (s[0] == '-') {
        a.sign = true; limit = 1;
    }
    else if (s[0] == '+') {
        a.sign = false; limit = 1;
    }
    else {
        a.sign = false; limit = 0;
    }
    a = s;
    return cin;
}

std::ostream& operator<<(std::ostream& cout, const integer& a) {
    if (a.sign) std::cout << '-';
    for (int i = (int)a.num_string.size() - 1; i >= 0; i--)
        std::cout << (short)a.num_string[i];
    return cout;
}

integer ConvertMessageToInteger(const std::string& message)
{
    std::string num = { '1' }; short len = 0, x, y, z;
    for (char ch : message) {
        len = (short)log10(ch) + 1;
        if (len == 3) {
            z = ch % 10; ch /= 10; y = ch % 10; x = ch / 10;
            num.push_back(x + '0'); num.push_back(y + '0'); num.push_back(z + '0');
        }
        else if (len == 2) {
            z = ch % 10; y = ch / 10; x = 0;
            num.push_back(x + '0'); num.push_back(y + '0'); num.push_back(z + '0');
        }
        else if (len == 1) {
            z = ch; y = 0; x = 0;
            num.push_back(x + '0'); num.push_back(y + '0'); num.push_back(z + '0');
        }
    }
    integer Tmp = num;
    return Tmp;
}

std::string ConvertIntegerToMessage(integer& num)
{
    std::string Tmp;
    for (int i = Length(num) - 2; i >= 0; i -= 3)
        Tmp.push_back(100 * num[i] + 10 * num[i - 1] + num[i - 2]);
    return Tmp;
}

inline integer random_integer(int64 len)
{
    std::string str; str.reserve(len + 1);

    std::random_device engine;

    std::mt19937 genaretor(engine());

    std::uniform_int_distribution<> dist_int('0', '9'); // distribution in range [start, end]

    std::uniform_int_distribution<> dist_bool(0, 1);

    if (dist_bool(genaretor))
    {
        str.push_back('-');
    }
    else
    {
        str.push_back('+');
    }

    for (int64 i = 0; i < len; ++i)
    {
        str.push_back(dist_int(genaretor));
    }

    return integer(str);
}

inline dynamic_array<int64> random_int(int64 start, int64 end, int64 n)
{
    std::random_device device;

    std::mt19937 rng(device());

    std::uniform_int_distribution<int64> dist(start, end); // distribution in range [start, end]

    dynamic_array<int64> Tmp(n);

    int64* data = Tmp.data();

    for (int64 i = 0; i < n; ++i)
    {
        *(data + i) = dist(rng);
    }

    return Tmp;
}


class Int : private dynamic_array<bool>
{

};

std::vector<bool> x; 

