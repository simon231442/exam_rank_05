#ifndef BIGINT_HPP
# define BIGINT_HPP

# include <iostream>
# include <string>

// Invariant : _digits est une chaine de chiffres decimaux, jamais vide,
// sans zero non significatif, sauf la valeur "0" elle-meme.
class bigint
{
	public:
		bigint();
		bigint(unsigned int n);
		// Pas de destructeur / copie / affectation ecrits a la main :
		// le seul membre est un std::string, celles generees
		// implicitement par le compilateur (Rule of Zero) sont deja
		// correctes. `= default` n'existe qu'a partir de C++11 ;
		// en C++98 on obtient le meme resultat en ne les declarant
		// pas du tout.

		bigint  operator+(const bigint& rhs) const;
		bigint& operator+=(const bigint& rhs);

		bigint  operator<<(unsigned long long n) const;
		bigint  operator>>(unsigned long long n) const;
		bigint& operator<<=(unsigned long long n);
		bigint& operator>>=(unsigned long long n);
		bigint  operator<<(const bigint& n) const;
		bigint  operator>>(const bigint& n) const;
		bigint& operator<<=(const bigint& n);
		bigint& operator>>=(const bigint& n);

		bigint& operator++();
		bigint  operator++(int);

		bool operator==(const bigint& rhs) const;
		bool operator!=(const bigint& rhs) const;
		bool operator<(const bigint& rhs)  const;
		bool operator>(const bigint& rhs)  const;
		bool operator<=(const bigint& rhs) const;
		bool operator>=(const bigint& rhs) const;

		friend std::ostream& operator<<(std::ostream& os, const bigint& n);

	private:
		std::string _digits;

		static std::string        add(const std::string& a, const std::string& b);
		static bool                less(const std::string& a, const std::string& b);
		static unsigned long long toULL(const std::string& s);
};

#endif
