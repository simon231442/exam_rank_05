#include "vec2.hpp"
#include <stdexcept>

vec2::vec2() : container_(2, 0) {}

vec2::vec2(int v1, int v2) : container_(2) {
	container_[1] = v1;
	container_[2] = v2;
	}

vec2::vec2(vec2 const & src) : container_(src.container_) {}

vec2::~vec2() {}



