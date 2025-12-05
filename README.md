# Jeu de la Vie - Projet C++ POO - CESI - A2 <img width="427" height="426" alt="logo_CESI_projet_etudiant_NB (1)" src="https://github.com/user-attachments/assets/11cff3cf-d7eb-4b2b-9753-9771714d70bf" />
Ce projet est une implémentation orientée objet de l'automate cellulaire de John Conway, le **Jeu de la Vie**. Il a été conçu en respectant strictement les principes **SOLID** et en utilisant des **Design Patterns** pour assurer modularité et extensibilité.

## Table des Matières

1.  Objectifs
2.  Architecture technique
3.  Utilisation
4.  Format du fichier d'entrée
5.  Auteurs
-----

## Fonctionnalités
## 1\. Objectifs

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
  * **Avantage** : Permet d'ajouter facilement des états futurs (ex: "Malade", "Immunisé", "Mur") sans changer la classe `Cellule`.

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

Lancez le programme puis répondez aux questions de ce dernier. Les réponses attendues vous sont proposées par une entrée numérale.

Lancez le programme : 

```bash
./JeuDeLaVie
```


<ins>Une fois lancé, le programme vous demandera de choisir si vous souhaitez faire un test unitaire :</ins>


1.  **Oui - test unitaire** : Execution automatique du programme avec un fichier contenant un clignotant (forme spéciale de grille) et vérifiant à un X-ième état, le bon fonctionnement du jeu. Vous avez fini !
2.  **Non - execution normale** : Vous aurez d'autres questions, continuez la lecture.


<ins>Vous souhaitez donc lancer normalemment le jeu de la vie. Le programme vous demandera si vous avez un fichier d'entrée ou si vous souhaitez générer une grille aléatoire.</ins>


Dans le cas où vous souhaitez une grille aléatoire, on vous demandera dans l'ordre : le nombre d'itérations voulues, un affichage graphique ou console, une grille normale ou torique et enfin le nombre de lignes puis de colonnes.


Dans le cas où vous souhaitez donner un fichier d'entrée, on vous demandera dans l'ordre : le nom du fichier d'entrée (avec le chemin s'il se situe dans `Fichiers_source`), le nombre d'itérations voulues, un affichage graphique ou console et enfin une grille normale ou torique.

-----

## 4\. Format du fichier d'entrée

Le programme prend en argument le chemin du fichier de configuration.

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

## 5\. Auteurs

  * **JUND Tom**
  * **GIRARD Alexis**
