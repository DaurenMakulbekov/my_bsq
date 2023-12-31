CC=gcc
CFLAGS=-Wall -Wextra -Werror
TARGET=my_bsq

all:
	$(CC) ${CFLAGS} my_bsq.c functions.c table.c my_readline.c -o ${TARGET}

clean:
	rm -f my_bsq

fclean: clean
