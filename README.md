# Jeu de la Vie - Projet C++ POO - CESI - A2

Ce projet est une implémentation orientée objet de l'automate cellulaire de John Conway, le **Jeu de la Vie**. Il a été conçu en respectant strictement les principes **SOLID** et en utilisant des **Design Patterns** pour assurer modularité et extensibilité.

## Table des Matières

1.  [Fonctionnalités](https://www.google.com/search?q=%23-fonctionnalit%C3%A9s)
2.  [Architecture Technique](https://www.google.com/search?q=%23-architecture-technique)
3.  [Prérequis](https://www.google.com/search?q=%23-pr%C3%A9requis)
4.  [Compilation](https://www.google.com/search?q=%23-compilation)
5.  [Utilisation](https://www.google.com/search?q=%23-utilisation)
6.  [Format du Fichier d'Entrée](https://www.google.com/search?q=%23-format-du-fichier-dentr%C3%A9e)
7.  [Auteurs](https://www.google.com/search?q=%23-auteurs)

-----

## Fonctionnalités

  * **Lecture de grille :** Chargement de l'état initial depuis un fichier texte.
  * **Mode Console :** Simulation rapide avec écriture des itérations dans des fichiers de sortie.
  * **Mode Graphique :** Visualisation temps réel de l'automate utilisant la bibliothèque **SFML**.
  * **Architecture évolutive :** Ajout facile de nouvelles règles ou de nouveaux états sans modifier le cœur du programme.
  * **Tests Unitaires :** Vérification de la robustesse de la logique.

-----

## Architecture Technique

Ce projet se distingue par l'utilisation avancée de concepts objets pour éviter le code procédural :

### 1\. Pattern État (State Pattern)

Contrairement à une simple approche booléenne, l'état d'une cellule est géré par polymorphisme.

  * **Classe** : `Cellule` délègue à `Etat_cellule`.
  * **États concrets** : `Est_vivant`, `Est_mort`.
  * **Avantage** : Permet d'ajouter facilement des états futurs (ex: "Malade", "Immunisé") sans changer la classe `Cellule`.

### 2\. Pattern Stratégie (Strategy Pattern)

Les règles de survie et de naissance sont encapsulées.

  * **Interface** : `Regles_du_jeu`.
  * **Implémentation** : `Regles_initiales` (Règles classiques de Conway).
  * **Avantage** : On peut changer les règles du jeu à la volée (ex: "HighLife", "Day & Night") sans toucher à la grille.

### 3\. Architecture MVC (Modèle-Vue-Contrôleur)

  * **Modèle** : `Grille`, `Cellule`, `Regles`.
  * **Vues** : `Console`, `Graphique`.
  * **Contrôleur** : `Gestion_jeu`.

-----

## Utilisation

Le programme prend en argument le chemin du fichier de configuration.

```bash
./JeuDeLaVie <fichier_entree.txt>
```

Une fois lancé, le programme vous demandera de choisir le mode :

1.  **Mode Console** : Génère les fichiers de sortie dans le dossier `*_out`.
2.  **Mode Graphique** : Ouvre une fenêtre pour voir l'évolution.

-----

## 📄 Format du Fichier d'Entrée

Le fichier doit respecter le format suivant :

1.  Première ligne : `Lignes Colonnes`
2.  Lignes suivantes : Matrice de `0` (mort) et `1` (vivant).

**Exemple (`glider.txt`) :**

```text
10 10
0 0 1 0 0 0 0 0 0 0
1 0 1 0 0 0 0 0 0 0
0 1 1 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
...
```

-----

## Auteurs

  * **JUND Tom**
  * **GIRARD Alexis**

*Projet réalisé dans le cadre du module Programmation Orientée Objet de l'Ecole d'Ingénieurs CESI - Campus de Strasbourg.*
