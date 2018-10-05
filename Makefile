all: memoria.pdf

memoria.pdf: header.md gramatica.md semantica.md tokens.md
	cat $^ | pandoc -o memoria.pdf
