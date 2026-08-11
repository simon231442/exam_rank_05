/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   bigint.hpp                                          :+:    :+:           */
/*                                                      +:+                   */
/*   By: srenaud <marvin@42.fr>                        +#+                    */
/*                                                    +#+                     */
/*   Created: 2026/08/11 14:48:56 by srenaud        #+#    #+#                */
/*   Updated: 2026/08/11 14:48:59 by srenaud        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIGINT_HPP
# define BIGINT_HPP

# include <iostream>
# include <string>

class bigint
{
	public:
		bigint();
		bigint(unsigned int n);

		bigint		operator+(bigint const & rhs) const;
		bigint&		operator+=(bigint const & rhs);

		bigint		operator<<(unsigned long long n) const;
		bigint		operator>>(unsigned long long n) const;
		bigint&		operator<<=(unsigned long long n);
		bigint&		operator>>=(unsigned long long n);
		bigint		operator<<(bigint const & n) const;
		bigint		operator>>(bigint const & n) const;
		bigint&		operator<<=(bigint const & n);
		bigint&		operator>>=(bigint const & n);

		bigint&		operator++();
		bigint		operator++(int);

		bool		operator==(bigint const & rhs) const;
		bool		operator!=(bigint const & rhs) const;
		bool		operator>(bigint const & rhs) const;
		bool		operator>=(bigint const & rhs) const;
		bool		operator<(bigint const & rhs) const;
		bool		operator<=(bigint const & rhs) const;

		friend std::ostream&	operator<<(std::ostream & os, bigint const & n);

	private:
		std::string	digits_;

		static std::string			add(std::string const & a, std::string const & b);
		static bool					less(std::string const & a, std::string const & b);
		static unsigned long long	toULL(std::string const & s);
};


