# PROJET-PLAGIAT-L2---C
Ce projet implémente un outil simple de détection de similarité entre fichiers C. Il utilise une approche basée sur les n-grammes et la distance de Dice pour comparer le contenu de n fichiers source, et fournit un score de proximité permettant d’identifier d’éventuelles ressemblances ou suspicions de plagiat.
Le code génère des matrices de distances visualisables en image PGM.


 -- READ ME --
 Ouvrez main.c dans votre éditeur de texte en code source C.
 Veillez à avoir vos fichiers tests dans le même répertoire que le code source (des fichiers test ont été mis à disposition). 
 Compilez main.c via votre terminal, puis executez avec les fichiers voulus. 

## Contenu du dépôt

- `main.c` : programme principal de détection de similarité  
- `file1.c` … `file5.c` : fichiers de test pour exécuter le programme  
- `Makefile` : pour compiler et exécuter automatiquement le programme  
- `README.md` : documentation  

---

## Prérequis

- GCC ou Clang installé  
- `make` disponible  
- SSH configuré pour GitHub si clonage via SSH  

---

## Installation et utilisation

### 1. Cloner le dépôt

```bash
git clone git@github.com:TON_USER/PROJET-PLAGIAT-L2---C.git
cd PROJET-PLAGIAT-L2---C

## 2. Compiler le programme

```bash
make

---

## Lancer toutes les comparaisons

```bash
make run

- Compare automatiquement tous les fichiers listés dans le Makefile (FILES)
- Affiche les distances entre chaque paire de fichiers
-Génère des fichiuer .pgm pour visualiser les matrices
 . dice_*.pgm --> distances de Dice
 . couplage_*.pgm --> couplage optimisés
 . filtrage_*.pgm --> post-filtrage
 . distances.pgm --> matrice finale de toutes les distances

## NOTA BENE
- Les distances sont normalsiées entre 0 et 1:
  . O --> ficheirs identiques
  . 1 --> fichiers très différents
- Le programme peut être étendu à plus de fichiers simplement en modifiant la variable FILES dans le Makefile.

--- 

