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

