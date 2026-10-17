# Compilateur et options
NVCC     := nvcc
NVCCFLAGS := -O3

# Exécutables cibles
TARGETS  := tp1_check.exe

# Règle par défaut : compile tous les programmes
all: $(TARGETS)

# Règle de compilation générique (.cu -> .exe)
%.exe: %.cu
	$(NVCC) $(NVCCFLAGS) -o $@ $<

# Règle pour exécuter les deux programmes avec la taille par défaut
run: all
	@echo "--- Exécution de tp1_check ---"
	./tp1_check.exe

# Règles individuelles pour exécuter un seul programme
run-check: tp1_check.exe
	./tp1_check.exe

# Nettoyage des fichiers générés
clean:
	rm -f $(TARGETS)

.PHONY: all run run-check clean
