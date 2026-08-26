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
vect2				vect2::operator-(vect2 const & rhs) const
{
	return vect2(container_[0] - rhs.container_[0],
				container_[1] - rhs.container_[1]);
}
vect2				vect2::operator*(int scalar) const
{
	return  vect2(container_[0] * scalar, container_[1] * scalar);
}
                                                         
vect2&				vect2::operator+=(vect2 const & rhs)
{
	container_[0] += rhs.container_[0];
	container_[1] += rhs.container_[1];
	return *this;
}
vect2&				vect2::operator-=(vect2 const & rhs)
{
	container_[0] -= rhs.container_[0];
	container_[1] -= rhs.container_[1];
	return *this;
}
vect2&				vect2::operator*=(int scalar)
{
	container_[0] *= scalar;
	container_[1] *= scalar;
	return *this;
}
                                                         
vect2&				vect2::operator++()
{
	container_[0]++;
	container_[1]++;
	return *this;
}
vect2				vect2::operator++(int)
{
	vect2	tmp(*this);

	++(*this);
	return tmp;
}
vect2&				vect2::operator--()
{
	container_[0]--;
	container_[1]--;
	return *this;
}
vect2				vect2::operator--(int)
{
	vect2	tmp(*this);

	--(*this);
	return tmp;
}
                                                         
bool				vect2::operator==(vect2 const & rhs) const
{
	return container_[0] == rhs.container_[0] && container_[1] == rhs.container_[1];
}
bool				vect2::operator!=(vect2 const & rhs) const
{
	return !(*this == rhs);
}



vect2						operator*(int scalar, vect2 const & rhs)
{
	return rhs * scalar;
}
std::ostream&				operator<<(std::ostream& out, vect2 const & rhs)
{
	out << "{" << rhs[0] << ", " <<rhs[1] << "}";
	return out;
}
