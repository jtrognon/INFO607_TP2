.PHONY: all clean # .PHONY -> précise que certaines cibles ne correspondent pas à des fichiers (cible mais pas fichier)

# Cible principale
all: bin/TP2_INFO607_BECHET_TROGNON

# Règle pour construire l'exécutable
bin/TP2_INFO607_BECHET_TROGNON: main.o Liste.o
	gcc $^ -g -O0 -Wall -Wextra -I./headers  -o $@ 
# -I pour le chemin des '#include'

# Ecrit ici car pas de .h donc marche par avec regle generique 
main.o: src/main.c Liste.o
	gcc -c $< -g -O0  -Wall -Wextra -I./headers  -o $@


%.o: src/%.c headers/%.h
	gcc -c $< -I./headers -o $@

# Cible pour nettoyer les fichiers objets et l'exécutable
clean:
	rm -f *.o ./bin/*