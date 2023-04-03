//-----------------------------------------------------------------------------
/***
    Author: Nicholas Barsi-Rhyne
    CruzID: nbarsirh
    Assignment: pa6

    BigInteger.cpp: This file contains the implementation of my List ADT IN C++.
***/
//-----------------------------------------------------------------------------

#include<iostream>
#include<string>
#include<stdexcept>
#include"BigInteger.h"

const long BASE = 1000000000;
const int POWER = 9;

// Class Constructors & Destructors -------------------------------------------

// BigInteger()
// Constructor that creates a new BigInteger in the zero state: 
// signum=0, digits=().
BigInteger::BigInteger() {
    digits.insertAfter(0);
    signum = 0;
}

// BigInteger()
// Constructor that creates a new BigInteger from the string s.
// Pre: s is a non-empty string consisting of (at least one) base 10 digit
// {0,1,2,3,4,5,6,7,8,9}, and an optional sign {+,-} prefix.
BigInteger::BigInteger(std::string s) {
    if (s.empty()) {
        throw std::invalid_argument("BigInteger: Constructor: empty string");
    }
    if (s.size() == 1 && !isdigit(s[0]))
        throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
    int counter = 0;
    std::string temp;
    for (int i = s.size() - 1; i > 0; i--) {
        if (!isdigit(s[i])) {
            throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
        }
        temp = s[i] + temp;
        counter++;
        if (counter == POWER) {
            double num;
            num = std::stol(temp);
            digits.insertAfter(num);
            counter = 0;
            temp = "";
        }
    }
    if (s[0] == '-')
        signum = -1;
    else
        signum = 1;
    if (s[0] == '-' || s[0] == '+') {
        int remain = (s.size() - 1) % POWER;
        if (remain != 0) {
            double num;
            num = std::stol(temp);
            digits.insertAfter(num);
        }
    }
    else {
        temp = s[0] + temp;
        double num;
        num = std::stol(temp);
        digits.insertAfter(num);
    }
    digits.moveFront();
    while (digits.moveNext() == 0) {
        if (digits.length() == 1)
            break;
        digits.eraseBefore();
    }
}

// BigInteger()
// Constructor that creates a copy of N.
BigInteger::BigInteger(const BigInteger& N) {
    signum = N.signum;
    digits = N.digits;
}
// Access functions -----------------------------------------------------------

// sign()
// Returns -1, 1 or 0 according to whether this BigInteger is negative, 
// positive or 0, respectively.
int BigInteger::sign() const {
    return signum;
}

// absCompare()
// Returns 1, 1, or 0 according to whether List A is greater than, less
// than or equal to B.
int absCompare(List& A, List& B)  {
    if (A.length() > B.length())
        return 1;
    if (A.length() < B.length())
        return -1;
    else {
        A.moveFront();
        B.moveFront();
        while (A.position() != A.length()) {
            long a = A.moveNext();
            long b = B.moveNext();
            if (a > b)
                return 1;
            if (a < b)
                return -1;
        }
        return 0;
    }
}

// compare()
// Returns -1, 1 or 0 according to whether this BigInteger is less than N,
// greater than N or equal to N, respectively.
int BigInteger::compare(const BigInteger& N) const {
    List tempN = N.digits;
    List temp = digits;
    if (temp.length() < tempN.length() && signum == 1 && N.signum == 1)
        return -1;
    if (temp.length() > tempN.length() && signum == 1 && N.signum == 1)
        return 1;
    if (temp.length() > tempN.length() && signum == -1 && N.signum == -1)
        return -1;
    if (temp.length() < tempN.length() && signum == -1 && N.signum == -1)
        return 1;
    if (signum == -1 && N.signum == 1)
        return -1;
    if (signum == 1 && N.signum == -1)
        return 1;
    else {
        temp.moveFront();
        tempN.moveFront();
        for (int i = 0; i < temp.length(); i++) {
            double t1 = temp.moveNext();
            double t2 = tempN.moveNext();
            if (t1 < t2 && signum == 1)
                return -1;
            if (t1 < t2 && signum == -1)
                return 1;
            if (t1 > t2 && signum == 1)
                return 1;
            if (t1 > t2 && signum == -1)
                return -1;
        }
        return 0;
    }
}

// Manipulation procedures ----------------------------------------------------

// makeZero()
// Re-sets this BigInteger to the zero state.
void BigInteger::makeZero() {
    digits.clear();
    digits.insertAfter(0);
    signum = 0;
}

// negateList()
// Changes the sign of each integer in List L. Used by sub(). 
void negateList(List& L) {
    L.moveFront();
    for (int i = 0; i <L.length(); i++) {
        L.setBefore(-L.moveNext());
    }
}

