# Guide complet : Polyset

## Fichiers fournis (ne pas modifier)

- `bag.hpp` — classe abstraite de base
- `searchable_bag.hpp` — classe abstraite avec `has()`
- `array_bag.hpp` / `array_bag.cpp` — implémentation avec tableau
- `tree_bag.hpp` / `tree_bag.cpp` — implémentation avec BST
- `main.cpp` — fichier de test fourni

## Fichiers à créer (ce que tu rends)

```
searchable_array_bag.hpp
searchable_array_bag.cpp
searchable_tree_bag.hpp
searchable_tree_bag.cpp
set.hpp
set.cpp
```

---

## Hiérarchie d'héritage

```
           bag  (abstraite, héritée virtuellement)
          /    \
    array_bag  tree_bag    searchable_bag (abstraite, héritée virtuellement)
         \       /    \       /
  searchable_array_bag  searchable_tree_bag

  set  ->  wrapping (contient une référence à searchable_bag)
```

`bag` est héritée avec `virtual` dans `array_bag`, `tree_bag`, et `searchable_bag`.
Cela évite le problème du diamant : dans `searchable_array_bag`, il n'y a qu'une seule instance de `bag`.

---

## Technique centrale : le OCF des classes enfants est vide

Quand une classe enfant n'ajoute pas de membres avec de la mémoire dynamique,
son OCF (constructeur de copie, operator=, destructeur) peut entièrement déléguer au parent.
Tu n'as pas besoin de réécrire la logique de copie ou de destruction.

```
copy constructor  =>  appelle le constructeur de copie du parent via la liste d'initialisation
operator=         =>  appelle operator= du parent explicitement
destructor        =>  corps vide, le parent fait tout
```

---

## Étape 1 : searchable_array_bag.hpp

```cpp
#pragma once

#include "array_bag.hpp"
#include "searchable_bag.hpp"

class searchable_array_bag : public array_bag, public searchable_bag
{
public:
    searchable_array_bag();
    searchable_array_bag(const searchable_array_bag& source);
    searchable_array_bag& operator=(const searchable_array_bag& source);
    ~searchable_array_bag();

    bool has(int) const;
};
```

Points clés :
- Héritage multiple : `array_bag` et `searchable_bag`
- `has(int) const` est la seule méthode à ajouter
- Pas de nouveaux membres de données, donc OCF minimal
- `data` et `size` de `array_bag` sont `protected`, accessibles directement

---

## Étape 2 : searchable_array_bag.cpp

```cpp
#include "searchable_array_bag.hpp"

searchable_array_bag::searchable_array_bag()
{
}

searchable_array_bag::searchable_array_bag(const searchable_array_bag& source)
    : array_bag(source)
{
}

searchable_array_bag& searchable_array_bag::operator=(const searchable_array_bag& source)
{
    if (this != &source)
        array_bag::operator=(source);
    return *this;
}

searchable_array_bag::~searchable_array_bag()
{
}

bool searchable_array_bag::has(int value) const
{
    for (int i = 0; i < size; i++)
        if (data[i] == value)
            return true;
    return false;
}
```

Explication de `has()` :
- `data` et `size` sont hérités de `array_bag` (membres `protected`)
- Parcours linéaire du tableau, retourne `true` dès que la valeur est trouvée
- Pas de gestion de mémoire, pas de complexité

Explication du copy constructor :
- `: array_bag(source)` appelle le copy constructor de `array_bag` qui alloue et copie `data[]`
- Le corps est vide car tout est fait par `array_bag`

Explication de operator= :
- On appelle `array_bag::operator=(source)` qui s'occupe de libérer l'ancienne mémoire et copier la nouvelle
- Self-assignment guard : `if (this != &source)`

---

## Étape 3 : searchable_tree_bag.hpp

```cpp
#pragma once

#include "tree_bag.hpp"
#include "searchable_bag.hpp"

class searchable_tree_bag : public tree_bag, public searchable_bag
{
private:
    bool search(node* n, int value) const;

public:
    searchable_tree_bag();
    searchable_tree_bag(const searchable_tree_bag& source);
    searchable_tree_bag& operator=(const searchable_tree_bag& source);
    ~searchable_tree_bag();

    bool has(int) const;
};
```

