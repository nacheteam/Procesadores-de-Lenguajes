all: memoria.pdf

SECTIONS = header.md introduccion.md gramatica.md semantica.md tokens.md
memoria.pdf: $(SECTIONS)
	pandoc $^ -o memoria.pdf
