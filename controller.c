//
// Created by Adrian Szell on 2019. 11. 25..
//
#include "controller.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *get_line_from_input() { //always free when made its purpose
    int buf_size = 32, index = 0;
    char *line = malloc(sizeof(char) * buf_size);
    if (line == NULL) {
        perror("Nem sikerult memoriat foglalni!");
        return NULL;
    }
    int ch;

    while (ch) {
        ch = getchar();

        if (ch == '\n')
            ch = 0;

        if (buf_size <= index) {
            buf_size += 32;
            line = realloc(line, buf_size);
        }
        line[index++] = ch;

    }
    line[index] = '\0';
    return line;
}

void create_new_save() {
    reg_window();
    char *name = get_line_from_input();

    free(name);
}

