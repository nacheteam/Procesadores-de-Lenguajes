SECTIONS = header.md introduccion.md gramatica.md semantica.md tokens.md tabla-tokens.md
FOLDER = Implementacion/
ANALIZADOR_LEXICO = $(FOLDER)lexico

ifdef SystemRoot
	# En Windows las cadenas se mostrarán en una codificación
	# compatible con cmd aunque en los archivos sean UTF-8
	CHARSET = -fexec-charset=CP850
endif

all: $(ANALIZADOR_LEXICO) memoria.pdf

memoria.pdf: $(SECTIONS)
	pandoc $^ -o $@

$(ANALIZADOR_LEXICO).yy.c: $(ANALIZADOR_LEXICO).l
	flex -o $@ $^

$(ANALIZADOR_LEXICO): $(ANALIZADOR_LEXICO).yy.c
	gcc -o $@ $^ -lfl $(CHARSET)
