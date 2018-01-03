#ifndef LONGINT_H
#define LONGINT_H

#include <iostream>
#include "deque.h"

using namespace std;

class LongInt {

    /**
     * friend function of LongInt that allow to take input with cin
     * and store it in a LongInt object
     *
     * @param in
     * @param rhs  LongInt
     * @return in
     */
    friend istream &operator>>(istream &in, LongInt &rhs);

    /**
     * friend function of LongInt that overloads the << operator
     *
     * @param out
     * @param rhs
     * @return
     */
    friend ostream &operator<<(ostream &out, const LongInt &rhs);

public:
    // Constructors
    LongInt(const string str);

    //Copy constructor that perform a deep copy
    LongInt( const LongInt &rhs );

    LongInt();

    // Destructor
    ~LongInt();

    // Arithmetic binary operators
    LongInt operator+(const LongInt &rhs) const;

    LongInt operator-(const LongInt &rhs) const;
//
//   // assignment operators
     const LongInt& operator=(const LongInt &rhs);
//
//    // Logical binary operators

     bool operator<(const LongInt &rhs) const;
//
     bool operator<=(const LongInt &rhs) const;
//
     bool operator>(const LongInt &rhs) const;
//
     bool operator>=(const LongInt &rhs) const;
//
     bool operator==(const LongInt &rhs) const;
//
     bool operator!=(const LongInt &rhs) const;


private:

    //private instance variables of LongInt
    Deque<char> digits;
    bool negative;

    //remove leading 0s from a number
    void remove0s();
};

#endif
