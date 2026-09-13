#include "vect2.hpp"

#include <iostream>

int main()
{
	vect2 v1;						// vect2()                                    -> ctor par défaut
	vect2 v2(1, 2);					// vect2(int, int)                             -> ctor paramétré
	const vect2 v3(v2);				// vect2(vect2 const &)                        -> ctor de copie
	vect2 v4 = v2;					// vect2(vect2 const &)                        -> ctor de copie (initialisation, pas operator=)

	std::cout << "v1: " << v1 << std::endl;	// operator<<(std::ostream &, vect2 const &)
	std::cout << "v2: " << v2 << std::endl;	// operator<<(std::ostream &, vect2 const &)
	std::cout << "v3: " << v3 << std::endl;	// operator<<(std::ostream &, vect2 const &)
	std::cout << "v4: " << v4 << std::endl;	// operator<<(std::ostream &, vect2 const &)
	std::cout << v4++ << std::endl;			// operator++(int)  puis  operator<<(...)     -> post-incrémentation
	std::cout << ++v4 << std::endl;			// operator++()     puis  operator<<(...)     -> pré-incrémentation
	std::cout << v4-- << std::endl;			// operator--(int)  puis  operator<<(...)     -> post-décrémentation
	std::cout << --v4 << std::endl;			// operator--()     puis  operator<<(...)     -> pré-décrémentation
	v2 += v3;						// operator+=(vect2 const &)
	v1 -= v2;						// operator-=(vect2 const &)
	v2 = v3 + v3 * 2;				// operator*(int)  puis  operator+(vect2 const&)  puis  operator=(vect2 const&)
	v2 = 3 * v2;						// operator*(int, vect2 const &) [non-membre, friend]  puis  operator=(vect2 const&)
	v2 += v2 += v3;					// operator+=(vect2 const &)  x2 (appels imbriqués)
	v1 *= 42;						// operator*=(int)
	v1 = v1 - v1 + v1;				// operator-(vect2 const&)  puis  operator+(vect2 const&)  puis  operator=(vect2 const&)
	std::cout << "v1: " << v1 << std::endl;			// operator<<(std::ostream &, vect2 const &)
	std::cout << "v2: " << v2 << std::endl;			// operator<<(std::ostream &, vect2 const &)
	std::cout << "-v2: " << -v2 << std::endl;			// operator-() const  puis  operator<<(...)   -> négation unaire
	std::cout << "v1[1]: " << v1[1] << std::endl;		// operator[](int) const  puis  operator<<(...)
	v1[1] = 12;						// operator[](int)                             -> version non-const (écriture)
	std::cout << "v1[1]: " << v1[1] << std::endl;		// operator[](int) const  puis  operator<<(...)
	std::cout << "v3[1]: " << v3[1] << std::endl;		// operator[](int) const  (v3 est const)  puis  operator<<(...)
	std::cout << "v1 == v3: " << (v1 == v3) << std::endl;	// operator==(vect2 const&) const  puis  operator<<(...)
	std::cout << "v1 == v1: " << (v1 == v1) << std::endl;	// operator==(vect2 const&) const  puis  operator<<(...)
	std::cout << "v1 != v3: " << (v1 != v3) << std::endl;	// operator!=(vect2 const&) const  puis  operator<<(...)
	std::cout << "v1 != v1: " << (v1 != v1) << std::endl;	// operator!=(vect2 const&) const  puis  operator<<(...)
	return (0);
}
