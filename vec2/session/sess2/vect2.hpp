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

		vect2&				operator=(vect2 const & rhs);	// v1 = v2;

		int					operator[](int index) const;	// x = v[0];
		int&				operator[](int index);			// v[1] = y;

		vect2				operator-() const;//opérateur unaire moins (Négation) // v1 = -v2
		vect2				operator*(int scalar) const;	// v2 = v1 * 3;

		vect2				operator*=(int scalar);			// v *= 3;
		//vect2				operator*=(vect2 const & rhs);	// v1 *= v2;
		vect2				operator+=(vect2 const & rhs);	// v1 += v2;
		vect2				operator-=(vect2 const & rhs);	// v1 -= v2;

		vect2&				operator++();					//++v; pourquoi ici &
		vect2				operator++(int);				//v++; et pas la ???
		vect2&				operator--();					//--v;
		vect2				operator--();

		bool				operator==(vect2 const& rhs) const; // bool = (v1 == v2)
		bool				operator!=(vect2 const& rhs) const; // bool = (v1 != v2)


		~vect2();
	};

int			operator*(int scalar, vect2 const & rhs);
std::ostream&				operator<<(std::ostream& out, vect2 const & rhs);

#endif
