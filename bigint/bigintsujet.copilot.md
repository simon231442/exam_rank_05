# Sujet clarifie: string_bigint

## 1. Objectif
Implementer une classe `bigint` capable de representer et manipuler des entiers de taille arbitraire (beaucoup plus grands que les types natifs), en stockant la valeur sous forme de chaine de caracteres.

## 2. Contraintes generales
- Nom du rendu: `string_bigint`
- Fichiers attendus: `*.cpp` et `*.hpp`
- Fonctions autorisees: toutes les fonctions standard C++
- Representation interne: uniquement des chiffres (`0` a `9`)
- Gestion du signe: non requise (pas de nombres negatifs a gerer en entree)

## 3. Interface minimale obligatoire

### 3.1 Classe et attribut prive
- Creer une classe `bigint`
- Ajouter l'attribut prive:
  - `std::string _string;`

### 3.2 Constructeurs obligatoires
Implementer:
- `bigint();`
  - Valeur par defaut: `"0"`
- `bigint(unsigned int n);`
- `bigint(const std::string& str);`
- `bigint(const bigint& original);`

### 3.3 Destructeur obligatoire
- `~bigint();`

### 3.4 Getter obligatoire
- `std::string getArbiter_value() const;`
  - Retourne la valeur interne sous forme de chaine

### 3.5 Operateurs obligatoires
Implementer au minimum:
- `operator+` (addition)
- `operator-` (soustraction)
- `operator*` (multiplication)
- `operator=` (affectation)
- `operator<<` (affichage dans un flux `std::ostream`)

## 4. Regles de comportement attendues

### 4.1 Normalisation des valeurs
- Supprimer les zeros en tete
- Conserver `"0"` comme representation canonique de zero
  - Exemple: `"0000"` devient `"0"`
  - Exemple: `"000123"` devient `"123"`

### 4.2 Validation des chaines en entree
- Une chaine invalide doit etre geree proprement (gestion d'erreur requise)
- Cas invalides typiques:
  - Chaine vide
  - Caracteres non numeriques
  - Espaces, signes, ponctuation

### 4.3 Operations arithmetiques
- Les operations doivent fonctionner meme pour des nombres depassant les types standards (`int`, `long long`, etc.)
- Les operations demandees doivent produire un `bigint` resultat
- L'implementation doit couvrir les cas limites usuels

## 5. Cas limites a couvrir explicitement
- Chaines vides
- Chaines avec zeros en tete
- Operandes egaux a zero
- Resultats avec retenue importante (addition)
- Resultats de taille superieure aux operandes

## 6. Checklist de realisation

- [ ] Declarer la classe `bigint` avec `std::string _string` en prive
- [ ] Implementer les 4 constructeurs demandes
- [ ] Implementer le destructeur
- [ ] Implementer `getArbiter_value() const`
- [ ] Implementer `operator+`
- [ ] Implementer `operator-`
- [ ] Implementer `operator*`
- [ ] Implementer `operator=`
- [ ] Implementer `operator<<` pour `std::ostream`
- [ ] Gerer la normalisation des zeros en tete
- [ ] Gerer les entrees string invalides
- [ ] Verifier que les calculs fonctionnent sur de tres grands nombres

## 7. Exemple d'utilisation attendu
```cpp
bigint a("123456789012345678901234567890");
bigint b(987654321);
bigint c = a + b;
std::cout << c << std::endl;
```

## 8. Definition de fini (Done)
Le travail est considere termine si:
- Toutes les signatures obligatoires sont presentes
- Les operations `+`, `-`, `*`, `=` et affichage fonctionnent
- Les valeurs sont toujours normalisees (`"0"` unique pour zero)
- Les erreurs d'entree string sont traitees
- Les tests sur grands nombres et cas limites passent
