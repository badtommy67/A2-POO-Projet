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
## 1\. Fonctionnalités

  * **Lecture de grille :** Chargement de l'état initial depuis un fichier texte.
  * **Mode Console :** Simulation rapide avec écriture des itérations dans des fichiers de sortie.
@@ -23,35 +21,35 @@ Ce projet est une implémentation orientée objet de l'automate cellulaire de Jo

-----

## 2\. Architecture technique

Ce projet se distingue par l'utilisation avancée de concepts objets pour éviter le code procédural :

### État

Contrairement à une simple approche booléenne, l'état d'une cellule est géré par polymorphisme.

  * **Classe** : `Cellule` délègue à `Etat_cellule`.
  * **États concrets** : `Est_vivant`, `Est_mort`.
  * **Avantage** : Permet d'ajouter facilement des états futurs (ex: "Malade", "Immunisé") sans changer la classe `Cellule`.

### Règles

Les règles de survie et de naissance sont encapsulées.

  * **Interface** : `Regles_du_jeu`.
  * **Implémentation** : `Regles_initiales` (Règles classiques de Conway).
  * **Avantage** : On peut changer les règles du jeu à la volée (ex: "HighLife", "Day & Night") sans toucher à la grille.

### Architecture du programme simplifiée

  * **Composants** : `Grille`, `Cellule`, `Regles`.
  * **Visualisation** : `Console`, `Graphique`.
  * **Contrôleur** : `Gestion_jeu`.

-----

## 3\. Utilisation

Le programme prend en argument le chemin du fichier de configuration.

@@ -66,7 +64,7 @@ Une fois lancé, le programme vous demandera de choisir le mode :

-----

## 4\. Format du fichier d'entrée

Le fichier doit respecter le format suivant :

@@ -87,7 +85,7 @@ Le fichier doit respecter le format suivant :

-----

## 5\. Auteurs

  * **JUND Tom**
  * **GIRARD Alexis**
