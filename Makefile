c:
	gcc -c stringlib.c userFileLib.c userlib.c teacherlib.c studentlib.c
	gcc -o c main.c stringlib.o userFileLib.o userlib.o teacherlib.o studentlib.o
	./c.exe




