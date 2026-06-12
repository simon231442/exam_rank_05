#include "vect2.hpp"

vect2::vect2()
{
    container_.push_back(0);
    container_.push_back(0);
}

vect2::vect2(int num1, int num2)
{
    container_.push_back(num1);
    container_.push_back(num2);
}

vect2::vect2(const vect2& source)
{
    *this = source;
}

vect2& vect2::operator=(const vect2& source)
{
    if (this != &source)
        container_ = source.container_;
    return (*this);
}

int vect2::operator[](int index) const
{
    return (container_[index]);
}

int& vect2::operator[](int index)
{
    return (container_[index]);
}

vect2 vect2::operator-() const
{
    vect2 temp(*this);
    temp.container_[0] = -temp.container_[0];
    temp.container_[1] = -temp.container_[1];
    return (temp);
}

vect2 vect2::operator*(int num) const
{
    vect2 temp(*this);
    temp *= num;
    return (temp);
}

vect2& vect2::operator*=(int num)
{
    container_[0] *= num;
    container_[1] *= num;
    return (*this);
}

vect2& vect2::operator+=(const vect2& obj)
{
    container_[0] += obj.container_[0];
    container_[1] += obj.container_[1];
    return (*this);
}

vect2& vect2::operator-=(const vect2& obj)
{
    container_[0] -= obj.container_[0];
    container_[1] -= obj.container_[1];
    return (*this);
}

vect2& vect2::operator*=(const vect2& obj)
{
    container_[0] *= obj.container_[0];
    container_[1] *= obj.container_[1];
    return (*this);
}

vect2 vect2::operator+(const vect2& obj) const
{
    vect2 temp(*this);
    temp += obj;
    return (temp);
}

vect2 vect2::operator-(const vect2& obj) const
{
    vect2 temp(*this);
    temp -= obj;
    return (temp);
}

vect2 vect2::operator*(const vect2& obj) const
{
    vect2 temp(*this);
    temp *= obj;
    return (temp);
}

vect2& vect2::operator++()
{
    ++container_[0];
    ++container_[1];
    return (*this);
}

vect2 vect2::operator++(int)
{
    vect2 temp(*this);
    ++(*this);
    return (temp);
}

vect2& vect2::operator--()
{
    --container_[0];
    --container_[1];
    return (*this);
}

vect2 vect2::operator--(int)
{
    vect2 temp(*this);
    --(*this);
    return (temp);
}

bool vect2::operator==(const vect2& obj) const
{
    return (container_[0] == obj.container_[0] && container_[1] == obj.container_[1]);
}

bool vect2::operator!=(const vect2& obj) const
{
    return (!(*this == obj));
}

vect2::~vect2()
{
}

vect2 operator*(int num, const vect2& obj)
{
    return (obj * num);
}

std::ostream& operator<<(std::ostream& os, const vect2& obj)
{
    os << "{" << obj[0] << ", " << obj[1] << "}";
    return (os);
}