Points clés :
- Héritage multiple : `tree_bag` et `searchable_bag`
- `node` est une struct imbriquée dans `tree_bag`, accessible via `tree_bag::node` ou directement `node` dans la classe enfant
- `tree` (le pointeur racine) est `protected` dans `tree_bag`, accessible directement
- La fonction `search()` est privée : c'est un helper récursif pour `has()`

---

## Étape 4 : searchable_tree_bag.cpp

```cpp
#include "searchable_tree_bag.hpp"

searchable_tree_bag::searchable_tree_bag()
{
}

searchable_tree_bag::searchable_tree_bag(const searchable_tree_bag& source)
    : tree_bag(source)
{
}

searchable_tree_bag& searchable_tree_bag::operator=(const searchable_tree_bag& source)
{
    if (this != &source)
        tree_bag::operator=(source);
    return *this;
}

searchable_tree_bag::~searchable_tree_bag()
{
}

bool searchable_tree_bag::search(node* n, int value) const
{
    if (n == nullptr)//if (n == 0) d'apres dia l'expert en polyset
        return false;
    if (n->value == value)
        return true;
    if (value < n->value)
        return search(n->l, value);
    return search(n->r, value);
}

bool searchable_tree_bag::has(int value) const
{
    return search(this->tree, value);
}
```

Explication de `search()` :
- Cas de base : noeud null => la valeur n'existe pas, retourne `false`
- Si la valeur est trouvée sur le noeud courant => retourne `true`
- Si la valeur cherchée est plus petite => on va à gauche (`n->l`)
- Sinon => on va à droite (`n->r`)
- C'est la propriété du BST : gauche < parent < droite

Explication de `has()` :
- Lance la recherche depuis la racine `this->tree`
- `tree` est `protected` dans `tree_bag`, donc accessible ici directement

---

## Étape 5 : set.hpp

```cpp
#pragma once

#include "searchable_bag.hpp"

class set
{
private:
    searchable_bag& bag;

public:
    set() = delete;//d'apres dia faut pas mettre ces 3 constructeurs car c++11 et y'en a pas besoin donc delete delete ^^ (supprime)
    set(const set& source) = delete;//c'est ciao
    set& operator=(const set& source) = delete;//c'est ciao

    set(searchable_bag& s_bag);
    ~set();

    bool has(int) const;
    void insert(int);
    void insert(int*, int);
    void print() const;
    void clear();

    const searchable_bag& get_bag();
};
```

Points clés sur le design :

**Pourquoi une référence et pas un pointeur ?**
Stocker `searchable_bag& bag` est la solution la plus simple :
- Pas de gestion de mémoire (pas de `new`, pas de `delete`)
- Le `set` ne possède pas le bag, il le wrappe juste
- Le bag continue d'exister indépendamment du `set`

**Pourquoi `= delete` sur le default ctor et la copie ?**
Une référence C++ doit être initialisée à la construction et ne peut jamais être réassignée.
Donc :
- Pas de constructeur par défaut possible (on ne peut pas initialiser une référence à rien)
- Pas de `operator=` possible (on ne peut pas réassigner une référence)
- On les supprime explicitement avec `= delete` plutôt que de les laisser générer une erreur bizarre

**Ce n'est pas un manque dans l'OCF** : l'OCF dit que si tu ne peux pas faire ces opérations
de manière sensée, les supprimer est la bonne pratique.

---

## Étape 6 : set.cpp

```cpp
#include "set.hpp"

set::set(searchable_bag& s_bag) : bag(s_bag)
{
}

set::~set()
{
}

bool set::has(int value) const
{
    return bag.has(value);
}

void set::insert(int value)
{
    if (!has(value))
        bag.insert(value);
}

void set::insert(int* arr, int n)
{
    for (int i = 0; i < n; i++)
        insert(arr[i]);
}

void set::print() const
{
    bag.print();
}

void set::clear()
{
    bag.clear();
}

const searchable_bag& set::get_bag()
{
    return bag;
}
```

Explication de chaque méthode :

