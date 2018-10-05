all: gramatica.pdf memoria.pdf

memoria.pdf: header.md semantica.md tokens.md
	cat $^ | pandoc -o memoria.pdf

%.pdf: %.tex
	pdflatex $^
