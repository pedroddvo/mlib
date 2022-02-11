CC=gcc
SRC=$(wildcard lib/*.c)
LIB=$(wildcard lib/*.h)
OBJ=$(SRC:.cpp=.o)
	
%.o: %.c $(LIB)
	$(CC) -Wall -Werror -c -o $@ $<
	
scaffold: $(OBJ)
	$(CC) -Wall -Werror -o $@.exe $(OBJ)