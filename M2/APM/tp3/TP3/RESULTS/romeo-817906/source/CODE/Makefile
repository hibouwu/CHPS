# Compilateur et options
NVCC     := nvcc
NVCCFLAGS := -O3

# Exécutables cibles
TARGETS  := dgemm-shared.exe

# Taille par défaut de la matrice
SIZE     := 4096

# Règle par défaut : compile tous les programmes
all: $(TARGETS)

# Règle de compilation générique (.cu -> .exe)
%.exe: %.cu
	$(NVCC) $(NVCCFLAGS) -o $@ $<

# Règle pour exécuter les deux programmes avec la taille par défaut
run: all
	@echo "--- Exécution de dgemm-shared ---"
	./dgemm-shared.exe $(SIZE)

# Règles individuelles pour exécuter un seul programme
run-shared: dgemm-shared.exe
	./dgemm-shared.exe $(SIZE)

# Nettoyage des fichiers générés
clean:
	rm -f $(TARGETS)

.PHONY: all run run-shared clean
