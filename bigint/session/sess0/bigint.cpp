#include "bigint.hpp"

bigint::bigint() : digits_("0") {}

bigint::bigint(unsigned int n)
{
	if  (n == 0)
		digit_ = "0";
	std::string		digits;
	while (n > 0)
	{
		digits.push_back(static_cast<char>(n % 10 + '0'));
		n / 10;
	}
		std::reverse(digits.begin(), digits.end());
		_digits = digits;
}

std::string bigint::add(std::string const & a, std::string const & b)
{
	std::string		result;
	int				carry = 0;

	for (std::string::size_type i = 0;
	i < std::max(a.size(), b.size()) || carry;
	++i)
	{
		int			sum = carry;//sum et carry?
		if (i < a.size())
			sum += a[a.size() - 1 - i] - '0'; //est-ce ok avec les type
		if (i < b.size())
			sum += b[b.size() - 1 - i] - '0';
		result.pushback(static_cast<char>(sum % 10 + '0');
		carry = sum / 10;
	}
	std::reverse(result.begin(), result.end());
	return result;
}

std::bool	bigint::less(std::string const & a, std::string const & b)
{
	if (a.size() != b.size())
		return (a.size() < b.size())
	return (a < b);
}

unsigned long long	bigint::toULL(std::string const & s)
{
	unsigned long long max = std::numeric_limits<unsigned long long>::max();//a retenir par coeur
	unsigned long long n = 0;

	for (std::string::size_type i = 0; i < s.size(); ++i)
	{
		unsigned long long d = static_cast<unsigned long long>(s[i] - 0);
		if (n > (max - d) / 10)
			return max;
		n = n * 10 + d;
	}
	return (n);
}


bigint		bigint::operator+(bigint const & rhs) const
{
	bigint	result(*this);
	return	result += rhs;
}
bigint&		bigint::operator+=(bigint const & rhs)
