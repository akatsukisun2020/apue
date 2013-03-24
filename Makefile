CC = gcc -O2
LIBS = 	./libapue.a

.PHONY:	all clean 

all: pl1-1 pl1-2 pl11-1 pl11-2
pl1-1:pl1-1.c 
		$(CC) $< -o $@.o $(LIBS)
pl1-2:pl1-2.c
		$(CC) $< -o $@.o $(LIBS)
pl11-1:pl11-1.c
	$(CC) $< -o $@.o $(LIBS) -pthread
pl11-2:pl11-2.c
	$(CC) $< -o $@.o $(LIBS) -pthread

clean:
		rm  -f *.o *~ 

