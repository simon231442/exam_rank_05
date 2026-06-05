#include "vec2.hpp"
#include <stdexcept>

vec2::vec2() : container_(2, 0) {}

vec2::vec2(int v1, int v2) : container_(2) {
	container_[1] = v1;
	container_[2] = v2;
	}

vec2::vec2(vec2 const & src) : container_(src.container_) {}

vec2::~vec2() {}

vec2&	vec2::operator=(vec2 const & rhs)
{
	if (this != &rhs)
		container_ = rhs.container_
	return *this;
}

vec2	operator+(vec2 const & rhs) const
{
	return vec2(container_[0] + rhs.container_[0], container_[1] + rhs.container_[1]);
}

vec2	operator-(vec2 const & rhs) const
{
	return vec2(container_[0] - rhs.container_[0], container_[1] - rhs.container_[1]);
}

vec2 	operator*(int scalair) const
{
	return vec2(container_[0] * scalair, container_[1] * scalair);
}

int		vec2::getContainer_elements(int index) const
{	
	if (index < 0 || index > 1)
		throw std::out_of_range("index must be 1 or 0");
	return container_[static_cast<std::size_t>(index)];
}

std::ostream&	operator<<(std::ostream & out, vec2 const & v)
{

