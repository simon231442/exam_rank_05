#ifndef VECT2_HPP
# define VECT2_HPP
# include <vector>
# include <iostream>
class	vect2 {
	private :
		std::vector<int>	container_;
	public :
		vect2();
		vect2(int x, int y);
		vect2(vect2 const & src);
		vect2&				operator=(vect2 const & rhs);	// v1 = v2;
		int					operator[](int index) const;	// x = v[0];
		int&				operator[](int index);			// v[1] = y;
		vect2				operator-() const;				// opérateur unaire moins (Négation) // v1 = -v2

		// --- Maths : opérateurs binaires (non-mutants, retournent un nouvel objet) ---
		vect2				operator+(vect2 const & rhs) const;	// v3 = v1 + v2;   [AJOUTÉ]
		vect2				operator-(vect2 const & rhs) const;	// v3 = v1 - v2;   [AJOUTÉ]
		vect2				operator*(int scalar) const;			// v2 = v1 * 3;

		// --- Maths : opérateurs d'affectation composée (mutants, modifient *this) ---
		vect2&				operator*=(int scalar);		// v *= 3;            [CORRIGÉ: retourne vect2&]
		//vect2				operator*=(vect2 const & rhs);	// v1 *= v2;
		vect2&				operator+=(vect2 const & rhs);	// v1 += v2;          [CORRIGÉ: retourne vect2&]
		vect2&				operator-=(vect2 const & rhs);	// v1 -= v2;          [CORRIGÉ: retourne vect2&]

		vect2&				operator++();					// ++v; pourquoi ici &  -> car pré-incrément retourne l'objet lui-même déjà modifié
		vect2				operator++(int);				// v++; et pas la ??? -> car post-incrément doit retourner une COPIE de l'ancienne valeur
		vect2&				operator--();					// --v;
		vect2				operator--(int);				// v--;
		bool				operator==(vect2 const& rhs) const; // bool = (v1 == v2)
		bool				operator!=(vect2 const& rhs) const; // bool = (v1 != v2)
		~vect2();
	};
vect2						operator*(int scalar, vect2 const & rhs);	// [CORRIGÉ: retourne vect2, pas int]
std::ostream&				operator<<(std::ostream& out, vect2 const & rhs);
#endif
