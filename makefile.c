# Nom de l'exécutable
EXEC = plagiarism_checker

# Commande de compilation
CC = gcc
CFLAGS = -Wall -Wextra

# Liste des fichiers de test
FILES = file1.c file2.c file3.c file4.c file5.c

# Cible par défaut : compile l'exécutable
all: $(EXEC)

# Compilation du programme
$(EXEC): main.c
	$(CC) $(CFLAGS) main.c -o $(EXEC)

# Exécution sur tous les fichiers pour générer la matrice complète
run: $(EXEC)
	@echo "Calcul de la matrice de distances pour tous les fichiers..."
	@./$(EXEC) $(FILES)

# Nettoyage : supprime l'exécutable et fichiers générés (.pgm)
clean:
	rm -f $(EXEC) *.pgm
