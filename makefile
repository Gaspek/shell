OBJ= main.o read.o
all: sheII
sheII:$(OBJ)
	gcc $(OBJ) -o sheII -Wall
$(OBJ): read.h
.PHONY: clean
clean:
	rm -f *.o sheII
