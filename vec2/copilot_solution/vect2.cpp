#include "vect2.hpp"

#include <stdexcept>

vect2::vect2() : _container(2, 0)
{
}

vect2::vect2(int v1, int v2) : _container(2)
{
    _container[0] = v1;
    _container[1] = v2;
}

vect2::vect2(const vect2& original) : _container(original._container)
{
}

vect2::~vect2()
{
}

int vect2::getContainer_elements(int index) const
{
    if (index < 0 || index > 1)
        throw std::out_of_range("vect2 index must be 0 or 1");
    return _container[static_cast<std::size_t>(index)];
}

vect2 vect2::operator+(const vect2& other) const
{
    return vect2(_container[0] + other._container[0], _container[1] + other._container[1]);
}

vect2 vect2::operator-(const vect2& other) const
{
    return vect2(_container[0] - other._container[0], _container[1] - other._container[1]);
}

vect2 vect2::operator*(int scalar) const
{
    return vect2(_container[0] * scalar, _container[1] * scalar);
}

vect2& vect2::operator=(const vect2& other)
{
    if (this != &other)
        _container = other._container;
    return *this;
}

std::ostream& operator<<(std::ostream& out, const vect2& v)
{
    out << "(" << v.getContainer_elements(0) << ", " << v.getContainer_elements(1) << ")";
    return out;
}
