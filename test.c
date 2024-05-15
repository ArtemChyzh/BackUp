#include "map.c"
#include <stdio.h>

void hi() { printf("Hello, world!\n"); }
void name() { printf("Hello, Artem\n"); }
void mate() { printf("Hello, my friend!\n"); }
void surname() { printf("Hello, Artem Chyzh!\n"); }

int main() {
    map table;
    initmap(&table, 3);

    addto(&table, "hello", hi);
    addto(&table, "name", name);
    addto(&table, "friend", mate);
    addto(&table, "surname", surname);

    executefrom(&table, "hello");
    executefrom(&table, "name");
    executefrom(&table, "friend");
    executefrom(&table, "surname");

    freemap(&table);

    getchar();
    return 0;
}