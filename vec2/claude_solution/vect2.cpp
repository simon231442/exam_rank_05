#include "vect2.hpp"

// ==================== Constructeurs / Destructeur ====================

vect2::vect2() : container_(2, 0) {}				// Constructeur par défaut

vect2::vect2(int x, int y) : container_(2) {		// Constructeur paramétré
	container_[0] = x;
	container_[1] = y;
}

vect2::vect2(vect2 const & src) : container_(src.container_) {}	// Constructeur de copie

vect2::~vect2() {						// Destructeur
	// std::vector gère lui-même sa mémoire, rien à faire ici
}

// ==================== Affectation ====================

vect2 & vect2::operator=(vect2 const & rhs) {	// Opérateur d'affectation
	if (this != &rhs)
		container_ = rhs.container_;
	return *this;
}

// ==================== Accès (indexation) ====================

int vect2::operator[](int index) const {	// Indexation lecture seule
	return container_[index];
}

int & vect2::operator[](int index) {		// Indexation lecture/écriture
	return container_[index];
}

// ==================== Négation ====================

vect2 vect2::operator-() const {			// Opérateur unaire de négation
	return vect2(-container_[0], -container_[1]);
}

// ==================== Maths : opérateurs binaires (non-mutants) ====================

vect2 vect2::operator+(vect2 const & rhs) const {	// Addition
	return vect2(container_[0] + rhs.container_[0],
				 container_[1] + rhs.container_[1]);
}

vect2 vect2::operator-(vect2 const & rhs) const {	// Soustraction
	return vect2(container_[0] - rhs.container_[0],
				 container_[1] - rhs.container_[1]);
}

vect2 vect2::operator*(int scalar) const {			// Multiplication par un scalaire
	return vect2(container_[0] * scalar, container_[1] * scalar);
}

// ==================== Maths : opérateurs d'affectation composée (mutants) ====================

vect2 & vect2::operator*=(int scalar) {			// Multiplication-affectation (scalaire)
	container_[0] *= scalar;
	container_[1] *= scalar;
	return *this;
}

vect2 & vect2::operator+=(vect2 const & rhs) {		// Addition-affectation
	container_[0] += rhs.container_[0];
	container_[1] += rhs.container_[1];
	return *this;
}

vect2 & vect2::operator-=(vect2 const & rhs) {		// Soustraction-affectation
	container_[0] -= rhs.container_[0];
	container_[1] -= rhs.container_[1];
	return *this;
}

// ==================== Incrémentation / Décrémentation ====================

vect2 & vect2::operator++() {			// Pré-incrémentation : ++v
	container_[0]++;
	container_[1]++;
	return *this;
}

vect2 vect2::operator++(int) {			// Post-incrémentation : v++
	vect2 tmp(*this);					// copie de l'état AVANT modification
	++(*this);							// réutilise le pré-incrément
	return tmp;							// retourne l'ancienne valeur
}

vect2 & vect2::operator--() {			// Pré-décrémentation : --v
	container_[0]--;
	container_[1]--;
	return *this;
}

vect2 vect2::operator--(int) {			// Post-décrémentation : v--
	vect2 tmp(*this);
	--(*this);
	return tmp;
}

// ==================== Comparaisons ====================

bool vect2::operator==(vect2 const & rhs) const {	// Égalité
	return (container_[0] == rhs.container_[0]
			&& container_[1] == rhs.container_[1]);
}

bool vect2::operator!=(vect2 const & rhs) const {	// Inégalité
	return !(*this == rhs);
}

// ==================== Opérateurs non-membres ====================

vect2 operator*(int scalar, vect2 const & rhs) {	// Multiplication scalaire à gauche : 3 * v1
	return rhs * scalar;
}

std::ostream & operator<<(std::ostream & out, vect2 const & rhs) {	// Affichage : std::cout << v
	out << "(" << rhs[0] << ", " << rhs[1] << ")";
	return out;
}
