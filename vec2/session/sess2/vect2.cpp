#include "vect2.hpp"

vect2::vect2() {}

vect2::vect2(int x, int y) : container_{x, y} {}

vect2::vect2(vect2 const & src) : container_{src.container_[0], src.container_[1]} {}

vect2&		vect2::operator=(vect2 const & rhs)
{
	if (this != &rhs)
	{
		this->container_[0] = rhs.container_[0];
		this->container_[1] = rhs.container_[1];
	}
	return *this;
}

vect2::~vect2() {}

int	main(void)
{
	return 0;
}
