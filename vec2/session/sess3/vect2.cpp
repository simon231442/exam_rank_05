#include "vect2.hpp"

vect2::vect2() : container_(2, 0) {}
vect2::vect2(int x, int y) : container_(2)
{
	this->container_[0] = x;
	this->container_[1] = y;
}
vect2::vect2(vect2 const & src) : container_(src.container_) {}
vect2::~vect2() {}
                                                         
vect2&				vect2::operator=(vect2 const & rhs)
{
	if (this != &rhs)
		this->container_ = rhs.container_;
	return *this;
}

int					vect2::operator[](int index) const
{
	return this->container_[index];
}
int&				vect2::operator[](int index)
{
	return this->container_[index];
}
                                                        
vect2				vect2::operator-() const
{
	return vect2(-container_[0], -container_[1]);
}

vect2				vect2::operator+(vect2 const & rhs) const
{
	return vect2(container_[0] + rhs.container_[0],
				container_[1] + rhs.container_[1]);
}
vect2				vect2::operator-(vect2 const & rhs) const;
{
	return vect2(container_[0] - rhs.container_[0],
				container_[1] - rhs.container_[1]);
}
vect2				vect2::operator*(int scalar) const
{
	return  vect2(-container_[0] * scalar, container_[1] * scalar);
}
                                                         
vect2&				vect2::operator+=(vect2 const & rhs);
vect2&				vect2::operator-=(vect2 const & rhs);
vect2&				vect2::operator*=(int scalar);
                                                         
vect2&				vect2::operator++();
vect2&				vect2::operator++(int);
vect2&				vect2::operator--();
vect2&				vect2::operator--(int);
                                                         
bool				vect2::operator==(vect2 const & rhs) const;
bool				vect2::operator!=(vect2 const & rhs) const;
