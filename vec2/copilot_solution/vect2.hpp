#ifndef VECT2_HPP
#define VECT2_HPP

#include <iostream>
#include <vector>

class vect2
{
private:
    std::vector<int> _container;

public:
    vect2();
    vect2(int v1, int v2);
    vect2(const vect2& original);
    ~vect2();

    int getContainer_elements(int index) const;

    vect2 operator+(const vect2& other) const;
    vect2 operator-(const vect2& other) const;
    vect2 operator*(int scalar) const;
    vect2& operator=(const vect2& other);
};

std::ostream& operator<<(std::ostream& out, const vect2& v);

#endif