// negate()
// If this BigInteger is zero, does nothing, otherwise reverses the sign of 
// this BigInteger positive <--> negative.
void BigInteger::negate() {
    if (signum != 0)
        signum *= -1;
}

// normalizeList()
// Performs carries from right to left (least to most significant // digits), 
// Used // by add(), sub() and mult().
void normalizeList(List& L) {
    // std::cout << "List L = " + L.to_string() << std::endl;
    L.moveBack();
    int carry = 0;
    for (int i = 0; i < L.length(); i++) {
        long l = L.movePrev() + carry;
        if (l == 0) {
            L.setAfter(l);
            carry = 0;
            continue;
        }

        if (l >= BASE) {
            L.setAfter(l % BASE);
            carry = l / BASE;
            continue;
        }
        if (l < 0) {
            long value = (BASE + (l % BASE)) % BASE;
            L.setAfter(value);
            if (l > -BASE)
                carry = -1;
            else
                carry = l / BASE;
            continue;
        }
        else {
            L.setAfter(l);
            carry = 0;
        }
    }
    if (carry < 0) {
        L.insertAfter(-carry);
    }
    if (carry > 0) {
        L.insertAfter(carry);
    }
    while (L.moveNext() == 0) {
        if (L.length() == 1)
            break;
        L.eraseBefore();
    }
}

// sumList()
// Overwrites the state of S with A + sgn*B (considered as vectors). 
// Used by both sum() and sub() and mult().
void sumList(List& S, List A, List B, int sgn) {
    S.clear();
    A.moveBack();
    B.moveBack();
    S.moveFront();
    for (int i = A.position(); i > 0; i--) {
        if (B.position() == 0)
            break;
        long a = A.movePrev();
        long b = B.movePrev();
        long s = a + sgn * b;
        S.insertAfter(s);
    }
    if (A.position() != 0) {
        for (int i = A.position(); i > 0; i--) {
            S.insertAfter(A.movePrev());
        }
    }
    if (B.position() != 0) {
        for (int i = B.position(); i > 0; i--) {
            S.insertAfter(B.movePrev());
        }
    }
}

// add()
// Returns a BigInteger representing the sum of this and N.
BigInteger BigInteger::add(const BigInteger& N) const {
    List A = digits;
    List B = N.digits;
    BigInteger S;
    if (signum == 0) {
        S = N;
        return S;
    }
    if (N.signum == 0) {
        S.digits = digits;
        S.signum = signum;
        return S;
    }
    if (signum == 1 && N.signum == 1) {
        sumList(S.digits ,A, B, 1);
        S.signum = 1;
    }
    if (signum == -1 && N.signum == -1) {
        sumList(S.digits, A, B, 1);
        S.signum = -1;
    }
    if ((signum == -1 && N.signum == 1) || (signum == 1 && N.signum == -1)) {
        int i = absCompare(A, B);
        if (i == 1){
            sumList(S.digits, A, B, -1);
            if (signum == 1)
                S.signum = 1;
            if (signum == -1)
                S.signum = -1;
        }
        else {
            sumList(S.digits, B, A, -1);
            if (N.signum == 1)
                S.signum = 1;
            if (N.signum == -1)
                S.signum = -1;
        }
    }
    normalizeList(S.digits);
    S.digits.moveFront();
    if (S.digits.peekNext() == 0)
        S.signum = 0;
    return S;
}

// sub()
// Returns a BigInteger representing the difference of this and N.
BigInteger BigInteger::sub(const BigInteger& N) const {
    List A = digits;
    List B = N.digits;
    BigInteger S;

    if (signum == 1 && N.signum == -1) {
        sumList(S.digits, A, B, 1);
        S.signum = 1;
    }
    if (signum == -1 && N.signum == 1) {
        sumList(S.digits, A, B, 1);
        S.signum = -1;
    }
    if ((signum == -1 && N.signum == -1) || (signum == 1 && N.signum == 1)) {
        int i = absCompare(A, B);
        if (i == 1){
            sumList(S.digits, A, B, -1);
            if (signum == 1)
                S.signum = 1;
            if (signum == -1)
                S.signum = -1;
        }
        else {
            sumList(S.digits, B, A, -1);
            if (N.signum == 1)
                S.signum = -1;
            if (N.signum == -1)
                S.signum = 1;
        }
    }
    normalizeList(S.digits);
    S.digits.moveFront();
    if (S.digits.peekNext() == 0)
        S.signum = 0;
    return S;
}

// shiftList()
// Prepends p zero digits to L, multiplying
void shiftList(List& L, int p) {
    L.moveBack();
    for (int i = 0; i < p; i++)
        L.insertAfter(0);
}

