#include <stdio.h>
#include "my_bsq.h"
#include <stdlib.h>


Item* create_item(char* value) {
	int length_value = my_strlen(value);

	Item* item = (Item*)malloc(sizeof(Item));
	item->value = (char*)malloc((length_value + 1) * sizeof(char));;

	item->value = my_strcpy(item->value, value);

	return item;
}

Table* create_table(int size) {
	Table* table = (Table*)malloc(sizeof(Table));
	table->size = size;
	table->items = (Item**)malloc(table->size * sizeof(Item*));

	for (int i = 0; i < table->size; i ++) {
		table->items[i] = NULL;
	}

	return table;
}

void print_table(Table* table) {
	for (int i = 0; i < table->size; i ++) {
		Item* item = table->items[i];
		printf("%s\n", item->value);
	}
}

void free_item(Item* item) {
	free(item->value);
	free(item);
	//printf("Item freed\n");
}

void free_table(Table* table) {
	for (int i = 0; i < table->size; i ++) {
		Item* item = table->items[i];
		free_item(item);
	}
	printf("Items freed\n");
	free(table->items);
	free(table);
	printf("Table freed\n");
}
