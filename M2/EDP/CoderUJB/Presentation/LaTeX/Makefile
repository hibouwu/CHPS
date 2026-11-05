LATEXMK ?= latexmk
MAIN := CoderUJB_Equipe6_FR

.PHONY: all clean package
all:
	$(LATEXMK) -pdf -interaction=nonstopmode -halt-on-error -file-line-error $(MAIN).tex

clean:
	$(LATEXMK) -c $(MAIN).tex

package: all
	zip -FS ../CoderUJB_Equipe6_LaTeX.zip CoderUJB_*.tex CoderUJB_*.pdf CoderUJB_*.md README.md Makefile .gitignore assets/*.pdf
