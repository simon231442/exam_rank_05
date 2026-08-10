#include "bigint.hpp"

#include <algorithm>
#include <limits>

// Addition posee en base 10, sans jamais copier/inverser les chaines en
// entree : on lit directement depuis la fin via l'index i.
std::string bigint::add(const std::string& a, const std::string& b)
{
	std::string result;
	int carry = 0;

	for (std::string::size_type i = 0; i < std::max(a.size(), b.size()) || carry; ++i)
	{
		int sum = carry;
		if (i < a.size())
			sum += a[a.size() - 1 - i] - '0';
		if (i < b.size())
			sum += b[b.size() - 1 - i] - '0';
		result.push_back(static_cast<char>('0' + sum % 10));
		carry = sum / 10;
	}
	std::reverse(result.begin(), result.end());
	return (result);
}

// Deux nombres normalises se comparent d'abord par longueur, puis
// lexicographiquement seulement a longueur egale.
bool bigint::less(const std::string& a, const std::string& b)
{
	if (a.size() != b.size())
		return (a.size() < b.size());
	return (a < b);
}

// Conversion saturante : jamais d'overflow, meme silencieux.
unsigned long long bigint::toULL(const std::string& s)
{
	const unsigned long long max = std::numeric_limits<unsigned long long>::max();
	unsigned long long n = 0;

	for (std::string::size_type i = 0; i < s.size(); ++i)
	{
		unsigned long long d = static_cast<unsigned long long>(s[i] - '0');
		if (n > (max - d) / 10)
			return (max);
		n = n * 10 + d;
	}
	return (n);
}

bigint::bigint() : _digits("0")
{
}

// std::to_string() est C++11 : en C++98 il faut extraire les chiffres
// a la main, comme dans la version Copilot d'origine.
bigint::bigint(unsigned int n)
{
	if (n == 0)
	{
		_digits = "0";
		return ;
	}
	std::string digits;
	while (n > 0)
	{
		digits.push_back(static_cast<char>('0' + n % 10));
		n /= 10;
	}
	std::reverse(digits.begin(), digits.end());
	_digits = digits;
}

bigint& bigint::operator+=(const bigint& rhs)
{
	_digits = add(_digits, rhs._digits);
	return (*this);
}

bigint bigint::operator+(const bigint& rhs) const
{
	bigint result(*this);
	return (result += rhs);
}

bigint& bigint::operator<<=(unsigned long long n)
{
	if (_digits != "0")
		_digits.append(static_cast<std::string::size_type>(n), '0');
	return (*this);
}

bigint& bigint::operator>>=(unsigned long long n)
{
	// Tronquer par la droite ne peut jamais faire apparaitre un zero
	// non significatif : le premier caractere conserve est celui du
	// nombre d'origine, deja non nul par invariant. Pas besoin de normalize.
	std::string::size_type count = static_cast<std::string::size_type>(n);

	_digits = (count >= _digits.size()) ? "0" : _digits.substr(0, _digits.size() - count);
	return (*this);
}

bigint bigint::operator<<(unsigned long long n) const
{
	bigint result(*this);
	return (result <<= n);
}

bigint bigint::operator>>(unsigned long long n) const
{
	bigint result(*this);
	return (result >>= n);
}

bigint& bigint::operator<<=(const bigint& n) { return (*this <<= toULL(n._digits)); }
bigint& bigint::operator>>=(const bigint& n) { return (*this >>= toULL(n._digits)); }
bigint  bigint::operator<<(const bigint& n) const { return (*this << toULL(n._digits)); }
bigint  bigint::operator>>(const bigint& n) const { return (*this >> toULL(n._digits)); }

bigint& bigint::operator++()
{
	return (*this += bigint(1));
}

bigint bigint::operator++(int)
{
	bigint tmp(*this);
	++(*this);
	return (tmp);
}

bool bigint::operator==(const bigint& rhs) const { return (_digits == rhs._digits); }
bool bigint::operator!=(const bigint& rhs) const { return (!(*this == rhs)); }
bool bigint::operator<(const bigint& rhs)  const { return (less(_digits, rhs._digits)); }
bool bigint::operator>(const bigint& rhs)  const { return (less(rhs._digits, _digits)); }
bool bigint::operator<=(const bigint& rhs) const { return (!(rhs < *this)); }
bool bigint::operator>=(const bigint& rhs) const { return (!(*this < rhs)); }

std::ostream& operator<<(std::ostream& os, const bigint& n)
{
	return (os << n._digits);
}
