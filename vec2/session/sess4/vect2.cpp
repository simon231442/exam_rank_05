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

vect2			vect2::operator+(vect2 const & rhs) const
{
	return (vect2(this->vec_[0] + rhs.vec_[0], this->vec_[1] + rhs.vec_[1]);
}

vect2			vect2::operator-(vect2 const & rhs) const
{
	return (vect2(this->vec_[0] - rhs.vec_[0], this->vec_[1] - rhs.vec_[1]);
}

vect2			vect2::operator*(int scalar) const
{
	return (vect2(this->vec_[0] * scalar, this->vec_[1] * scalar);
}

vect2			vect2::operator++(int)
{
	vect2	tmp(*this);
	++*this;
	return tmp;
}

vect2			vect2::operator++()
{
	++vec_[0];
	++vec_[1];
	return *this;
}

vect2			vect2::operator--(int)
{
	vect2	tmp(*this);
	--*this;
	return tmp;
}

vect2			vect2::operator--()
{
	++vec_[0];
	++vec_[1];
	return *this;
}

vect2			vect2::operator+=(vect2 const & rhs)
{
	vec_[0] += rhs.vec_[0];
	vec_[1] += rhs.vec_[1];
}

vect2			vect2::operator-=(vect2 const & rhs)
{
	vec_[0] -= rhs.vec_[0];
	vec_[1] -= rhs.vec_[1];
}

vect2			vect2::operator*=(int scalar)
{
	vec_[0] *= rhs.vec_[0];
	vec_[1] *= rhs.vec_[1];
}

vect2 &			vect2::operator[](int index) const
{
	return *this[index];
}

vect2			vect2::operator[](int index) const
{
	return *this[index];
}

std::ostream &	vect2::operator<<(std::ostream out, vect2 vect) const
{
        out << "{" << v[0] << ", " << v[1] << "}" << std::endl;
		return out;
}

vect2			vect2::operator*(int scalar)
{

}

vect2			vect2::operator+(int scalar)
{
}

