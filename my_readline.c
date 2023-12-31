#include <unistd.h>
#include "my_bsq.h"


void read_first_line(int fd, char* buf, char* buf_1) {
	int index = 0;

		while (buf_1[0] != '\n') {
			read(fd, buf_1, 1);
			if (buf_1[0] != '\n') {
				buf[index] = buf_1[0];
				index ++;
			}
		} 
		buf[index] = '\0';
}

char* my_read(int fd, char* buf) {
	int sz = read(fd, buf, 511);
	buf[sz] = '\0';

	return buf;
}

char* my_strcpy_readline(char* buf, char* buf_1, int* index, int fd) {
	int index_1 = 0;
	int index_2 = *index;

	while (buf[index_2] != '\n') {
		if (buf[index_2] == '\0') {
			buf = my_read(fd, buf);
			index_2 = 0;
		}
		else {
			buf_1[index_1] = buf[index_2];
			index_1 ++;
			index_2 ++;
		}
	}
	buf_1[index_1] = '\0';
	*index = index_2 + 1;

	return buf_1;
}
