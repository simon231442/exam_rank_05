#ifndef VECT2_HPP
# define VECT2_HPP

# include <vector>
# include <iostream>

class	vect2 {
	private :
		std::vector<int>	container_;
	public :
		vect2();
		vect2(int x, int y);
		vect2(vect2 const & src);
		~vect2();

		vect2&				operator=(vect2 const & rhs);

		int					operator[](int index) const;
		int&				operator[](int index);

		vect2				operator-() const;

		vect2				operator+(vect2 const & rhs) const;
		vect2				operator-(vect2 const & rhs) const;
		vect2				operator*(int scalar) const;

		vect2&				operator+=(vect2 const & rhs);
		vect2&				operator-=(vect2 const & rhs);
		vect2&				operator*=(int scalar);

		vect2&				operator++();
		vect2&				operator++(int);
		vect2&				operator--();
		vect2&				operator--(int);

		bool				operator==(vect2 const & rhs) const;
		bool				operator!=(vect2 const & rhs) const;
};

vect2						operator*(int scalar, vect2 const & rhs);
std::ostream&				operator<<(std::ostream& out, vect2 const & rhs);

#endif




