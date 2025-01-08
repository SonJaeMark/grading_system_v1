c:
	gcc -c stringlib.c userFileLib.c userlib.c
	gcc -o c main.c stringlib.o userFileLib.o userlib.o
	./c.exe




