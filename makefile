OBJ= main.o read.o history.o execute.o change.o
all: sheII
sheII:$(OBJ)
	gcc $(OBJ) -o sheII -Wall
$(OBJ): read.h history.h execute.h change.h
.PHONY: clean
clean:
	rm -f *.o sheII
