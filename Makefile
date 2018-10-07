all: memoria.pdf

SECTIONS = header.md gramatica.md semantica.md tokens.md
memoria.pdf: $(SECTIONS)
	for i in $(SECTIONS); do \
		echo "\n" >> $$i; \
	done
	cat $^ | pandoc -o memoria.pdf