**constructor** : `: bag(s_bag)` initialise la référence membre. C'est la seule façon d'initialiser
une référence, dans la liste d'initialisation. Après ça, `bag` est lié à `s_bag` pour toujours.

**destructor** : corps vide. Le `set` ne possède pas le bag, donc il ne le détruit pas.

**`has()`** : délègue directement à `bag.has()`. Le polymorphisme fait le reste :
si le bag est un `searchable_array_bag`, il appellera son `has()`, et pareil pour `searchable_tree_bag`.

**`insert(int)`** : c'est la logique centrale du set.
La différence entre un bag et un set : le set refuse les doublons.
On vérifie d'abord avec `has()`, on insère seulement si la valeur est absente.

**`insert(int*, int)`** : boucle simple qui appelle `insert(int)` pour chaque élément.
On réutilise la version simple qui fait déjà la vérification de doublon.

**`print()`** : délègue à `bag.print()`.

**`clear()`** : délègue à `bag.clear()`.

**`get_bag()`** : retourne une `const` référence au bag interne. Permet d'accéder au bag
directement sans modifier le set (comme dans `main.cpp` : `sa.get_bag().print()`).

---

## Compilation

Le `main.cpp` fourni n'inclut que `searchable_bag.hpp` mais utilise toutes les classes.
Pour compiler et tester, ajoute les includes dans ton `main.cpp` :

```cpp
#include "searchable_bag.hpp"
#include "searchable_array_bag.hpp"
#include "searchable_tree_bag.hpp"
#include "set.hpp"
```

Commande de compilation :

```bash
c++ -Wall -Wextra -std=c++11 \
    main.cpp \
    array_bag.cpp \
    tree_bag.cpp \
    searchable_array_bag.cpp \
    searchable_tree_bag.cpp \
    set.cpp \
    -o polyset
```

---

## Résumé des règles importantes

| Règle | Application |
|---|---|
| OCF obligatoire | Toutes les classes sauf `set` (qui utilise `= delete`) |
| `const` sur les méthodes de lecture | `has()`, `print()`, `get_bag()` |
| Pas de doublons dans le set | `insert()` vérifie `has()` avant d'insérer |
| Héritage virtuel du diamant | `bag` hérité avec `virtual` dans `array_bag`, `tree_bag`, `searchable_bag` |
| Le set ne détruit pas le bag | Le bag appartient à l'appelant, pas au set |
| Déléguer au parent dans OCF | Copy ctor et operator= appellent le parent, corps vide |







 installe render-markdown.nvim dans ma config                                                                                                                                       

● Je vais d'abord localiser ta config Neovim.

  Read 1 file, listed 1 directory (ctrl+o to expand)

● C'est ici que va le plugin. Je l'ajoute.

● Update(~/.config/nvim/lua/plugins/custom/your-plugins-go-here.lua)

─────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────
 Edit file
✻ Brewed for 8s

❯ installe render-markdown.nvim dans ma config                                                                                                                                       

● Je vais d'abord localiser ta config Neovim.

  Read 1 file, listed 1 directory (ctrl+o to expand)

● C'est ici que va le plugin. Je l'ajoute.

● Update(~/.config/nvim/lua/plugins/custom/your-plugins-go-here.lua)
  ⎿  Added 6 lines
       9    -- The naming convention is "GitHub Profile/GitHub Repo"
       9    -- The naming convention is "GitHub Profile/GitHub Repo"
      10    --example:
      11    -- 'elkowar/yuck.vim'
      12 +  {                                                                                                                                                                                                  
      13 +    "MeanderingProgrammer/render-markdown.nvim",                                                                                                                                                     
      14 +    dependencies = { "nvim-treesitter/nvim-treesitter" },                                                                                                                                            
      15 +    ft = { "markdown" },                                                                                                                                                                             
      16 +    opts = {},                                                                                                                                                                                       
      17 +  },                                                                                                                                                                                                 
      18  }

● Fait. Maintenant lance :Lazy sync dans nvim pour installer le plugin. Il s'activera automatiquement quand tu ouvres un fichier .md.

✻ Sautéed for 11s

