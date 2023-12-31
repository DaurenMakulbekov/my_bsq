#include "my_bsq.h"
#include <stdlib.h>

int my_strlen(char* value) {
	int index = 0;
	while (value[index] != '\0') {
		index ++;
	}
	return index;
}

char* my_strcpy(char* table_value, char* value) {
	int index = 0;
	while (value[index] != '\0') {
		table_value[index] = value[index];
		index ++;
	}
	table_value[index] = '\0';

	return table_value;
}

void get_array_int(char** ptrRef, int** array_int) {
	int* array = *array_int;
	char* ptr = *ptrRef;
	int number[10] = {0, 1, 2, 3, 4, 5, 6, 7 ,8 ,9};

	int index = 0;
	int count = 0;
	while (*ptr != '\0') {
		count = 0;
		for (int i = 48; i < 58; i++) {
			if (*ptr == i) {
				array[index] = number[count];
				index += 1;
			}
			count += 1;
		}
		ptr ++;
	}
}

int my_atoi(char** ptrRef) {
	int* array_int = NULL;
	int length = my_strlen(*ptrRef);
	array_int = (int*)malloc(length * sizeof(int));
	get_array_int(&(*ptrRef), &array_int);

	int array_numbers[10] = {1, 10, 100, 1000};
	int index_1 = length - 1;
	int number_int = 0;
	int index = 0;
	while (index < length) {
		number_int += array_int[index] * array_numbers[index_1];
		index += 1;
		index_1 -= 1;
	}
	free(array_int);

	return number_int;
}
