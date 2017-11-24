OBJ=$(patsubst ./%.c, ./%.o, $(wildcard ./*.c))

All: $(OBJ)
	gcc -g -o $@ $^

.PHONY: clean

clean:
	@rm All $(OBJ) 
