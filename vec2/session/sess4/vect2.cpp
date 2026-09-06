#include "vect2.hpp"

vect2::vect2() : vec_(2, 0)
{

}
vect2::vect2(int x, int y)
{
	vec_[0] = x;
	vec_[1] = y;
}
vect2::vect(vect2 const & src)
{
	vec_[0] = src.vec_[0];
	vec_[1] = src.vec_[1];
}
vect2::~vect2()
{

}
vect2			vect2::operator=(vect2 const & rhs)
{
	if (this != rhs)
	{
		vec_[0] = src.vec_[0];
		vec_[1] = src.vec_[1];
	}
	return *this;
}

vect2			vect2::operator+(vect2 const & rhs)
{
	return (vect2(this->vec_[0] + rhs.vec_[0], this->vec_[1] + rhs.vec_[1]);
}
vect2			vect2::operator-(vect2 const & rhs)
{
	return (vect2(this->vec_[0] - rhs.vec_[0], this->vec_[1] - rhs.vec_[1]);
}
vect2			vect2::operator*(int scalar)
{
	return (vect2(this->vec_[0] * scalar, this->vec_[1] * scalar);
}

vect2			vect2::operator++(int)
{
	
	return tmp;
}
vect2			vect2::operator++()
{

}
vect2			vect2::operator--(int)
{

}
vect2			vect2::operator--()
{

}

vect2			vect2::operator+=(vect2 const & rhs)
{

}
vect2			vect2::operator-=(vect2 const & rhs)
{

}
vect2			vect2::operator*=(int scalar
{

}

vect2 &			vect2::operator[](int index
{

}
vect2			vect2::operator[](int index
{

}

std::ostream	vect2::operator<<(std::ostream out; vect2 vec)
{

}
vect2			vect2::operator*(int scalar)
{

}
vect2			vect2::operator+(int scalar)
{

}

