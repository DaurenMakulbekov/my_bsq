#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "my_bsq.h"


int find_min(int top, int top_left, int prev) {
	int min = top;

	if (top_left < min) {
		min = top_left;
	}
	if (prev < min) {
		min = prev;
	}
	
	return min;
}

void fill_array(int size, int array[][size]) {
	int top, top_left, prev, min_value;

	for (int i = 1; i < size; i ++) {
		for (int j = 1; j < size; j ++) {
			top = array[i - 1][j];
			top_left = array[i - 1][j - 1];
			prev = array[i][j - 1];

			if (array[i][j] != 0 && prev != 0 && top != 0 && top_left != 0) {
				min_value = find_min(top, top_left, prev);
				array[i][j] = min_value + 1;
			}
		}
	}
}

void create_array(Table* table, int size, int array[][size]) {
	Item* item = NULL;

	for (int i = 0; i < table->size; i ++) {
		item = table->items[i];
		for (int j = 0; j < table->size; j ++) {
			if (item->value[j] == '.') {
				array[i][j] = 1;
			}
			else {
				array[i][j] = 0;
			}
		}
	}
}

void print_array(int size, int array[][size]) {
	for (int i = 0; i < size; i ++) {
		if (i < 10) {
			printf("%d:  ", i);
		}
		else {
			printf("%d: ", i);
		}
		for (int j = 0; j < size; j ++) {
			printf("%d", array[i][j]);
		}
		printf("\n");
	}
}

void find_max(int size, int array[][size], int* array_bsq_index) {
	int max = array[0][0];

	for (int i = 0; i < size; i ++) {
		for (int j = 0; j < size; j ++) {
			if (array[i][j] > max) {
				max = array[i][j];
				array_bsq_index[0] = i;
				array_bsq_index[1] = j;
			}
		}
	}
}

void my_bsq(Table* table) {
	int size = table->size;
	int array[size][size];
	int array_bsq_index[2] = {};

	create_array(table, size, array);
	fill_array(size, array);
	find_max(size, array, array_bsq_index);
	
	int row_index = array_bsq_index[0];
	int col_index = array_bsq_index[1];
	int bsq = array[row_index][col_index];
	int row_index_1 = row_index - bsq + 1;
	int col_index_1 = col_index - bsq + 1;

	Item* item = NULL;
	for (int i = row_index_1; i <= row_index; i ++) {
		item = table->items[i];
		for (int j = col_index_1; j <= col_index; j ++) {
			item->value[j] = 'x';
		}
	}
}

void fill_table(int fd, Table* table, int size) {
	char* buf = (char*)malloc(512 * sizeof(char));
	char* buf_1 = (char*)malloc(512 * sizeof(char));
	int index = 0;
	buf = my_read(fd, buf);

	for (int i = 0; i < size; i ++) {
		buf_1 = my_strcpy_readline(buf, buf_1, &index, fd);
		Item* item = create_item(buf_1);
		
		table->items[i] = item;
	}
	free(buf);
	free(buf_1);
}

int main(int argc, char* argv[]) {
    if (argc == 1) {
		return 0;
    }
        
	int fd = open(argv[1], O_RDONLY);

	if (fd < 0) {
		printf("No such file\n");
	}
	else {
		char* buf = (char*)malloc(10 * sizeof(char));
		char* buf_1 = (char*)malloc(2 * sizeof(char));
		read_first_line(fd, buf, buf_1);
		int size = my_atoi(&buf);

		Table* table = create_table(size);
		fill_table(fd, table, size);

		my_bsq(table);
		print_table(table);
		/* free table */
		printf("\n");
		free_table(table);

		free(buf);
		free(buf_1);
	}
	close(fd);

	return 0;
}
