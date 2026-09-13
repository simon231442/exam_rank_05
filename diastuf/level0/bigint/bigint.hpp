#pragma once
#include <string>
#include <iostream>
#include <sstream>

class bigint {
    std::string _n;

public:
    bigint() : _n("0")								{}
    bigint(unsigned int n)							{ std::stringstream ss; ss << n; _n = ss.str(); }
    bigint(const bigint& o) : _n(o._n)				{}
    bigint& operator=(const bigint& o) 				{ _n = o._n; return *this; }

    std::string str() const 						{ return _n; }

    bigint  operator+(const bigint& o) const;
    bigint& operator+=(const bigint& o) 			{ return *this = *this + o; }
    bigint& operator++()							{ return *this += bigint(1); }
    bigint  operator++(int)							{ bigint t = *this; ++*this; return t; }

    bigint  operator<<(unsigned int n) const;
    bigint  operator>>(unsigned int n) const;
    bigint& operator<<=(unsigned int n)				{ return *this = *this << n; }
    bigint& operator>>=(unsigned int n)				{ return *this = *this >> n; }

    bigint  operator<<(const bigint& o) const;
    bigint  operator>>(const bigint& o) const;
    bigint& operator<<=(const bigint& o);
    bigint& operator>>=(const bigint& o);

    bool operator==(const bigint& o) const 			{ return _n == o._n; }
    bool operator!=(const bigint& o) const 			{ return !(*this == o); }
    bool operator<(const bigint& o)  const;
    bool operator>(const bigint& o)  const 			{ return o < *this; }
    bool operator<=(const bigint& o) const 			{ return !(o < *this); }
    bool operator>=(const bigint& o) const 			{ return !(*this < o); }
};

std::ostream& operator<<(std::ostream& os, const bigint& b);
