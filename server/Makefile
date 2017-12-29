#COMMON_OBJ=$(patsubst ../framework/%.c, ./framework/%.o, $(wildcard ./framework/*.c))

COMMON_OBJ = ../framework/array.o \
	../framework/buffer.o \
	../framework/list.o \
	../framework/log.o \
	../framework/palloc.o \
	../framework/queue.o \
	../framework/rbtree.o \
	../framework/shm.o \
	../framework/times.o

THIRD_OBJ = ../include/cJSON.o

OBJ=$(patsubst ./%.c, ./%.o, $(wildcard ./*.c))

COMPILE=gcc -c
LINK=gcc -o

CFLAG += -g -Wall -D_DEBUG  -I../include -I../framework
LIBS += -L../lib/ -lmxml -lpthread
 
BIN=../bin/mobile_server

all : $(BIN)

$(BIN):	$(COMMON_OBJ) $(OBJ) $(THIRD_OBJ)
	$(LINK) $@ $^ $(LIBS)

$(COMMON_OBJ): %.o : %.c
	$(COMPILE) -o $@ $< $(CFLAG)

$(OBJ): %.o : %.c	
	$(COMPILE) -o $@ $< $(CFLAG)

.PHONY: clean

clean:
	@rm $(BIN) $(COMMON_OBJ) $(OBJ) $(THIRD_OBJ) 
