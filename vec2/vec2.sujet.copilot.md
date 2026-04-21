# Sujet vec2 (version clarifiée)

## 1) Nom du rendu
- Nom de l’exercice : vect2
- Fichiers attendus : uniquement des fichiers .cpp et .hpp
- Fonctions autorisées : toutes les fonctions standard C++

## 2) Objectif
Créer une classe nommée vect2 qui représente un vecteur mathématique 2D.
La classe doit stocker ses deux composantes via un conteneur std::vector<int>.

## 3) Structure obligatoire de la classe
La classe vect2 doit contenir :
- Un attribut privé nommé _container de type std::vector<int>
- Ce conteneur doit toujours contenir exactement 2 entiers :
- Index 0 : composante x
- Index 1 : composante y

## 4) Constructeurs et destructeur à implémenter
Tu dois implémenter exactement :
- vect2();
- Constructeur par défaut : initialise à (0, 0)
- vect2(int v1, int v2);
- Constructeur à deux valeurs : initialise à (v1, v2)
- vect2(const vect2& original);
- Constructeur de copie
- ~vect2();
- Destructeur

## 5) Méthode obligatoire
Tu dois implémenter :
- int getContainer_elements(int index) const;

Comportement attendu :
- Retourne l’élément demandé (index 0 ou 1)
- Doit gérer la vérification de bornes
- Si l’index est invalide, le comportement doit être géré proprement dans ton implémentation

## 6) Surcharges d’opérateurs obligatoires
Tu dois implémenter :
- operator+ : addition de deux vecteurs
- operator- : soustraction de deux vecteurs
- operator* : multiplication par un scalaire (vect2 * int)
- operator= : affectation
- operator<< : affichage dans un flux de sortie

Format d’affichage imposé pour operator<< :
- (x, y)

## 7) Règles mathématiques à respecter
- Addition : (x1, y1) + (x2, y2) = (x1 + x2, y1 + y2)
- Soustraction : (x1, y1) - (x2, y2) = (x1 - x2, y1 - y2)
- Multiplication scalaire : (x, y) * k = (x * k, y * k)

## 8) Contraintes de conception
- _container doit toujours avoir 2 éléments, jamais plus, jamais moins
- La méthode getContainer_elements doit vérifier les bornes
- La copie doit être correcte (sémantique de copie propre)
- Les opérations arithmétiques (+, -, *) doivent retourner de nouveaux objets vect2

## 9) Résultat attendu (exemple d’utilisation)
Exemple logique attendu :
- vect2 v1(3, 4)
- vect2 v2(1, 2)
- vect2 v3 = v1 + v2 donne (4, 6)
- vect2 v4 = v1 * 2 donne (6, 8)
- Affichage de v3 avec operator<< donne : (4, 6)

## 10) Checklist finale avant rendu
- La classe s’appelle bien vect2
- _container est privé et de type std::vector<int>
- _container contient toujours exactement 2 éléments
- Les 3 constructeurs sont présents et corrects
- Le destructeur est présent
- getContainer_elements(int) const est présent et vérifie les bornes
- operator+, operator-, operator*, operator= et operator<< sont présents
- operator<< affiche exactement au format (x, y)
- Les opérations +, -, * renvoient de nouveaux objets
- Le code compile proprement

## 11) Ce que ton implémentation doit bien gérer
- Initialisation correcte du conteneur interne
- Accès sécurisé aux éléments via index
- Surcharges d’opérateurs cohérentes
- Gestion propre du cycle de vie des objets
