#ifndef VECT2_HPP
#define VECT2_HPP

#include <iostream>
#include <vector>

class vect2
{
    private:
        std::vector<int> container_;
    public:
        vect2();//:23??????
        vect2(int num1, int num2);//:24
        vect2(const vect2& source);//:25
        vect2& operator=(const vect2& source);//:26

        int operator[](int index) const;//:49,50
        int& operator[](int index);//:47,48

        vect2 operator-() const;//:46
        vect2 operator*(int num) const;//:39

        vect2& operator*=(int num);//:42

        vect2& operator+=(const vect2& obj);//:37
        vect2& operator-=(const vect2& obj);//:38
        vect2& operator*=(const vect2& obj);//!!!!!!!!!!!!!!!!!!!!!!!!

        vect2 operator+(const vect2& obj) const;//:43
        vect2 operator-(const vect2& obj) const;//:43
        vect2 operator*(const vect2& obj) const;//:!!!!!!

        vect2& operator++();//:34
        vect2 operator++(int);//:33
        vect2& operator--();//:36
        vect2 operator--(int);//:35

        bool operator==(const vect2& obj) const;//:51,52
        bool operator!=(const vect2& obj) const;//:53,54

        ~vect2();
};

vect2 operator*(int num, const vect2& obj);

std::ostream& operator<<(std::ostream& os, const vect2& obj);

#endif
