#pragma once

#include <iostream>

class vect2 {
	private:
		int x;
		int y;

	public:
		vect2();
		vect2(int n1, int n2);
		vect2(const vect2& src);
		vect2& operator=(const vect2& src);
		~vect2();

		int		operator[](int i) const;			// lecture seule
		int&	operator[](int i);					// lecture + ecriture

		vect2	operator-() const;					// -v

		vect2	operator*(int n) const;				// v * 2
		vect2&	operator*=(int n);					// v *= 2

		vect2&	operator+=(const vect2& o);
		vect2&	operator-=(const vect2& o);
		vect2	operator+(const vect2& o) const;
		vect2	operator-(const vect2& o) const;

		vect2&	operator++();						// ++v
		vect2	operator++(int);					// v++
		vect2&	operator--();
		vect2	operator--(int);

		bool	operator==(const vect2& o) const;
		bool	operator!=(const vect2& o) const;
};

vect2			operator*(int n, const vect2& o);	// 3 * v
std::ostream&	operator<<(std::ostream& os, const vect2& o);
