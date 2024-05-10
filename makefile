OBJ= main.o read.o history.o
all: sheII
sheII:$(OBJ)
	gcc $(OBJ) -o sheII -Wall
$(OBJ): read.h history.h
.PHONY: clean
clean:
	rm -f *.o sheII
