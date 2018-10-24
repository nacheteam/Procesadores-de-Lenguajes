ANALIZADOR_LEXICO = lexico
ANALIZADOR_SINTACTICO = sintactico
OBJ = obj/

ifdef SystemRoot
	# En Windows las cadenas se mostrarán en una codificación
	# compatible con cmd aunque en los archivos sean UTF-8
	CHARSET = -fexec-charset=CP850
endif

all: $(ANALIZADOR_LEXICO) $(ANALIZADOR_SINTACTICO)

$(ANALIZADOR_LEXICO).yy.c: $(ANALIZADOR_LEXICO).l
	flex -o $@ $^

$(ANALIZADOR_LEXICO): $(OBJ)$(ANALIZADOR_LEXICO).yy.o
	gcc -o $@ $^ -lfl

$(ANALIZADOR_SINTACTICO).tab.c: $(ANALIZADOR_SINTACTICO).y $(ANALIZADOR_LEXICO).yy.c
	bison -o $@ $<

$(OBJ)%.o: %.c
	gcc -c $^ -o $@ $(CHARSET)

$(ANALIZADOR_SINTACTICO): $(OBJ)$(ANALIZADOR_SINTACTICO).o $(OBJ)$(ANALIZADOR_SINTACTICO).tab.o
	gcc -o $@ $^

clean:
	rm -rf $(OBJ)/*.o *.yy.c *.tab.c
