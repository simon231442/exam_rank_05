#ifndef VECT2_HPP
# define VECT2_HPP
# include <vector>
# include <iostream>
class	vect2 {
	private :
		std::vector<int>	container_;
	public :

		// --- Constructeurs / Destructeur ---
		vect2();							// Constructeur par défaut
		vect2(int x, int y);				// Constructeur paramétré
		vect2(vect2 const & src);			// Constructeur de copie
		~vect2();							// Destructeur

		// --- Affectation ---
		vect2&				operator=(vect2 const & rhs);	// Opérateur d'affectation (copy assignment)	// v1 = v2;

		// --- Accès (indexation) ---
		int					operator[](int index) const;	// Opérateur d'indexation en lecture seule		// x = v[0];
		int&				operator[](int index);			// Opérateur d'indexation en lecture/écriture	// v[1] = y;

		// --- Négation ---
		vect2				operator-() const;				// Opérateur unaire de négation					// v1 = -v2

		// --- Maths : opérateurs binaires (non-mutants, retournent un nouvel objet) ---
		vect2				operator+(vect2 const & rhs) const;	// Opérateur d'addition					// v3 = v1 + v2;
		vect2				operator-(vect2 const & rhs) const;	// Opérateur de soustraction				// v3 = v1 - v2;
		vect2				operator*(int scalar) const;			// Opérateur de multiplication par scalaire // v2 = v1 * 3;

		// --- Maths : opérateurs d'affectation composée (mutants, modifient *this) ---
		vect2&				operator*=(int scalar);		// Opérateur multiplication-affectation (scalaire)		// v *= 3;
		//vect2				operator*=(vect2 const & rhs);	// Opérateur multiplication-affectation (vecteur) — NON implémenté, pas de sens géométrique standard // v1 *= v2;
		vect2&				operator+=(vect2 const & rhs);	// Opérateur addition-affectation							// v1 += v2;
		vect2&				operator-=(vect2 const & rhs);	// Opérateur soustraction-affectation						// v1 -= v2;

		// --- Incrémentation / Décrémentation ---
		vect2&				operator++();					// Opérateur de pré-incrémentation (retourne une référence : modifie et renvoie l'objet lui-même)	// ++v;
		vect2				operator++(int);				// Opérateur de post-incrémentation (retourne une copie de l'ancienne valeur)						// v++;
		vect2&				operator--();					// Opérateur de pré-décrémentation							// --v;
		vect2				operator--(int);				// Opérateur de post-décrémentation						// v--;

		// --- Comparaisons ---
		bool				operator==(vect2 const& rhs) const; // Opérateur de comparaison d'égalité		// bool = (v1 == v2)
		bool				operator!=(vect2 const& rhs) const; // Opérateur de comparaison d'inégalité	// bool = (v1 != v2)
	};

// --- Opérateurs non-membres ---
vect2						operator*(int scalar, vect2 const & rhs);		// Opérateur de multiplication non-membre (scalaire à gauche : 3 * v1)
std::ostream&				operator<<(std::ostream& out, vect2 const & rhs);	// Opérateur de flux <<, pour l'affichage (std::cout << v)
#endif
