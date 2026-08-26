



		bigint  operator+(const bigint& rhs) const;			//operateur binaire non-modificateur d'addition
		bigint& operator+=(const bigint& rhs);				//operateur d'affectation compose d'addition

		bigint  operator<<(unsigned long long n) const;		//operateur binaire non-modificateur de digitshifting par un unsigned long long vers la gauche
		bigint  operator>>(unsigned long long n) const;		//operateur binaire non-modificateur de digitshifting par un unsigned long long vers la droite
		bigint& operator<<=(unsigned long long n);			//operateur d'affectation compose de digitshifting par un unsigned long long vers la gauche
		bigint& operator>>=(unsigned long long n);			//operateur d'affectation compose de digitshifting par un unsigned long long vers la droite
		bigint  operator<<(const bigint& n) const;			//operateur binaire non-modificateur de digitshifting par un bigint vers la gauche
		bigint  operator>>(const bigint& n) const;			//operateur binaire non-modificateur de digitshifting par un bigint vers la droite
		bigint& operator<<=(const bigint& n);				//operateur d'affectation compose de digitshifting par un bigint vers la gauche
		bigint& operator>>=(const bigint& n);               //operateur d'affectation compose de digitshifting par un bigint vers la droite

		bigint& operator++();								//operateur de pre-incrementation
		bigint  operator++(int);							//operateur de post-incrementation

		bool operator==(const bigint& rhs) const;			//operateur de comparaison d'egalite
		bool operator!=(const bigint& rhs) const;			//operateur de comparaison d'inegalite
		bool operator<(const bigint& rhs)  const;			//operateur de comparaison d'inferiorite
		bool operator>(const bigint& rhs)  const;			//operateur de comparaison de superiorite
		bool operator<=(const bigint& rhs) const;			//operateur de comparaison d'inferiorite/egalite
		bool operator>=(const bigint& rhs) const;			//operateur de comparaison de superiorite/egalite

		friend std::ostream& operator<<(std::ostream& os, const bigint& n);	//operateur d'insertion dans le flux


