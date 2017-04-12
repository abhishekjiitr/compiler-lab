all: calc
	./calc
calc: y.tab.c lex.yy.c 
	gcc lex.yy.c y.tab.c -o calc
lex.yy.c: 
	lex calc.l
y.tab.c: 
	yacc -d calc.y