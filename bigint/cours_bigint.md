# Cours : comprendre la solution `bigint` (version Copilot)

Ce document passe en revue **toutes les fonctions** de `bigint.hpp` / `bigint.cpp`, explique leur rôle, leur fonctionnement interne, et pourquoi elles sont écrites ainsi.

---

## 1. Architecture générale

La classe `bigint` stocke un grand entier **sous forme de `std::string`**, chiffre par chiffre, en base 10, **sans signe** (l'énoncé demande un entier non signé).

```cpp
class bigint
{
private:
    std::string str;             // ex: "1337"
    bigint(const std::string& value); // constructeur PRIVÉ

    static std::string normalize(...);
    static std::string add_strings(...);
    static int compare_strings(...);
    static unsigned long long parse_count(...);
    static std::string shift_left(...);
    static std::string shift_right(...);
public:
    // constructeurs, opérateurs...
};
```

**Idée clé** : toute la logique "métier" (addition, comparaison, décalage) est déportée dans des **fonctions statiques privées qui manipulent des `std::string`**, indépendamment de la classe elle-même. Les opérateurs publics (`+`, `<<`, `==`...) ne font qu'appeler ces fonctions et emballer le résultat dans un `bigint`.

Le **constructeur privé `bigint(const std::string&)`** est l'astuce centrale : il permet de construire un `bigint` directement à partir d'une chaîne déjà calculée, sans exposer ce constructeur à l'utilisateur (on ne veut pas qu'un utilisateur externe puisse faire `bigint("abc")` n'importe comment sans validation... même si ici il n'y a pas de vraie validation, voir limites en fin de document).

---

## 2. Fonctions utilitaires libres (hors classe)

