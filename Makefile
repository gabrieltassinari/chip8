OBJ=main.o decode.o stack.o chip8.o

all: $(OBJ)
	$(CC) $(OBJ) -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o chip8
clean:
	-rm chip8 $(OBJ)

.PHONY: clean
