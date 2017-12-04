OBJ=$(patsubst ./%.c, ./%.o, $(wildcard ./*.c))

COMPILE=gcc -c
LINK=gcc -o

CFLAG += -g -Wall -D_DEBUG  -I../thirdpart
LIBS += -L../lib/ -lmxml -lpthread
 
BIN=../bin/game

all : $(BIN)

$(BIN):	$(OBJ)
	$(LINK) $@ $^ $(LIBS)

$(OBJ): %.o : %.c
	$(COMPILE) -o $@ $< $(CFLAG)

.PHONY: clean

clean:
	@rm $(BIN) $(OBJ) 
