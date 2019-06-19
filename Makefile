.c.o:   $*.h
	gcc -c $*.c -I./externals/SOIL/inc

.cpp.o:	$*.h
	g++	-c $*.cpp -I./externals/SOIL/inc

all:	arvore

arvore:  arvore.o winGL.o EstruturasDeDados.o 
	g++ -o $@ $^ -L./external/SOIL/lib -lglut -lGL -lGLU -lSOIL

clean:
	rm *.o *.*~ *~ arvore