### `reverse_string`
```cpp
static std::string reverse_string(const std::string& value)
```
- Inverse une chaîne de caractères (ex: `"123"` → `"321"`).
- Utilisée car il est **beaucoup plus simple d'additionner deux nombres si on part du chiffre des unités**, donc on travaille souvent "à l'envers" puis on réinverse le résultat.
- Déclarée `static` **au sens du C++ pour un fichier .cpp** (visibilité limitée à ce fichier, pas de fuite dans l'éditeur de liens).

---

## 3. Fonctions statiques privées de `bigint` (le cœur algorithmique)

### `normalize`
```cpp
static std::string bigint::normalize(const std::string& value)
```
- Supprime les zéros non significatifs en tête de chaîne.
- Exemples : `"007"` → `"7"`, `"000"` → `"0"`, `"42"` → `"42"`.
- **Pourquoi c'est indispensable** : l'énoncé impose *"the output should not contain any leading zeros"*. Chaque fois qu'on construit un `bigint` ou qu'on modifie `str`, on repasse par `normalize`.

### `add_strings`
```cpp
static std::string bigint::add_strings(const std::string& lhs, const std::string& rhs)
```
Additionne deux nombres représentés en `string`, **comme une addition posée à la main** :

1. On inverse les deux chaînes (`reverse_string`) pour partir des unités.
2. On parcourt chiffre par chiffre (`i = 0, 1, 2, ...`) jusqu'à avoir dépassé la longueur des deux nombres **et** qu'il n'y ait plus de retenue (`carry`).
3. À chaque étape :
   - on récupère le chiffre courant de chaque nombre (`0` si on est hors des bornes),
   - on calcule `sum = digit_left + digit_right + carry`,
   - on stocke `sum % 10` comme chiffre du résultat,
   - on met à jour `carry = sum / 10`.
4. On réinverse le résultat, puis on `normalize`.

C'est l'algorithme classique d'addition en base 10 avec retenue, généralisé à des nombres de taille arbitraire.

### `compare_strings`
```cpp
static int bigint::compare_strings(const std::string& lhs, const std::string& rhs)
```
Retourne `-1`, `0` ou `1` selon que `lhs < rhs`, `lhs == rhs` ou `lhs > rhs`.

Logique :
1. Si les tailles diffèrent, **la chaîne la plus longue représente le plus grand nombre** (puisqu'il n'y a jamais de zéros non significatifs grâce à `normalize`). Donc comparer les tailles suffit.
2. Si les tailles sont égales, une comparaison lexicographique classique (`lhs < rhs` sur des `std::string`) fonctionne, car à longueur égale, l'ordre lexicographique des chiffres correspond à l'ordre numérique.

⚠️ C'est un point souvent raté par les étudiants : comparer `"9"` et `"10"` directement en lexicographique donnerait `"9" > "10"` (faux !). D'où l'importance de vérifier la taille en premier.

### `parse_count`
```cpp
static unsigned long long bigint::parse_count(const std::string& value)
```
- Convertit une chaîne de chiffres en `unsigned long long`, utilisé pour les décalages (`operator<<`/`operator>>` qui prennent un `bigint` en paramètre).
- Gère un **overflow protection** : si la valeur convertie dépasserait `ULLONG_MAX`, elle **sature** à `ULLONG_MAX` au lieu de déborder silencieusement (comportement indéfini évité).
```cpp
if (count > (ULLONG_MAX - digit) / 10)
    return (ULLONG_MAX);
```
Cette formule évite de calculer `count * 10 + digit` avant de vérifier le dépassement (ce qui provoquerait déjà l'overflow).

### `shift_left`
```cpp
static std::string bigint::shift_left(const std::string& value, unsigned long long count)
```
- Équivalent de multiplier par `10^count` : on **ajoute `count` zéros à la fin** de la chaîne.
- Cas particulier : si `value == "0"`, on renvoie `"0"` (pas la peine d'ajouter des zéros à zéro).
- Exemple : `shift_left("42", 3)` → `"42000"`.

### `shift_right`
```cpp
static std::string bigint::shift_right(const std::string& value, unsigned long long count)
```
- Équivalent d'une division entière par `10^count` : on **retire les `count` derniers caractères**.
- Si `count >= value.size()`, il ne reste plus rien de significatif → on renvoie `"0"`.
- Exemple : `shift_right("1337", 2)` → `"13"`.
- On repasse par `normalize` au cas où (bien que retirer des caractères de la fin ne crée pas de zéros en tête, cet appel est surtout défensif/cohérent avec le reste du code).

---

## 4. Constructeurs et affectation

### `bigint()` — constructeur par défaut
```cpp
bigint::bigint() : str("0") {}
```
Un `bigint` par défaut vaut `0`.

### `bigint(unsigned int num)` — constructeur depuis un entier
```cpp
bigint::bigint(unsigned int num)
```
- Convertit un `unsigned int` en `std::string` chiffre par chiffre (`num % 10`, puis `num /= 10`), en accumulant les chiffres puis en les inversant à la fin.
- Cas particulier `num == 0` → `"0"` directement (sinon la boucle `while (num > 0)` ne s'exécuterait jamais et laisserait `value` vide).

### `bigint(const std::string& value)` — constructeur privé
```cpp
bigint::bigint(const std::string& value) : str(normalize(value)) {}
```
- **Privé** : seule la classe elle-même peut l'utiliser en interne (dans `operator+`, `operator<<`, etc.) pour construire un résultat déjà calculé sous forme de chaîne.
- Appelle `normalize` par sécurité.

### `bigint(const bigint& source)` — constructeur de copie
```cpp
bigint::bigint(const bigint& source) : str(source.str) {}
```
Copie simplement la chaîne interne. Nécessaire ici même si le compilateur en génèrerait un automatiquement équivalent (bonne pratique de le définir explicitement quand on a un destructeur/operator= custom — règle des 3).

### `operator=` — opérateur d'affectation
```cpp
bigint& bigint::operator=(const bigint& source)
```
- Protection contre l'auto-affectation (`if (this != &source)`).
- Retourne `*this` pour permettre le chaînage (`a = b = c`).

### `~bigint()` — destructeur
```cpp
bigint::~bigint() {}
```
Vide, car `std::string` gère sa propre mémoire (RAII). Défini explicitement par cohérence avec la règle des 3 (copie / affectation / destruction).

---

## 5. Accesseur

### `getStr`
```cpp
std::string bigint::getStr() const
```
Retourne la représentation interne en `std::string`. Utilisé notamment par `operator<<` (affichage).

---

## 6. Opérateur d'addition

### `operator+`
```cpp
bigint bigint::operator+(const bigint& other) const
```
Retourne un **nouveau** `bigint` égal à `*this + other`, sans modifier `*this`. Utilise `add_strings` puis le constructeur privé.

### `operator+=`
```cpp
bigint& bigint::operator+=(const bigint& other)
```
Modifie `*this` **en place** et retourne une référence sur lui-même (pour permettre `a += b += c` ou juste l'affichage direct du résultat).

---

## 7. Opérateurs de décalage (digitshift)

Il y a **4 variantes de chaque opérateur** (`<<`/`>>`), car l'énoncé exige que ça marche à la fois avec un `unsigned int` classique et avec un `bigint` (cf. `d >>= (const bigint)2` dans le `main`) :

| Opérateur | Paramètre | Rôle |
|---|---|---|
| `operator<<(unsigned int n) const` | `unsigned int` | renvoie une copie décalée |
| `operator<<=(unsigned int n)` | `unsigned int` | décale `*this` en place |
| `operator<<(const bigint& other) const` | `bigint` | renvoie une copie décalée |
| `operator<<=(const bigint& other)` | `bigint` | décale `*this` en place |

(idem pour `>>` / `>>=`)

**Astuce d'implémentation** : les versions "avec `bigint` en paramètre" ne font que convertir ce `bigint` en `unsigned long long` via `parse_count`, puis appellent la version avec `unsigned int`/`unsigned long long` :

```cpp
bigint bigint::operator<<(const bigint& other) const
{
    return (*this << parse_count(other.str));
}
```

Cela évite de dupliquer la logique : **une seule vraie implémentation** (`shift_left`/`shift_right`), les autres méthodes ne sont que des "adaptateurs".

---

## 8. Incrémentation

### `operator++()` — pré-incrémentation
```cpp
bigint& bigint::operator++()
{
    return (*this += bigint(1));
}
```
`++b` : incrémente `*this`, puis retourne une référence sur la valeur **déjà incrémentée**.

### `operator++(int)` — post-incrémentation
```cpp
bigint bigint::operator++(int)
{
    bigint temp(*this);
    ++(*this);
    return (temp);
}
```
`b++` : sauvegarde l'état **avant** incrémentation dans `temp`, incrémente `*this`, puis retourne `temp` (la valeur **avant** incrémentation).
Le paramètre `int` factice (non utilisé) est la convention C++ pour distinguer post- de pré-incrémentation à la surcharge.

---

## 9. Opérateurs de comparaison

Tous délèguent à `compare_strings` :

```cpp
bool bigint::operator==(const bigint& other) const { return (str == other.str); }
bool bigint::operator!=(const bigint& other) const { return (!(*this == other)); }
bool bigint::operator<(const bigint& other) const  { return (compare_strings(str, other.str) < 0); }
bool bigint::operator>(const bigint& other) const  { return (compare_strings(str, other.str) > 0); }
bool bigint::operator<=(const bigint& other) const { return (compare_strings(str, other.str) <= 0); }
bool bigint::operator>=(const bigint& other) const { return (compare_strings(str, other.str) >= 0); }
```
- `==` compare directement les chaînes (valide car normalisées, donc pas d'ambiguïté du type `"007"` vs `"7"`).
- `!=` est défini **à partir de `==`** (évite la duplication de logique).
- Les autres s'appuient sur `compare_strings` qui renvoie `-1`/`0`/`1`.

---

## 10. Affichage

### `operator<<(std::ostream&, const bigint&)` — hors classe
```cpp
std::ostream& operator<<(std::ostream& output, const bigint& obj)
{
    output << obj.getStr();
    return (output);
}
```
- Déclarée **hors de la classe** (obligatoire en C++ car le flux `std::ostream` est à gauche de l'opérateur, pas l'objet `bigint`).
- Déclarée `friend`... en fait non, ici elle n'a **pas besoin** d'être `friend` puisqu'elle utilise `getStr()` (accesseur public) plutôt que d'accéder directement à `str`.
- Retourne `output` pour permettre le chaînage (`std::cout << a << b << std::endl`).

---

## 11. Tableau récapitulatif

| Fonction | Type | Rôle en une phrase |
|---|---|---|
| `reverse_string` | libre, fichier .cpp | inverse une chaîne |
| `normalize` | statique privée | retire les zéros de tête |
| `add_strings` | statique privée | additionne deux nombres-chaînes |
| `compare_strings` | statique privée | compare deux nombres-chaînes (-1/0/1) |
| `parse_count` | statique privée | convertit une chaîne en `unsigned long long` (avec saturation) |
| `shift_left` | statique privée | ajoute des zéros à droite (×10ⁿ) |
| `shift_right` | statique privée | retire des chiffres à droite (÷10ⁿ) |
| `bigint()` | constructeur | valeur par défaut = 0 |
| `bigint(unsigned int)` | constructeur | depuis un entier natif |
| `bigint(const std::string&)` | constructeur privé | depuis une chaîne déjà calculée |
| `bigint(const bigint&)` | constructeur de copie | copie |
| `operator=` | affectation | copie avec protection auto-affectation |
| `~bigint()` | destructeur | rien à faire (RAII) |
| `getStr` | accesseur | renvoie la chaîne interne |
| `operator+` / `+=` | arithmétique | addition |
| `operator<<`/`>>` (×4 chacun) | digitshift | décalage décimal |
| `operator++` (pré/post) | incrémentation | +1 |
| `==`,`!=`,`<`,`>`,`<=`,`>=` | comparaison | comparaison numérique |
| `operator<<(ostream&, ...)` | affichage | impression via `std::cout` |

---

## 12. Limites / points à surveiller si tu évalues une copie

- **`bigint(unsigned int)`** : ne gère pas les nombres qui dépassent `SIZE_MAX` *au moment de la construction*, ce qui est normal (l'énoncé demande de dépasser `SIZE_MAX` **après calculs**, pas en entrée).
- **Pas de vérification que la string passée au constructeur privé ne contient que des chiffres** — acceptable car ce constructeur est privé et seulement utilisé en interne avec des chaînes déjà valides.
- **Complexité** : `add_strings` est en `O(n)` où `n` est le nombre de chiffres — c'est optimal pour une addition.
- **`shift_left`/`shift_right`** sont en `O(n)` à cause de la copie de `std::string` — acceptable, pas d'algorithme plus rapide possible pour une représentation en chaîne.

---

*Ce cours couvre l'intégralité des fonctions de `bigint.hpp`/`bigint.cpp` (version Copilot). Pour t'entraîner, essaie de ré-écrire chaque fonction à partir de sa seule description ci-dessus, sans regarder le code.*
