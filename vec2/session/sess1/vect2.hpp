#ifndef VECT2_HPP
# define VECT2_HPP

# include <vector>
# include <iostream>

class vect2 {
	private :
		std::vector<int>	container_;
	public :
		vect2();
		vect2(int v1, int v2);
		vect2(vect2 const & original);

		~vect2();

		vect2&	operator=(vect2 const & rhs);

		vect2	operator+(vect2 const & rhs) const;
		vect2	operator-(vect2 const & rhs) const;
		vect2	operator*(int scalar) const;

		int		getContainer_elements(int index) const;
	};

std::iostream&	operator<<(std::iostream& out, vect2 const & v);

#endif
