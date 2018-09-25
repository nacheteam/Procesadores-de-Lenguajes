all: gramatica.pdf

%.pdf: %.tex
	pdflatex $^
