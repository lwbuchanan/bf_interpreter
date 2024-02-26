
interpreter.c :
	gcc interpreter.c -o bin/bf

run : interpreter.c
	./bin/bf
