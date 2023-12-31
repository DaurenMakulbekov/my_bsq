typedef struct Item {
	char* value;
} Item;

typedef struct Table {
	int size;
	Item** items;
} Table;

/* functions.c */
int my_strlen(char* value);
char* my_strcpy(char* table_value, char* value);
void get_array_int(char** ptrRef, int** array_int);
int my_atoi(char** ptrRef);

/* table.c */
Item* create_item(char* value);
Table* create_table(int size);
void free_item(Item* item);
void free_table(Table* table);
void print_table(Table* table);

/* my_readline.c */
void read_first_line(int fd, char* buf, char* buf_1);
char* my_read(int fd, char* buf);
char* my_strcpy_readline(char* buf, char* buf_1, int* index, int fd);
