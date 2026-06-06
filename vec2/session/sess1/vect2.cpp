#include "vect2.hpp"
#include <stdexcept>

vect2::vect2() : container_(2,0) {}

vect2::vect2(int v1, int v2) : container_(2) {
	container_[0] = v1;
	container_[1] = v2;
}

vect2::vect2(vect2 const & original) : container_(original.container_) {}
