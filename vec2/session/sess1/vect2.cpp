#include "vect2.hpp"
#include <stdexcept>

vect2::vect2() : container_(2,0) {}

vect2::vect2(int v1, int v2) : container_(2) {
	container_[0] = v1;
	container_[1] = v2;
}

vect2::vect2(vect2 const & original) : container_(original.container_) {}

vect2::~vect2() {}

vect2&		vect2::operator=(vect2 const & rhs) {
	if (this != &rhs)
		container_ = rhs.container_;
	return *this;
}

vect2		vect2::operator+(vect2 const & rhs) const {
	return vect2(container_[0] + rhs.container[0], container_[1] + rhs.container[1]);
}

vect2		vect2::operator-(vect2 const & rhs) const {
	return vect2(container_[0] - rhs.container[0], container_[1] - rhs.container[1]);
}

vect2		vect2::operator*(int scalar) const {
	return vect2(container_[0] * scalar, container_[1] * scalar);
}

int			vect2::getContainer_elements(int index) const {
	if (index < 0 || index > 1)
		throw std::out_of_range("index must be between 0 1");
	return static<int>(container_[index]);
}



