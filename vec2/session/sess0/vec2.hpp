#ifndef VEC2_HPP
# define VEC2_HPP

#include <iostream>
#include <vector>

class vec2 {
	private :
		std::vector<int>	container_;

	public :
		vec2(int v1, int v2);
		vec2(vec2 const & src);
		~vec2();

		vec2 &				operator=(vec2 const & rhs);
		vec2				operator+(vec2 const & other) const;
		vec2				operator-(vec2 const & other) const;
		vec2				operator*(int scalar) const;
		int					getContainer_elements(vec2 const & v) const;
	};

std::ostream &				operator<<(std::ostream & out, vec2 const & v);

#endif
