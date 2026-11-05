LATEXMK ?= latexmk
MAIN := CoderUJB_Equipe6_FR

.PHONY: all clean
all:
	$(LATEXMK) -pdf -interaction=nonstopmode -halt-on-error -file-line-error $(MAIN).tex

clean:
	$(LATEXMK) -c $(MAIN).tex
