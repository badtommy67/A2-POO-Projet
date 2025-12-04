# Jeu de la Vie - Projet C++ POO - CESI - A2 <img width="427" height="426" alt="logo_CESI_projet_etudiant_NB (1)" src="https://github.com/user-attachments/assets/11cff3cf-d7eb-4b2b-9753-9771714d70bf" />

Ce projet est une implémentation orientée objet de l'automate cellulaire de John Conway, le **Jeu de la Vie**. Il a été conçu en respectant strictement les principes **SOLID** et en utilisant des **Design Patterns** pour assurer modularité et extensibilité.

## Table des Matières

1.  Fonctionnalités
2.  Architecture technique
3.  Utilisation
4.  Format du fichier d'entrée
5.  Auteurs
-----

## Fonctionnalités

  * **Lecture de grille :** Chargement de l'état initial depuis un fichier texte.
  * **Mode Console :** Simulation rapide avec écriture des itérations dans des fichiers de sortie.
  * **Mode Graphique :** Visualisation temps réel de l'automate utilisant la bibliothèque **SFML**.
  * **Architecture évolutive :** Ajout facile de nouvelles règles ou de nouveaux états sans modifier le cœur du programme.
  * **Tests Unitaires :** Vérification de la robustesse de la logique.

-----

## Architecture technique

Ce projet se distingue par l'utilisation avancée de concepts objets pour éviter le code procédural :

### 1\. État

Contrairement à une simple approche booléenne, l'état d'une cellule est géré par polymorphisme.

  * **Classe** : `Cellule` délègue à `Etat_cellule`.
  * **États concrets** : `Est_vivant`, `Est_mort`.
  * **Avantage** : Permet d'ajouter facilement des états futurs (ex: "Malade", "Immunisé") sans changer la classe `Cellule`.

### 2\. Règles

Les règles de survie et de naissance sont encapsulées.

  * **Interface** : `Regles_du_jeu`.
  * **Implémentation** : `Regles_initiales` (Règles classiques de Conway).
  * **Avantage** : On peut changer les règles du jeu à la volée (ex: "HighLife", "Day & Night") sans toucher à la grille.

### 3\. Architecture du programme simplifiée

  * **Composants** : `Grille`, `Cellule`, `Regles`.
  * **Visualisation** : `Console`, `Graphique`.
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

## Format du fichier d'entrée

Le fichier doit respecter le format suivant :

1.  Première ligne : `Lignes Colonnes`
2.  Lignes suivantes : Matrice de `0` (mort) et `1` (vivant).

**Exemple (`grille.txt`) :**

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
