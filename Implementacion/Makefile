ANALIZADOR_LEXICO = lexico
ANALIZADOR_SINTACTICO = sintactico
ANALIZADOR_SEMANTICO = semantico
GENERADOR_CODIGO = generador
OBJ = obj/

ifdef OS
	# En Windows las cadenas se mostrarán en una codificación
	# compatible con cmd aunque en los archivos sean UTF-8
	CHARSET = -fexec-charset=CP850 -DPUNTO='">"'
endif

all: $(ANALIZADOR_LEXICO) $(ANALIZADOR_SINTACTICO) $(ANALIZADOR_SEMANTICO) $(GENERADOR_CODIGO)

programas: all

$(ANALIZADOR_LEXICO).yy.c: $(ANALIZADOR_LEXICO).l
	flex -o $@ $^

$(ANALIZADOR_LEXICO): $(OBJ)$(ANALIZADOR_LEXICO).yy.o $(OBJ)error.o $(OBJ)file_io.o $(OBJ)tabla.o
	gcc -o $@ $^

y.tab.c: $(ANALIZADOR_SEMANTICO).y $(ANALIZADOR_LEXICO).yy.c
	bison -dyv -o $@ $<

y_syntax.tab.c: $(ANALIZADOR_SINTACTICO).y $(ANALIZADOR_LEXICO).yy.c y.tab.c
	bison -dyv -o $@ $<

$(OBJ)$(ANALIZADOR_LEXICO).yy.o: $(ANALIZADOR_LEXICO).yy.c y.tab.c
	@mkdir -p $(OBJ)
	gcc -c $< -o $@ $(CHARSET) -DMAIN_LEXICO

$(ANALIZADOR_SINTACTICO).y: $(ANALIZADOR_SEMANTICO).y
	@cat $< | tr '\n' '\f' | tr '\r' '\v' | tr '\\' '\b' | sed -rb "s/%type [^\f\v]+(\v)?\f//g;s/(%token )(<[^>]*>) /\1/g;s/ \{([^\{\}]*\{[^\{\}]*\})+[^\{\}]*\}( *)/\2/g;s/ \{[^\{]*\}( *)/\1/g" | tr '\b' '\\' | tr '\f' '\n' | tr '\v' '\r' > $@

$(OBJ)%.o: %.c
	@mkdir -p $(OBJ)
	gcc -c $< -o $@ $(CHARSET)

$(ANALIZADOR_SINTACTICO): $(OBJ)main_$(ANALIZADOR_SINTACTICO).o $(OBJ)y_syntax.tab.o $(OBJ)error.o $(OBJ)file_io.o $(OBJ)tabla.o
	gcc -o $@ $^

$(ANALIZADOR_SEMANTICO): $(OBJ)main_$(ANALIZADOR_SEMANTICO).o $(OBJ)y.tab.o $(OBJ)error.o $(OBJ)file_io.o $(OBJ)tabla.o
	gcc -o $@ $^

$(GENERADOR_CODIGO): $(OBJ)main_$(GENERADOR_CODIGO).o $(OBJ)y.tab.o $(OBJ)error.o $(OBJ)file_io.o $(OBJ)tabla.o
	gcc -o $@ $^

clean:
	rm -rf $(OBJ)*.o *.yy.c *.tab.c *.tab.h
