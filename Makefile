CC = gcc -O2 
LIBS = 	./libapue.a	

.PHONY:	all clean 

all: pl1-1 pl1-2 pl3-1 pl3-4  pl4-1 pl7-1 pl7-2 pl7-3 pl7-10 pl7-6 pl8-1 pl7-8 pl8-2 pl8-4 pl8-5 pl8-6 pl8-7 pl8-8 pl8-9 pl8-10 pl15-1 pl15-2 pl15-3
pl1-1:pl1-1.c 
	$(CC)  $< -o $@  $(LIBS)
pl1-2:pl1-2.c
	$(CC)  $< -o $@  $(LIBS)
pl3-1:pl3-1.c
	$(CC)  $< -o $@  $(LIBS)
pl3-4:pl3-4.c
	$(CC)  $< -o $@  $(LIBS)
pl4-1:pl4-1.c
	$(CC)  $< -o $@  $(LIBS)
pl7-1:pl7-1.c
	$(CC)  $< -o $@  $(LIBS)
pl7-2:pl7-2.c
	$(CC)  $< -o $@  $(LIBS)
pl7-3:pl7-3.c
	$(CC)  $< -o $@  $(LIBS)
pl7-10:pl7-10.c
	$(CC)  $< -o $@  $(LIBS)
pl7-6:pl7-6.c
	$(CC)  $< -o $@  $(LIBS)
pl8-1:pl8-1.c
	$(CC)  $< -o $@  $(LIBS)
pl7-8:pl7-8.c
	$(CC)  $< -o $@  $(LIBS)
pl8-2:pl8-2.c
	$(CC)  $< -o $@  $(LIBS)
pl8-4:pl8-4.c
	$(CC)  $< -o $@  $(LIBS)
pl8-5:pl8-5.c
	$(CC)  $< -o $@  $(LIBS)
pl8-6:pl8-6.c
	$(CC)  $< -o $@  $(LIBS)
pl8-7:pl8-7.c
	$(CC)  $< -o $@  $(LIBS)
pl8-8:pl8-8.c
	$(CC)  $< -o $@  $(LIBS)
pl8-9:pl8-9.c
	$(CC)  $< -o $@  $(LIBS)
pl8-10:pl8-10.c
	$(CC)  $< -o $@  $(LIBS)
pl15-1:pl15-1.c
	$(CC)  $< -o $@  $(LIBS)
pl15-2:pl15-2.c
	$(CC)  $< -o $@  $(LIBS)
pl15-3:pl15-3.c
	$(CC)  $< -o $@  $(LIBS)

clean:
	rm  -f *.o  
