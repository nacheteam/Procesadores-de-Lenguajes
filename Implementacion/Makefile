ANALIZADOR_LEXICO = lexico
ANALIZADOR_SINTACTICO = sintactico
OBJ = obj/

ifdef OS
	# En Windows las cadenas se mostrarán en una codificación
	# compatible con cmd aunque en los archivos sean UTF-8
	CHARSET = -fexec-charset=CP850
endif

all: $(ANALIZADOR_LEXICO) $(ANALIZADOR_SINTACTICO)

programas: all

$(ANALIZADOR_LEXICO).yy.c: $(ANALIZADOR_LEXICO).l
	flex -o $@ $^

$(ANALIZADOR_LEXICO): $(OBJ)$(ANALIZADOR_LEXICO).yy.o $(OBJ)yyerror.o
	gcc -o $@ $^

y.tab.c: $(ANALIZADOR_SINTACTICO).y $(ANALIZADOR_LEXICO).yy.c
	bison -dy -o $@ $<

$(OBJ)$(ANALIZADOR_LEXICO).yy.o: $(ANALIZADOR_LEXICO).yy.c y.tab.c
	gcc -c $< -o $@ $(CHARSET) -DMAIN_LEXICO

$(OBJ)%.o: %.c
	gcc -c $< -o $@ $(CHARSET)

$(ANALIZADOR_SINTACTICO): $(OBJ)main_$(ANALIZADOR_SINTACTICO).o $(OBJ)y.tab.o $(OBJ)yyerror.o
	gcc -o $@ $^

clean:
	rm -rf $(OBJ)*.o *.yy.c *.tab.c *.tab.h
