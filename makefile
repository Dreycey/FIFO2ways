CC = gcc
CFLAGS = -Wall -Werror -g -O0
INCLUDE_PATH = headers
EXE_NAME = test_full_pipe.exe

default:
	$(CC) $(CFLAGS) -I$(INCLUDE_PATH) headers/* src/* main.c -o $(EXE_NAME)
clean:
	rm -f *.o *.exe
