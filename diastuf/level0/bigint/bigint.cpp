#include "bigint.hpp"

bigint	bigint::operator+(const bigint& o) const {
	std::string a = _n, b = o._n;

	while (a.size() < b.size())
		a = "0" + a;
	while (b.size() < a.size())
		b = "0" + b;

	int 		carry = 0;
	std::string	res   = a;

	for (int i = (int)a.size() - 1; i >= 0; i--) {
		int sum = (a[i]-'0') + (b[i]-'0') + carry;
		res[i] = sum % 10 + '0';
		carry = sum / 10;
	}

	if (carry)
		res = char('0' + carry) + res;

	bigint ret;
	ret._n = res;
	return ret;
}

bigint	bigint::operator<<(unsigned int n) const {
	bigint ret = *this;

	ret._n.append(n, '0');

	return ret;
}

bigint	bigint::operator>>(unsigned int n) const {
	bigint ret = *this;

	if (n >= ret._n.size())
		ret._n = "0";
	else
		ret._n.erase(ret._n.size() - n, n);
	
	return ret;
}

static unsigned int toUInt(const std::string& s) {
	std::stringstream ss(s);
	unsigned int n;

	ss >> n;
	return n;
}

bigint	bigint::operator<<(const bigint& o) const {
	return *this << toUInt(o._n);
}

bigint	bigint::operator>>(const bigint& o) const {
	return *this >> toUInt(o._n);
}

bigint&	bigint::operator<<=(const bigint& o) {
	return *this = *this << toUInt(o._n);
}

bigint&	bigint::operator>>=(const bigint& o) {
	return *this = *this >> toUInt(o._n);
}

bool	bigint::operator<(const bigint& o) const {
	if (_n.size() != o._n.size())
		return (_n.size() < o._n.size());
	return _n < o._n;
}

std::ostream&	operator<<(std::ostream& os, const bigint& o) {
	return os << o.str();
}


















