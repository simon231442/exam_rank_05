#ifndef VECT2_HPP
#define VECT2_HPP

#include <iostream>
#include <vector>

class vect2
{
    private:
        std::vector<int> container_;
    public:
        vect2();
        vect2(int num1, int num2);
        vect2(const vect2& source);
        vect2& operator=(const vect2& source);

        int operator[](int index) const;
        int& operator[](int index);

        vect2 operator-() const;//:46
        vect2 operator*(int num) const;

        vect2& operator*=(int num);

        vect2& operator+=(const vect2& obj);//:37
        vect2& operator-=(const vect2& obj);//:38
        vect2& operator*=(const vect2& obj);

        vect2 operator+(const vect2& obj) const;
        vect2 operator-(const vect2& obj) const;//:43
        vect2 operator*(const vect2& obj) const;

        vect2& operator++();
        vect2 operator++(int);
        vect2& operator--();//:36
        vect2 operator--(int);//:35

        bool operator==(const vect2& obj) const;
        bool operator!=(const vect2& obj) const;

        ~vect2();
};

vect2 operator*(int num, const vect2& obj);

std::ostream& operator<<(std::ostream& os, const vect2& obj);

#endif
