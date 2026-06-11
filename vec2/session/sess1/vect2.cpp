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
		container_ = rhs->container_;
	return *this;
}

vect2		vect2::operator+(vect2 const & rhs) {



