#ifndef VECT2_HPP
# define VECT2_HPP

#include <iostream>
#include <vector>

class vect2 {
	public :
		std::vector<int>		vec_;

		vect2();
		vect2(int x, int y);
		vect(vect2 const & src);
		~vect2();
		vect2			operator=(vect2 const & rhs);

		vect2			operator+(vect2 const & rhs);
		vect2			operator-(vect2 const & rhs);
		vect2			operator*(int scalar);
		
		vect2			operator++(int);
		vect2			operator++();
		vect2			operator--(int);
		vect2			operator--();
		
		vect2			operator+=(vect2 const & rhs);
		vect2			operator-=(vect2 const & rhs);
		vect2			operator*=(int scalar)
		
		vect2 &			operator[](int index)
		vect2			operator[](int index)
	friend :
		std::ostream	operator<<(std::ostream out; vect2 vec);
		vect2			operator*(int scalar);
		vect2			operator+(int scalar);
	};
	
