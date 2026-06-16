#ifndef VECT2_HPP
# define VECT2_HPP

# include <vector>
# include <iostream>

class	vect2 {
	private :
		std::vector<int>	_container;
	public :
		vect2();
		vect2(int x, int y);
		vect2(vect2 const & src);

		vect2&				operator=(vect2 const & rhs);

		int					operator[](int index) const;
		int&				operator[](int index);

		vect2				operator-() const;//opérateur unaire moins (Négation)
		vect2				operator*(int scalar) const;

		vect2				operator*=(int scalar);
		vect2				operator*=(vect2 const & rhs);
		vect2				operator+=(vect2 const & rhs);// pourquoi de += un scalaire ?
		vect2				operator-=(vect2 const & rhs);

		~vect2();
	};

int			operator*(int scalar, vect2 const & rhs);
