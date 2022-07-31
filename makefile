CFLAGS=-m64 -std=c99 -pedantic -Wall
CFILES=source/main.c source/setup.c
BUILD=build/test.exe

all: compile

compile: $(CFILES)
	gcc $(CFLAGS) $(CFILES) -o $(BUILD) -lws2_32 -lgdi32 -lmswsock

clean: 
	rm $(BUILD) source/main.c~ source/main.h~ source/setup.c~ source/setup.h~