// scalarMultList()
// Multiplies L (considered as a vector) by
List scalarMultList(List& L, ListElement m) {
    List S;
    L.moveFront();
    for (int i = 0; i < L.length(); i++) {
        S.insertAfter(L.moveNext() * m);
        S.moveNext();
    }
    return S;
}

// mult()
// Returns a BigInteger representing the product of this and N. 
BigInteger BigInteger::mult(const BigInteger& N) const {
    List A = digits;
    List B = N.digits;
    List temp = A;
    List temp2;
    BigInteger S;
    A.moveFront();
    B.moveFront();
    if (A.peekNext() == 0 || B.peekNext() == 0)
        return S;
    int shifter = 0;

    A.moveBack();
    B.moveBack();

    while (A.position() > 0) {
        int val = A.movePrev();
        temp = scalarMultList(B, val);
        shiftList(temp, shifter);
        temp2 = S.digits;
        sumList(S.digits, temp2, temp, 1);
        normalizeList(S.digits);
        shifter++;
    }
    if ((N.signum == 1 && signum == 1) || (N.signum == -1 && signum == -1))
        S.signum = 1;
    else
        S.signum = -1;
    normalizeList(S.digits);
    return S;
}

// Other Functions ------------------------------------------------------------

// to_string()
// Returns a string representation of this BigInteger consisting of its
// base 10 digits. If this BigInteger is negative, the returned string 
// will begin with a negative sign '-'. If this BigInteger is zero, the
// returned string will consist of the character '0' only.
std::string BigInteger::to_string() {
    std::string temp = "";
    // std::cout << "to_string" + digits.to_string() << std::endl;
    digits.moveFront();
    if (signum == -1) {
        temp = "-";
    }
    // std::cout << digits << std::endl;
    std::string strnum = std::to_string(digits.moveNext());
    temp = temp + strnum;
    for (int i = 0; i < digits.length() - 1; i++) {
        std::string strnum = std::to_string(digits.moveNext());
        if (strnum.length() != POWER) {
            for (int i = strnum.length(); i < POWER; i++) {
                strnum = "0" + strnum;
            }
        }
        temp = temp + strnum;
    }
    return temp;
}
// Overloaded Operators -------------------------------------------------------

// operator<<()
// Inserts string representation of N into stream.
std::ostream& operator<<( std::ostream& stream, BigInteger N ) {
    return stream << N.BigInteger::to_string();
}

// operator==()
// Returns true if and only if A equals B. 
bool operator==( const BigInteger& A, const BigInteger& B ) {
    if (A.BigInteger::compare(B) == 0)
        return true;
    return false;

}

// operator<()
// Returns true if and only if A is less than B. 
bool operator<( const BigInteger& A, const BigInteger& B ) {
    if (A.BigInteger::compare(B) == -1)
        return true;
    return false;
}

// operator<=()
// Returns true if and only if A is less than or equal to B. 
bool operator<=( const BigInteger& A, const BigInteger& B ) {
    if (A.BigInteger::compare(B) == -1 || A.BigInteger::compare(B) == 0)
        return true;
    return false;
}

// operator>()
// Returns true if and only if A is greater than B. 
bool operator>( const BigInteger& A, const BigInteger& B ) {
    if (A.BigInteger::compare(B) == 1)
        return true;
    return false;
}

// operator>=()
// Returns true if and only if A is greater than or equal to B. 
bool operator>=( const BigInteger& A, const BigInteger& B ) {
    if (A.BigInteger::compare(B) == 1 || A.BigInteger::compare(B) == 0)
        return true;
    return false;
}

// operator+()
// Returns the sum A+B. 
BigInteger operator+( const BigInteger& A, const BigInteger& B ) {
    BigInteger S = A.BigInteger::add(B);
    return S;
}

// operator+=()
// Overwrites A with the sum A+B. 
BigInteger operator+=( BigInteger& A, const BigInteger& B ) {
    BigInteger S = A.BigInteger::add(B);
    A = S;
    return A;
}

// operator-()
// Returns the difference A-B. 
BigInteger operator-( const BigInteger& A, const BigInteger& B ) {
    BigInteger S = A.BigInteger::sub(B);
    return S;
}

// operator-=()
// Overwrites A with the difference A-B. 
BigInteger operator-=( BigInteger& A, const BigInteger& B ) {
    BigInteger S = A.BigInteger::sub(B);
    A = S;
    return A;
}

// operator*()
// Returns the product A*B. 
BigInteger operator*( const BigInteger& A, const BigInteger& B ) {
    BigInteger S = A.BigInteger::mult(B);
    return S;
}

// operator*=()
// Overwrites A with the product A*B. 
BigInteger operator*=( BigInteger& A, const BigInteger& B ) {
    BigInteger S = A.BigInteger::mult(B);
    A = S;
    return A;
}
