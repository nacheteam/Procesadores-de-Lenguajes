SECTIONS = header.md introduccion.md gramatica.md semantica.md tokens.md tabla-tokens.md
CODE_FOLDER = Implementacion/

all: memoria.pdf

memoria.pdf: $(SECTIONS)
	pandoc $^ -o $@

%::
	@cd ./$(CODE_FOLDER) && $(MAKE) $@
