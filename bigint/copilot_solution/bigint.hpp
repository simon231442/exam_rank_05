#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <iostream>
#include <string>

class bigint
{
private:
	std::string str;
	bigint(const std::string& value);

	static std::string normalize(const std::string& value);
	static std::string add_strings(const std::string& lhs, const std::string& rhs);
	static int compare_strings(const std::string& lhs, const std::string& rhs);
	static unsigned long long parse_count(const std::string& value);
	static std::string shift_left(const std::string& value, unsigned long long count);
	static std::string shift_right(const std::string& value, unsigned long long count);

public:
	bigint();
	bigint(unsigned int num);
	bigint(const bigint& source);
	bigint& operator=(const bigint& source);
	~bigint();

	std::string getStr() const;

	bigint operator+(const bigint& other) const;
	bigint& operator+=(const bigint& other);

	bigint operator<<(unsigned int n) const;
	bigint operator>>(unsigned int n) const;
	bigint& operator<<=(unsigned int n);
	bigint& operator>>=(unsigned int n);
	bigint operator<<(const bigint& other) const;
	bigint operator>>(const bigint& other) const;
	bigint& operator<<=(const bigint& other);
	bigint& operator>>=(const bigint& other);

	bigint& operator++();
	bigint operator++(int);

	bool operator==(const bigint& other) const;
	bool operator!=(const bigint& other) const;
	bool operator<(const bigint& other) const;
	bool operator>(const bigint& other) const;
	bool operator<=(const bigint& other) const;
	bool operator>=(const bigint& other) const;
};

std::ostream& operator<<(std::ostream& output, const bigint& obj);

#endif
