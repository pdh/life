INCLUDE = -I/usr/include/
LIBRARY = -L/usr/X11R6/lib

COMPILERFLAGS = -Wall
CC = gcc
CFLAGS = $(COMPILERFLAGS) $(INCLUDE)
LIBRARIES = -framework GLUT -framework OpenGL

life : life.o
	$(CC) $(CFLAGS) -o $@ $(LIBDIR) $< $(LIBRARIES)	
