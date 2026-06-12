#include "bigint.hpp"

#include <climits>
#include <sstream>

static std::string reverse_string(const std::string& value)
{
	std::string result;
	for (std::string::size_type i = value.size(); i > 0; --i)
		result.push_back(value[i - 1]);
	return (result);
}

std::string bigint::normalize(const std::string& value)
{
	std::string::size_type index = 0;
	while (index < value.size() && value[index] == '0')
		++index;
	if (index == value.size())
		return ("0");
	return (value.substr(index));
}

std::string bigint::add_strings(const std::string& lhs, const std::string& rhs)
{
	std::string left = reverse_string(lhs);
	std::string right = reverse_string(rhs);
	std::string result;
	std::size_t max_len = left.size() > right.size() ? left.size() : right.size();
	int carry = 0;

	for (std::size_t i = 0; i < max_len || carry != 0; ++i)
	{
		int digit_left = (i < left.size()) ? left[i] - '0' : 0;
		int digit_right = (i < right.size()) ? right[i] - '0' : 0;
		int sum = digit_left + digit_right + carry;
		result.push_back(static_cast<char>('0' + (sum % 10)));
		carry = sum / 10;
	}
	return (normalize(reverse_string(result)));
}

int bigint::compare_strings(const std::string& lhs, const std::string& rhs)
{
	if (lhs.size() < rhs.size())
		return (-1);
	if (lhs.size() > rhs.size())
		return (1);
	if (lhs == rhs)
		return (0);
	return (lhs < rhs ? -1 : 1);
}

unsigned long long bigint::parse_count(const std::string& value)
{
	unsigned long long count = 0;
	for (std::string::size_type i = 0; i < value.size(); ++i)
	{
		unsigned int digit = static_cast<unsigned int>(value[i] - '0');
		if (count > (ULLONG_MAX - digit) / 10)
			return (ULLONG_MAX);
		count = count * 10 + digit;
	}
	return (count);
}

std::string bigint::shift_left(const std::string& value, unsigned long long count)
{
	if (value == "0")
		return ("0");
	std::string result = value;
	result.append(static_cast<std::string::size_type>(count), '0');
	return (normalize(result));
}

std::string bigint::shift_right(const std::string& value, unsigned long long count)
{
	if (count >= value.size())
		return ("0");
	return (normalize(value.substr(0, value.size() - static_cast<std::string::size_type>(count))));
}

bigint::bigint() : str("0")
{
}

bigint::bigint(unsigned int num)
{
	std::string value;
	if (num == 0)
		value = "0";
	else
	{
		while (num > 0)
		{
			value.push_back(static_cast<char>('0' + (num % 10)));
			num /= 10;
		}
		value = reverse_string(value);
	}
	str = normalize(value);
}

bigint::bigint(const std::string& value) : str(normalize(value))
{
}

bigint::bigint(const bigint& source) : str(source.str)
{
}

bigint& bigint::operator=(const bigint& source)
{
	if (this != &source)
		str = source.str;
	return (*this);
}

bigint::~bigint()
{
}

std::string bigint::getStr() const
{
	return (str);
}

bigint bigint::operator+(const bigint& other) const
{
	return (bigint(add_strings(str, other.str)));
}

bigint& bigint::operator+=(const bigint& other)
{
	str = add_strings(str, other.str);
	return (*this);
}

bigint bigint::operator<<(unsigned int n) const
{
	return (bigint(shift_left(str, n)));
}

bigint bigint::operator>>(unsigned int n) const
{
	return (bigint(shift_right(str, n)));
}

bigint& bigint::operator<<=(unsigned int n)
{
	str = shift_left(str, n);
	return (*this);
}

bigint& bigint::operator>>=(unsigned int n)
{
	str = shift_right(str, n);
	return (*this);
}

bigint bigint::operator<<(const bigint& other) const
{
	return (*this << parse_count(other.str));
}

bigint bigint::operator>>(const bigint& other) const
{
	return (*this >> parse_count(other.str));
}

bigint& bigint::operator<<=(const bigint& other)
{
	return (*this <<= parse_count(other.str));
}

bigint& bigint::operator>>=(const bigint& other)
{
	return (*this >>= parse_count(other.str));
}

bigint& bigint::operator++()
{
	return (*this += bigint(1));
}

bigint bigint::operator++(int)
{
	bigint temp(*this);
	++(*this);
	return (temp);
}

bool bigint::operator==(const bigint& other) const
{
	return (str == other.str);
}

bool bigint::operator!=(const bigint& other) const
{
	return (!(*this == other));
}

bool bigint::operator<(const bigint& other) const
{
	return (compare_strings(str, other.str) < 0);
}

bool bigint::operator>(const bigint& other) const
{
	return (compare_strings(str, other.str) > 0);
}

bool bigint::operator<=(const bigint& other) const
{
	return (compare_strings(str, other.str) <= 0);
}

bool bigint::operator>=(const bigint& other) const
{
	return (compare_strings(str, other.str) >= 0);
}

std::ostream& operator<<(std::ostream& output, const bigint& obj)
{
	output << obj.getStr();
	return (output);
}
